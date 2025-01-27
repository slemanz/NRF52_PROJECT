#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "nrf52.h"

void uart_init(void);
void uart_write_byte(uint8_t ch);
void uart_write(uint8_t* buffer, uint32_t Len);

void uart_tx_start(void);
void uart_tx_stop(void);
void uart_rx_start(void);
void uart_rx_stop(void);

#endif