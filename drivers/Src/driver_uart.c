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

    uint8_t psel_port = 0;

    uint32_t temp = 0;
    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL_TXD = temp;
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {

    }
    
    // 2. init peripheral
    UART_PeriClockControl(ENABLE);
    UART->BAUDRATE = pUARTHandle->UART_Config.Baud;

    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        uart_tx_start();
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {

    }
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