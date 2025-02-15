#ifndef INC_NRF52_H_
#define INC_NRF52_H_

// this header file describes the microcontroller
#include <stdint.h>
#include <stdbool.h>

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))


/*******************START: Processor Specific Details *************************/
/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ICER0 						((__vo uint32_t*)0xE000E180UL)
#define NVIC_ICER1 						((__vo uint32_t*)0xE000E184UL)
#define NVIC_ICER2 						((__vo uint32_t*)0xE000E188UL)
#define NVIC_ICER3 						((__vo uint32_t*)0xE000E18CUL)

/*
 * ARm Cortex Mx Processor Priority Regesiter Address Calculation
 */

#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400UL)
#define NO_PR_BITS_IMPLEMENTED 		4


/******************* Memory and Peripherals address *************************/
/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x00000000U
#define SRAM1_BASEADDR						0x20000000U


/*
 * Base addresses of peripherals
 */

#define SCS_BASE            				(0xE000E000UL)
#define SYSTICK_BASEADDR					(SCS_BASE + 0x0010UL)
#define GPIOP0_BASEADDR						(0x50000000UL)
#define GPIOP1_BASEADDR						(0x50000300UL)
#define UART_BASEADDR 						(0x40002000UL)
											
#define SPI0_BASEADDR 						(0x40003000UL)
#define SPI1_BASEADDR 						(0x40004000UL)
#define SPI2_BASEADDR 						(0x40023000UL)

#define TWI0_BASEADDR                   	(0x40003000UL)
#define TWI1_BASEADDR                   	(0x40004000UL)


#define RCC_BASEADDR						(AHB1PERIPH_BASE + 0x3800U)

/*******************peripheral register definition structures*******************/

typedef struct
{
  	__vo uint32_t  RESERVED0[321];
	__vo uint32_t  OUT;                               /*!< Write GPIO port                                                       */
	__vo uint32_t  OUTSET;                            /*!< Set individual bits in GPIO port                                      */
	__vo uint32_t  OUTCLR;                            /*!< Clear individual bits in GPIO port                                    */
	__vo uint32_t  IN;                                /*!< Read GPIO port                                                        */
	__vo uint32_t  DIR;                               /*!< Direction of GPIO pins                                                */
	__vo uint32_t  DIRSET;                            /*!< DIR set register                                                      */
	__vo uint32_t  DIRCLR;                            /*!< DIR clear register                                                    */
	__vo uint32_t  LATCH;                             /*!< Latch register indicating what GPIO pins that have met the criteria
                                                         set in the PIN_CNF[n].SENSE registers                                 */
	__vo uint32_t  DETECTMODE;                        /*!< Select between default DETECT signal behaviour and LDETECT mode       */
	__vo uint32_t  RESERVED1[118];
	__vo uint32_t  PIN_CNF[32];  
}GPIOP_RegDef_t;

typedef struct
{
	__vo uint32_t CTRL; 
	__vo uint32_t LOAD; 
	__vo uint32_t VAL;  
	__vo uint32_t CALIB;
}SYSTICK_RegDef_t;

typedef struct {
	__vo uint32_t  RTS;                               /*!< Pin select for RTS                                                    */
	__vo uint32_t  TXD;                               /*!< Pin select for TXD                                                    */
	__vo uint32_t  CTS;                               /*!< Pin select for CTS                                                    */
	__vo uint32_t  RXD;                               /*!< Pin select for RXD                                                    */
} UART_PSEL_T;


