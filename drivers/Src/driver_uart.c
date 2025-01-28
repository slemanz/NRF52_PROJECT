#include "driver_uart.h"

void uart_init(void)
{
    uint32_t temp = ((0 << 31) | (1 << 5) | (3 << 0));
    UART->PSEL_TXD = temp;
    
    // 2. init peripheral in tx
    UART->BAUDRATE = 0x00275000U;
    UART->PENABLE = (4 << 0);

    uart_tx_start();
}

void uart_write_byte(uint8_t ch)
{
    UART->TXD = (ch);
    event_pooling(&UART_EVENTS->TXDRDY);
}

void uart_write(uint8_t* buffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        uart_write_byte(buffer[i]);
    }
}

void uart_tx_start(void)
{
    UART_TASKS->STARTTX |= 1;
}

void uart_tx_stop(void)
{
    UART_TASKS->STOPTX |= 1;
}