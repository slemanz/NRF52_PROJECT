// Author: William Sleman @ 2024/25
#include <stdio.h>
#include "nrf52.h"
#include "init_app.h"

#define SPI_PORT            GPIOP1
#define SPI_PIN_MISO        GPIO_PIN_NO_8
#define SPI_PIN_MOSI        GPIO_PIN_NO_1
#define SPI_PIN_SCK         GPIO_PIN_NO_2

#define CS_PORT             GPIOP0
#define CS_PIN              GPIO_PIN_NO_27

const uint8_t leds_pin[] = {0, LED_BLUE_PIN, LED_RED_PIN, LED_GREEN_PIN};

// retarget printf
extern int __io_putchar(int ch)
{
    uart_write_byte((uint8_t)ch);
    return ch;
}

uint8_t rcv = 0;

int main(void)
 {
    system_init();

    GPIO_Handle_t SpiPins;
    SpiPins.pGPIOx = SPI_PORT;
    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MISO;
    SpiPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_IN;
    SpiPins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    GPIO_Init(&SpiPins);

    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MOSI;
    SpiPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    SpiPins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    SpiPins.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_RESET;
    GPIO_Init(&SpiPins);

    SpiPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_SCK;
    GPIO_Init(&SpiPins);
    GPIOP1_CNF->CNF[SPI_PIN_SCK] &= ~(1 << 1);


    GPIO_Handle_t CsPin;
    CsPin.pGPIOx = CS_PORT;
    CsPin.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    CsPin.GPIO_PinConfig.GPIO_PinNumber = CS_PIN;
    CsPin.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    CsPin.GPIO_PinConfig.GPIO_PinState = GPIO_PIN_SET;
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

    uint8_t sendSpi[] = "Hello World!";






    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    uint8_t cnt = 0;

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system\n\r");

    while (1)
    {   
       if(rcv != 0)
       {
            printf("%c", rcv);
            rcv = 0;
       }

        if((system_get_ticks() - start_time) >= 1000)
        {
            GPIO_WriteToOutputPin(GPIOP0, LED_GREEN_PIN, GPIO_PIN_SET);
            GPIO_WriteToOutputPin(GPIOP0, LED_RED_PIN, GPIO_PIN_SET);
            GPIO_WriteToOutputPin(GPIOP0, LED_BLUE_PIN, GPIO_PIN_SET);

            if(leds_pin[cnt] != 0) GPIO_WriteToOutputPin(GPIOP0, leds_pin[cnt], GPIO_PIN_RESET);

            cnt++;
            cnt &= 0x3;
            start_time = system_get_ticks();
        }
        

        if((system_get_ticks() - start_time2) >= 2000) // send hello world
        {
            //printf("Working\n");
            GPIO_WriteToOutputPin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
            SPI_SendData(SPI0, sendSpi, 12);
            GPIO_WriteToOutputPin(CS_PORT, CS_PIN, GPIO_PIN_SET);
            start_time2 = system_get_ticks();
        }

        if(!GPIO_ReadFromInputPin(BUTTON1_PORT, BUTTON1_PIN))
        {
            GPIO_WriteToOutputPin(GPIOP0, LED1_EXT_PIN, GPIO_PIN_SET);
        }else
        {
            GPIO_WriteToOutputPin(GPIOP0, LED1_EXT_PIN, GPIO_PIN_RESET);
        }
    }
}


void UART_IRQHandler(void)
{
    if(UART_EVENT_RXDRDY)
    {
        event_clear(&UART_EVENT_RXDRDY);
        rcv = UART->RXD;
    }
}