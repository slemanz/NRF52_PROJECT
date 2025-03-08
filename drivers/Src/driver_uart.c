/*
 * ==========================================================================================
 *      File: driver_uart.c
 *      Author: William Sleman
 *
 *      Description:
 *      This source file contains the implementation of functions for configuring and 
 *      managing the Universal Asynchronous Receiver-Transmitter (UART). It includes 
 *      functions for initializing the UART peripheral, transmitting and receiving data, 
 *      and managing UART interrupts. The implementation supports various modes of 
 *      operation, including only transmission, only reception, and both.
 *
 *      Note:
 *      For details on the structures and function prototypes, see the header file: 
 *      driver_uart.h.
 * ==========================================================================================
 */
#include "driver_uart.h"
#include "ring-buffer.h"

#define RING_BUFFER_SIZE		(128)
static ring_buffer_t rb = {0U};
static uint8_t data_buffer[RING_BUFFER_SIZE] = {0U};


/*
 ********************************************************************************************
 * @fn              - UART_PeriClockControl
 *
 * @brief           - Enables or disables the clock for the UART peripheral.
 *
 * @param[in]       - EnorDi: Flag indicating whether to enable (ENABLE) or disable (DISABLE) the clock.
 *
 * @return          - none
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

void UART_PeriClockControl(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART->ENABLER = (4 << 0);
    }else
    {
        UART->ENABLER = 0;
    }
}


/*
 ********************************************************************************************
 * @fn              - UART_Init
 *
 * @brief           - Initializes the UART peripheral based on the provided configuration
 *                    settings in the UART_Handle_t structure, including pin configuration 
 *                    and UART mode.
 *
 * @param[in]       - pUARTHandle: Pointer to a UART_Handle_t structure containing the 
 *                    UART configuration settings.
 *
 * @return          - none
 *
 * @Note            - This function sets up pin multiplexing based on the mode (TX, RX, or TXRX)
 *                    and initializes the peripheral according to the specified baud rate.
 *
 ********************************************************************************************
 */

void UART_Init(UART_Handle_t* pUARTHandle)
{
    ring_buffer_setup(&rb, data_buffer, RING_BUFFER_SIZE);
    UART_PeriClockControl(DISABLE);

    // 1, Config pins
    uint8_t psel_port = 0;

    uint32_t temp = 0;
    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL.TXD = temp;
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL.RXD = temp;

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL.TXD = temp;

        psel_port = 0;
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL.RXD = temp;
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


/*
 ********************************************************************************************
 * @fn              - uart_write_byte
 *
 * @brief           - Writes a single byte to the UART transmit data register.
 *
 * @param[in]       - ch: The byte to be transmitted.
 *
 * @return          - none
 *
 * @Note            - This function waits for the TXDRDY event to ensure readiness for transmission.
 *
 ********************************************************************************************
 */

void uart_write_byte(uint8_t ch)
{
    UART->TXD = (ch);
    event_pooling(&UART->EVENTS_TXDRDY);
}


/*
 ********************************************************************************************
 * @fn              - uart_read_byte
 *
 * @brief           - Reads a single byte from the UART receive data register.
 *
 * @return          - uint8_t: The byte received from the UART.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

uint8_t uart_read_byte(void)
{
    return (uint8_t)UART->RXD;
}

/*
 ********************************************************************************************
 * @fn              - uart_write
 *
 * @brief           - Writes a buffer of bytes to the UART transmit data register.
 *
 * @param[in]       - buffer: Pointer to the buffer containing the data to be transmitted.
 *
 * @param[in]       - Len: The number of bytes to write from the buffer.
 *
 * @return          - none
 *
 * @Note            - The function sequentially writes each byte from the buffer.
 *
 ********************************************************************************************
 */

void uart_write(uint8_t* buffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        uart_write_byte(buffer[i]);
    }
}

void uart_tx_start(void)
{
    UART->TASKS_STARTTX |= 1;
}

void uart_tx_stop(void)
{
    UART->TASKS_STOPTX |= 1;
}

void uart_rx_start(void)
{
    UART->TASKS_STARTRX |= 1;
}

void uart_rx_stop(void)
{
    UART->TASKS_STOPRX |= 1;
}


void uart_interruptConfig(uint32_t interrupts, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART->INTENSET |= interrupts;
    }else
    {
        UART->INTENCLR |= interrupts;
    }
}


bool uart_data_available(void)
{
    return !ring_buffer_empty(&rb);
}

uint32_t uart_rcv(uint8_t *data, const uint32_t length)
{
    if(length == 0)
	{
		return 0;
	}
	
	for(uint32_t bytes_read = 0; bytes_read < length; bytes_read++)
	{
		if(!ring_buffer_read(&rb, &data[bytes_read]))
		{
			return bytes_read;
		}
	}

	return length;
}

uint8_t uart_rcv_byte(void)
{
    uint8_t byte = 0;
	
	(void)uart_rcv(&byte, 1);

	return byte;
}



void UART_IRQHandler(void)
{
    if(UART_EVENT_RXDRDY)
    {
        event_clear(&UART_EVENT_RXDRDY);
        if(ring_buffer_write(&rb, uart_read_byte()))
		{
			// handle some error/failure
		}
    }
}