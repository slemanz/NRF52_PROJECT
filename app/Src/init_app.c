#include "init_app.h"
#include "nrf52.h"

static volatile uint64_t ticks = 0;


static void system_systickInit(void);
static void system_setupGpio(void);
static void system_setupUart(void);
static void system_setupSpi(void);
static void system_setupSaadc(void);


void system_init(void)
{
    system_systickInit();
    system_setupGpio();
    system_setupUart();
    system_setupSpi();
    system_setupSaadc();
}

uint64_t system_get_ticks(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}

static void system_systickInit(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();

}

static void system_setupGpio(void)
{
    GPIO_Handle_t ledPins;
    ledPins.pGPIOx = GPIOP0;
    ledPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_GREEN_PIN;
    ledPins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    ledPins.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_DISCONNECT;
    ledPins.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_SET;
    GPIO_Init(&ledPins);

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_BLUE_PIN;
    GPIO_Init(&ledPins);

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_RED_PIN;
    GPIO_Init(&ledPins);

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_BUILT_IN;
    GPIO_Init(&ledPins);

    GPIO_Handle_t inputPin;
    inputPin.pGPIOx = BUTTON1_PORT;
    inputPin.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_IN;
    inputPin.GPIO_PinConfig.GPIO_PinNumber = BUTTON1_PIN;
    inputPin.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_PU;
    inputPin.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_CONNECT;
    GPIO_Init(&inputPin);
}

static void system_setupUart(void)
{
    // 1. init pin tx
    GPIO_Handle_t uartTx;
    uartTx.pGPIOx = GPIOP1;
    uartTx.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    uartTx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    uartTx.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    uartTx.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_DISCONNECT;
    uartTx.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_SET;
    GPIO_Init(&uartTx);
    
    // 2. init pin rx
    GPIO_Handle_t uartRx;
    uartRx.pGPIOx = GPIOP1;
    uartRx.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_IN;
    uartRx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    uartRx.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    uartRx.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_CONNECT;
    GPIO_Init(&uartRx);


    // 3. init peripheral
    UART_Handle_t UARTHandle;
    UARTHandle.UART_Config.Baud = UART_STD_BAUD_115200;
    UARTHandle.UART_Config.Mode = UART_MODE_TXRX;
    UARTHandle.Tx.port = GPIOP1;
    UARTHandle.Tx.pin  = GPIO_PIN_NO_3;
    UARTHandle.Rx.port = GPIOP1;
    UARTHandle.Rx.pin  = GPIO_PIN_NO_10;
    UART_Init(&UARTHandle);
    uart_interruptConfig(UART_INTERRUPT_RXRDY, ENABLE);
    interrupt_config(UART_IRQ_NO, ENABLE);
}

static void system_setupSpi(void)
{
    GPIO_Handle_t SpiPins;
    SpiPins.pGPIOx = SPI_PORT;
    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MISO;
    SpiPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_IN;
    SpiPins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    SpiPins.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_CONNECT;
    GPIO_Init(&SpiPins);

    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_SCK;
    SpiPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    SpiPins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    SpiPins.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_RESET;
    GPIO_Init(&SpiPins);

    SpiPins.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_DISCONNECT;
    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MOSI;
    GPIO_Init(&SpiPins);


    GPIO_Handle_t CsPin;
    CsPin.pGPIOx = CS_PORT;
    CsPin.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    CsPin.GPIO_PinConfig.GPIO_PinNumber = CS_PIN;
    CsPin.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    CsPin.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_SET;
    CsPin.GPIO_PinConfig.GPIO_InpBuf = GPIO_INP_BUF_DISCONNECT;
    GPIO_Init(&CsPin);

    SPI_Handle_t SPIHandle;
    SPIHandle.pSPIx = SPI0;
    SPIHandle.SPI_Config.CPHA = SPI_CPHA_LOW;
    SPIHandle.SPI_Config.CPOL = SPI_CPOL_LOW;
    SPIHandle.SPI_Config.Frequency = SPI_FREQUENCY_K250;

    SPIHandle.MISO.port = SPI_PORT;
    SPIHandle.MOSI.port = SPI_PORT;
    SPIHandle.SCK.port  = SPI_PORT;

    SPIHandle.MISO.pin = SPI_PIN_MISO;
    SPIHandle.MOSI.pin = SPI_PIN_MOSI;
    SPIHandle.SCK.pin  = SPI_PIN_SCK;
    SPI_Init(&SPIHandle);
}

static void system_setupSaadc(void)
{
    // A2 -> P0.4
    SAADC_Handle_t SAADCHandle;
    SAADCHandle.CHANNEL = SAADC_CHANNEL_0;
    SAADCHandle.RESN    = SAADC_RES_BYPASS;
    SAADCHandle.RESP    = SAADC_RES_BYPASS;
    SAADCHandle.GAIN    = SAADC_GAIN_1_4;
    SAADCHandle.REFSEL  = SAADC_REFSEL_VDD_1_4;
    SAADCHandle.MODE    = SAADC_MODE_SE;
    SAADCHandle.TACQ    = SAADC_TACQ_15US;
    SAADCHandle.RESOLUTION = SAADC_RESOLUTION_12BIT;

    SAADCHandle.PSELP   = SAADC_PSEL_AIN2;
    SAADCHandle.PSELN   = SAADC_PSEL_NC;

    saadc_init(&SAADCHandle);
}