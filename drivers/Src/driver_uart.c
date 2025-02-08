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

    // 1, Config pins
    uint8_t psel_port = 0;

    uint32_t temp = 0;
    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL_TXD = temp;
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL_RXD = temp;

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL_TXD = temp;

        psel_port = 0;
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL_RXD = temp;
    }
    
    // 2. init peripheral
    UART_PeriClockControl(ENABLE);
    UART->BAUDRATE = pUARTHandle->UART_Config.Baud;

    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        uart_tx_start();
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {
        uart_rx_start();

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {
        uart_tx_start();
        uart_rx_start();
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

void uart_rx_start(void)
{
    UART_TASKS->STARTRX |= 1;
}

void uart_rx_stop(void)
{
    UART_TASKS->STOPRX |= 1;
}


void uart_interruptConfig(uint32_t interrupts, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART_INTEN->SET |= interrupts;
    }else
    {
        UART_INTEN->CLR |= interrupts;
    }
}