typedef struct
{
	__vo uint32_t  TASKS_STARTRX;                     /*!< Start UART receiver                                                   */
	__vo uint32_t  TASKS_STOPRX;                      /*!< Stop UART receiver                                                    */
	__vo uint32_t  TASKS_STARTTX;                     /*!< Start UART transmitter                                                */
	__vo uint32_t  TASKS_STOPTX;                      /*!< Stop UART transmitter                                                 */
	__vo uint32_t  RESERVED0[3];
	__vo uint32_t  TASKS_SUSPEND;                     /*!< Suspend UART                                                          */
	__vo uint32_t  RESERVED1[56];
	__vo uint32_t  EVENTS_CTS;                        /*!< CTS is activated (set low). Clear To Send.                            */
	__vo uint32_t  EVENTS_NCTS;                       /*!< CTS is deactivated (set high). Not Clear To Send.                     */
	__vo uint32_t  EVENTS_RXDRDY;                     /*!< Data received in RXD                                                  */
	__vo uint32_t  RESERVED2[4];
	__vo uint32_t  EVENTS_TXDRDY;                     /*!< Data sent from TXD                                                    */
	__vo uint32_t  RESERVED3;
	__vo uint32_t  EVENTS_ERROR;                      /*!< Error detected                                                        */
	__vo uint32_t  RESERVED4[7];
	__vo uint32_t  EVENTS_RXTO;                       /*!< Receiver timeout                                                      */
	__vo uint32_t  RESERVED5[46];
	__vo uint32_t  SHORTS;                            /*!< Shortcut register                                                     */
	__vo uint32_t  RESERVED6[64];
	__vo uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
	__vo uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
	__vo uint32_t  RESERVED7[93];
	__vo uint32_t  ERRORSRC;                          /*!< Error source                                                          */
	__vo uint32_t  RESERVED8[31];
	__vo uint32_t  ENABLER;                            /*!< Enable UART                                                           */
	__vo uint32_t  RESERVED9;
	UART_PSEL_T    PSEL;                              /*!< Unspecified                                                           */
	__vo uint32_t  RXD;                               /*!< RXD register                                                          */
	__vo uint32_t  TXD;                               /*!< TXD register                                                          */
	__vo uint32_t  RESERVED10;
	__vo uint32_t  BAUDRATE;                          /*!< Baud rate. Accuracy depends on the HFCLK source selected.             */
	__vo uint32_t  RESERVED11[17];
	__vo uint32_t  CONFIG; 
}UART_RegDef_t;

typedef struct {
	__vo uint32_t  SCK;                               /*!< Pin select for SCK                                                    */
	__vo uint32_t  MOSI;                              /*!< Pin select for MOSI signal                                            */
	__vo uint32_t  MISO;                              /*!< Pin select for MISO signal                                            */
} SPI_PSEL_T;

typedef struct {                                    /*!< SPI Structure                                                         */
  __vo uint32_t  RESERVED0[66];
  __vo uint32_t  EVENTS_READY;                      /*!< TXD byte sent and RXD byte received                                   */
  __vo uint32_t  RESERVED1[126];
  __vo uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
  __vo uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
  __vo uint32_t  RESERVED2[125];
  __vo uint32_t  ENABLER;                            /*!< Enable SPI                                                            */
  __vo uint32_t  RESERVED3;
  SPI_PSEL_T     PSEL;                               /*!< Unspecified                                                           */
  __vo uint32_t  RESERVED4;
  __vo uint32_t  RXD;                               /*!< RXD register                                                          */
  __vo uint32_t  TXD;                               /*!< TXD register                                                          */
  __vo uint32_t  RESERVED5;
  __vo uint32_t  FREQUENCY;                         /*!< SPI frequency. Accuracy depends on the HFCLK source selected.         */
  __vo uint32_t  RESERVED6[11];
  __vo uint32_t  CONFIG;                            /*!< Configuration register                                                */
} SPI_RegDef_t;

typedef struct {
	__vo uint32_t  SCL;                               /*!< Pin select for SCL                                                    */
	__vo uint32_t  SDA;                               /*!< Pin select for SDA                                                    */
} TWI_PSEL_T;

