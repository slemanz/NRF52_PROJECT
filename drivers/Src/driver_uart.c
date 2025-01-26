#include "driver_uart.h"

void uart_init(void)
{
    // 1. init pin tx
    GPIO_Handle_t uartTx;
    uartTx.pGPIOx = GPIOP1;
    uartTx.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    uartTx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    uartTx.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_NO_PUPD;
    GPIO_Init(&uartTx);
    GPIO_WriteToOutputPin(GPIOP1, GPIO_PIN_NO_3, GPIO_PIN_SET);

    uint32_t temp = ((0 << 31) | (1 << 5) | (3 << 0));
    UART->PSEL_TXD = temp;
    

    // 2. init peripheral in tx
    UART->BAUDRATE = 0x00275000U;
    UART->PENABLE = (4 << 0);
}

void uart_write_byte(uint8_t ch)
{

    UART_TASKS->STARTTX |= 1;
    UART->TXD = (ch);

    event_pooling(&UART_EVENTS->TXDRDY);

    UART_TASKS->STOPTX |= 1;
}

void uart_write(uint8_t* buffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        uart_write_byte(buffer[i]);
    }
}