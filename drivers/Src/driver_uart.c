#include "driver_uart.h"


void UART_PeriClockControl(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART->PENABLE = (4 << 0);
    }else
    {
        UART->PENABLE = 0;
    }
}

void UART_Init(UART_Handle_t* pUARTHandle)
{
    UART_PeriClockControl(DISABLE);

    uint32_t temp = 0;
    if(pUARTHandle->UART_Config.USART_Mode == UART_MODE_ONLY_TX)
    {

    }else if(pUARTHandle->UART_Config.USART_Mode == UART_MODE_ONLY_RX)
    {

    }else if(pUARTHandle->UART_Config.USART_Mode == UART_MODE_TXRX)
    {

    }

    uint32_t temp = ((0 << 31) | (1 << 5) | (3 << 0));
    UART->PSEL_TXD = temp;
    
    // 2. init peripheral in tx
    UART_PeriClockControl(ENABLE);
    UART->BAUDRATE = 0x00275000U;

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