typedef struct {                                    /*!< TWI Structure                                                         */
	__vo uint32_t  TASKS_STARTRX;                     /*!< Start TWI receive sequence                                            */
	__vo uint32_t  RESERVED0;
	__vo uint32_t  TASKS_STARTTX;                     /*!< Start TWI transmit sequence                                           */
	__vo uint32_t  RESERVED1[2];
	__vo uint32_t  TASKS_STOP;                        /*!< Stop TWI transaction                                                  */
	__vo uint32_t  RESERVED2;
	__vo uint32_t  TASKS_SUSPEND;                     /*!< Suspend TWI transaction                                               */
	__vo uint32_t  TASKS_RESUME;                      /*!< Resume TWI transaction                                                */
	__vo uint32_t  RESERVED3[56];
	__vo uint32_t  EVENTS_STOPPED;                    /*!< TWI stopped                                                           */
	__vo uint32_t  EVENTS_RXDREADY;                   /*!< TWI RXD byte received                                                 */
	__vo uint32_t  RESERVED4[4];
	__vo uint32_t  EVENTS_TXDSENT;                    /*!< TWI TXD byte sent                                                     */
	__vo uint32_t  RESERVED5;
	__vo uint32_t  EVENTS_ERROR;                      /*!< TWI error                                                             */
	__vo uint32_t  RESERVED6[4];
	__vo uint32_t  EVENTS_BB;                         /*!< TWI byte boundary, generated before each byte that is sent or
														received                                                              */
	__vo uint32_t  RESERVED7[3];
	__vo uint32_t  EVENTS_SUSPENDED;                  /*!< TWI entered the suspended state                                       */
	__vo uint32_t  RESERVED8[45];
	__vo uint32_t  SHORTS;                            /*!< Shortcut register                                                     */
	__vo uint32_t  RESERVED9[64];
	__vo uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
	__vo uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
	__vo uint32_t  RESERVED10[110];
	__vo uint32_t  ERRORSRC;                          /*!< Error source                                                          */
	__vo uint32_t  RESERVED11[14];
	__vo uint32_t  ENABLE;                            /*!< Enable TWI                                                            */
	__vo uint32_t  RESERVED12;
	TWI_PSEL_T    PSEL;                               /*!< Unspecified                                                           */
	__vo uint32_t  RESERVED13[2];
	__vo uint32_t  RXD;                               /*!< RXD register                                                          */
	__vo uint32_t  TXD;                               /*!< TXD register                                                          */
	__vo uint32_t  RESERVED14;
	__vo uint32_t  FREQUENCY;                         /*!< TWI frequency. Accuracy depends on the HFCLK source selected.         */
	__vo uint32_t  RESERVED15[24];
	__vo uint32_t  ADDRESS;                           /*!< Address used in the TWI transfer                                      */
} TWI_RegDef_t;


typedef struct
{
	GPIOP_RegDef_t* port;
	uint8_t pin;
}PSEL_t;


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define SYSTICK         	((SYSTICK_RegDef_t*)SYSTICK_BASEADDR) 

#define GPIOP0				((GPIOP_RegDef_t*)	(GPIOP0_BASEADDR))
#define GPIOP1				((GPIOP_RegDef_t*)	(GPIOP1_BASEADDR))

#define UART 				((UART_RegDef_t*)	(UART_BASEADDR))

#define SPI0 				((SPI_RegDef_t*)	(SPI0_BASEADDR))
#define SPI1 				((SPI_RegDef_t*)	(SPI1_BASEADDR))
#define SPI2 				((SPI_RegDef_t*)	(SPI2_BASEADDR))

#define TWI0				((TWI_RegDef_t*)	(TWI0_BASEADDR))
#define TWI1				((TWI_RegDef_t*)	(TWI1_BASEADDR))


/*
 * 		Some generic macros
 */

#define ENABLE 						1
#define	DISABLE 					0
#define _SET						ENABLE
#define _RESET						DISABLE
#define FLAG_SET					_SET
#define FLAG_RESET					_RESET


/*
 * 		IRQ Priority levels
 */

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15

/*
 *		SCB
 */

#define SCB_BASE 			(0xE000ED00UL)
#define VTOR_OFFSET      	MMIO32(SCB_BASE + 0x08U)



/*
 * Drivers includes
 */

#include "driver_event.h"
#include "driver_interrupt.h"
#include "driver_gpio.h"
#include "driver_systick.h"
#include "driver_uart.h"
#include "driver_spi.h"

#endif