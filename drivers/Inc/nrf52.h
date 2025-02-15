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
#define SPI0_BASEADDR 						(0x40000300UL)
#define SPI1_BASEADDR 						(0x40000400UL)
#define SPI2_BASEADDR 						(0x40002300UL)


#define RCC_BASEADDR						(AHB1PERIPH_BASE + 0x3800U)

/*******************peripheral register definition structures*******************/

typedef struct
{
	__vo uint32_t OUT;
	__vo uint32_t OUTSET;
	__vo uint32_t OUTCLR;
	__vo uint32_t IN;
	__vo uint32_t DIR;
	__vo uint32_t DIRSET;
	__vo uint32_t DIRCLR;
	__vo uint32_t LATCH;
	__vo uint32_t DETECTMODE;
}GPIOP_RegDef_t;


typedef struct
{
	__vo uint32_t CNF[32];
}GPIOP_CNF_t;

typedef struct
{
  __vo uint32_t CTRL; 
  __vo uint32_t LOAD; 
  __vo uint32_t VAL;  
  __vo uint32_t CALIB;
}SYSTICK_RegDef_t;

typedef struct
{
	__vo uint32_t STARTRX;
	__vo uint32_t STOPRX;
	__vo uint32_t STARTTX;
	__vo uint32_t STOPTX;
	__vo uint32_t RESERVERD[3];
	__vo uint32_t SUSPEND;
}UART_TASKS_t;

typedef struct
{
	__vo uint32_t CTS;
	__vo uint32_t NCTS;
	__vo uint32_t RXDRDY;
	__vo uint32_t RESERVERD0[4];
	__vo uint32_t TXDRDY;
	__vo uint32_t RESERVERD1;
	__vo uint32_t ERROR;
	__vo uint32_t RESERVERD2[7];
	__vo uint32_t RXTO;
}UART_EVENTS_t;

typedef struct
{
	__vo uint32_t SET;
	__vo uint32_t CLR;
}UART_INTEN_t;

typedef struct
{
	__vo uint32_t PENABLE;
	__vo uint32_t RESERVERD0;
	__vo uint32_t PSEL_RTS;
	__vo uint32_t PSEL_TXD;
	__vo uint32_t PSEL_CTS;
	__vo uint32_t PSEL_RXD;
	__vo uint32_t RXD;
	__vo uint32_t TXD;
	__vo uint32_t RESERVERD1;
	__vo uint32_t BAUDRATE;
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




/*
 * 	Peripheral definitions 
 */

#define SYSTICK         ((SYSTICK_RegDef_t*)SYSTICK_BASEADDR) 
#define GPIOP0			((GPIOP_RegDef_t*)(GPIOP0_BASEADDR + 0x504U))
#define GPIOP1			((GPIOP_RegDef_t*)(GPIOP1_BASEADDR + 0x504U))
#define GPIOP0_CNF		((GPIOP_CNF_t*)(GPIOP0_BASEADDR + 0x700U))
#define GPIOP1_CNF		((GPIOP_CNF_t*)(GPIOP1_BASEADDR + 0x700U))



#define UART_TASKS	 		((UART_TASKS_t*)(UART_BASEADDR + 0x0000U))
#define UART_EVENTS 		((UART_EVENTS_t*)(UART_BASEADDR + 0x0100U))
#define UART_INTEN			((UART_INTEN_t*)(UART_BASEADDR + 0x0304U))
#define UART_CONFIG			(*(__vo uint32_t*)(UART_BASEADDR + 0x056CU))
#define UART 				((UART_RegDef_t*)(UART_BASEADDR + 0x0500))

#define SPI0 				((SPI_RegDef_t*)	(SPI0_BASEADDR))
#define SPI1 				((SPI_RegDef_t*)	(SPI1_BASEADDR))
#define SPI2 				((SPI_RegDef_t*)	(SPI2_BASEADDR))


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