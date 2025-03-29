#include "init_app.h"
#include "nrf52.h"
#include "core/ticks.h"

static volatile uint64_t ticks = 0;


static void system_systickInit(void);
static void system_setupGpio(void);
static void system_setupUart(void);
static void system_setupSpi(void);
static void system_setupSaadc(void);
static void system_setupTwi(void);


void system_init(void)
{
    system_systickInit();
    system_setupGpio();
    system_setupUart();
    system_setupSpi();
    system_setupSaadc();
    system_setupTwi();
}

uint64_t system_get_ticks(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks_increment();
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
    UART_Handle_t UARTHandle;
    UARTHandle.UART_Config.Baud = UART_STD_BAUD_115200;
    UARTHandle.UART_Config.Mode = UART_MODE_TXRX;

    UARTHandle.Tx.port = UART_TX_PORT;
    UARTHandle.Tx.pin  = UART_TX_PIN;
    UARTHandle.Rx.port = UART_RX_PORT;
    UARTHandle.Rx.pin  = UART_RX_PIN;

    UART_Init(&UARTHandle);
    uart_interruptConfig(UART_INTERRUPT_RXRDY, ENABLE);
    interrupt_config(UART_IRQ_NO, ENABLE);
}

static void system_setupSpi(void)
{
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
    SPIHandle.SPI_Config.Frequency = SPI_FREQUENCY_K125;

    SPIHandle.MISO.port = SPI_PORT_MISO;
    SPIHandle.MOSI.port = SPI_PORT_MOSI;
    SPIHandle.SCK.port  = SPI_PORT_SCK;

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

    (void)SAADCHandle;
    ///saadc_init(&SAADCHandle);
}

static void system_setupTwi(void)
{
    TWI_Handle_t TWIHandle;
    TWIHandle.config.FREQUENCY = TWI_FREQUENCY_K100;
    TWIHandle.pTWIx = TWI1;

    TWIHandle.SCL.port = TWI_SCL_PORT;
    TWIHandle.SCL.pin = TWI_SCL_PIN;

    TWIHandle.SDA.port = TWI_SDA_PORT;
    TWIHandle.SDA.pin = TWI_SDA_PIN;

    TWI_Init(&TWIHandle);
}

// retarget printf
extern int __io_putchar(int ch)
{
    uart_write_byte((uint8_t)ch);
    return ch;
}