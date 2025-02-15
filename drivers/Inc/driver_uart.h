#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "nrf52.h"

/*
 * Configuration structure for UARTx peripheral
 */

typedef struct
{
	uint8_t Mode;
	uint32_t Baud;
}UART_Config_t;


/*
 * Handle structure for USARTx peripheral
 */

typedef struct{
	UART_Config_t UART_Config;
    PSEL_t Tx;
    PSEL_t Rx;
}UART_Handle_t;

/*
 *@UART_Mode
 *Possible options for USART_Mode
 */
#define UART_MODE_ONLY_TX		0
#define UART_MODE_ONLY_RX		1
#define UART_MODE_TXRX			2

/*
 *@UART_Baud
 *Possible options for USART_Baud
 */
#define UART_STD_BAUD_9600			0x00275000U
#define UART_STD_BAUD_115200		0x01D7E000U

/*
 * UART Registers 
 */

#define UART_PSEL_PIN           0
#define UART_PSEL_PORT          5
#define UART_PSEL_CONNECT       31

/*
 * UART Interrupts
 */

#define UART_INTERRUPT_CTS		(1 << 0)
#define UART_INTERRUPT_NCTS		(1 << 1)
#define UART_INTERRUPT_RXRDY	(1 << 2)
#define UART_INTERRUPT_TXRDY	(1 << 7)
#define UART_INTERRUPT_ERROR	(1 << 9)
#define UART_INTERRUPT_TXTO		(1 << 17)

/*
 * UART Events
 */

#define UART_IRQ_NO				2

#define UART_EVENT_RXDRDY		(UART->EVENTS_RXDRDY)

/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 * Peripheral Clock setup
 */
void UART_PeriClockControl(uint8_t EnorDi);

void UART_Init(UART_Handle_t* pUARTHandle);
void uart_write_byte(uint8_t ch);
void uart_write(uint8_t* buffer, uint32_t Len);
uint8_t uart_read_byte(void);

void uart_tx_start(void);
void uart_tx_stop(void);
void uart_rx_start(void);
void uart_rx_stop(void);

/*
 * Interrupts
 */
void uart_interruptConfig(uint32_t interrupts, uint8_t EnorDi);

/*
 * Other
 */
bool uart_data_available(void);
uint32_t uart_rcv(uint8_t *data, const uint32_t length);
uint8_t uart_rcv_byte(void);

#endif