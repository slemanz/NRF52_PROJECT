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

#define SAADC_BASEADDR                  	(0x40007000UL)


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
} TWIM_PSEL_T;

typedef struct {
  __vo uint32_t  PTR;                               /*!< Data pointer                                                          */
  __vo uint32_t  MAXCNT;                            /*!< Maximum number of bytes in receive buffer                             */
  __vo uint32_t  AMOUNT;                            /*!< Number of bytes transferred in the last transaction                   */
  __vo uint32_t  LIST;                              /*!< EasyDMA list type                                                     */
} TWIM_RXD_Type;

typedef struct {
  __vo uint32_t  PTR;                               /*!< Data pointer                                                          */
  __vo uint32_t  MAXCNT;                            /*!< Maximum number of bytes in transmit buffer                            */
  __vo uint32_t  AMOUNT;                            /*!< Number of bytes transferred in the last transaction                   */
  __vo uint32_t  LIST;                              /*!< EasyDMA list type                                                     */
} TWIM_TXD_Type;

typedef struct {                                    /*!< TWI Structure                                                         */
	__vo uint32_t  TASKS_STARTRX;                     /*!< Start TWI receive sequence                                            */
	__vo uint32_t  RESERVED0;
	__vo uint32_t  TASKS_STARTTX;                     /*!< Start TWI transmit sequence                                           */
	__vo uint32_t  RESERVED1[2];
	__vo uint32_t  TASKS_STOP;                        /*!< Stop TWI transaction. Must be issued while the TWI master is
															not suspended.                                                        */
	__vo uint32_t  RESERVED2;
	__vo uint32_t  TASKS_SUSPEND;                     /*!< Suspend TWI transaction                                               */
	__vo uint32_t  TASKS_RESUME;                      /*!< Resume TWI transaction                                                */
	__vo uint32_t  RESERVED3[56];
	__vo uint32_t  EVENTS_STOPPED;                    /*!< TWI stopped                                                           */
	__vo uint32_t  RESERVED4[7];
	__vo uint32_t  EVENTS_ERROR;                      /*!< TWI error                                                             */
	__vo uint32_t  RESERVED5[8];
	__vo uint32_t  EVENTS_SUSPENDED;                  /*!< Last byte has been sent out after the SUSPEND task has been
															issued, TWI traffic is now suspended.                                 */
	__vo uint32_t  EVENTS_RXSTARTED;                  /*!< Receive sequence started                                              */
	__vo uint32_t  EVENTS_TXSTARTED;                  /*!< Transmit sequence started                                             */
	__vo uint32_t  RESERVED6[2];
	__vo uint32_t  EVENTS_LASTRX;                     /*!< Byte boundary, starting to receive the last byte                      */
	__vo uint32_t  EVENTS_LASTTX;                     /*!< Byte boundary, starting to transmit the last byte                     */
	__vo uint32_t  RESERVED7[39];
	__vo uint32_t  SHORTS;                            /*!< Shortcut register                                                     */
	__vo uint32_t  RESERVED8[63];
	__vo uint32_t  INTEN;                             /*!< Enable or disable interrupt                                           */
	__vo uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
	__vo uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
	__vo uint32_t  RESERVED9[110];
	__vo uint32_t  ERRORSRC;                          /*!< Error source                                                          */
	__vo uint32_t  RESERVED10[14];
	__vo uint32_t  ENABLE;                            /*!< Enable TWIM                                                           */
	__vo uint32_t  RESERVED11;
	TWIM_PSEL_T    PSEL;                              /*!< Unspecified                                                           */
	__vo uint32_t  RESERVED12[5];
	__vo uint32_t  FREQUENCY;                         /*!< TWI frequency. Accuracy depends on the HFCLK source selected.         */
	__vo uint32_t  RESERVED13[3];
	TWIM_RXD_Type RXD;                                /*!< RXD EasyDMA channel                                                   */
	TWIM_TXD_Type TXD;                                /*!< TXD EasyDMA channel                                                   */
	__vo uint32_t  RESERVED14[13];
	__vo uint32_t  ADDRESS;  
} TWI_RegDef_t;


typedef struct
{
	GPIOP_RegDef_t* port;
	uint8_t pin;
}PSEL_t;

typedef struct
{
	__vo uint32_t  LIMITH;                            /*!< Description cluster[n]: Last result is equal or above CH[n].LIMIT.HIGH */
	__vo uint32_t  LIMITL;                            /*!< Description cluster[n]: Last result is equal or below CH[n].LIMIT.LOW */
} SAADC_EVENTS_CH_T;

typedef struct 
{
	__vo uint32_t  PSELP;                             /*!< Description cluster[n]: Input positive pin selection for CH[n]        */
	__vo uint32_t  PSELN;                             /*!< Description cluster[n]: Input negative pin selection for CH[n]        */
	__vo uint32_t  CONFIG;                            /*!< Description cluster[n]: Input configuration for CH[n]                 */
	__vo uint32_t  LIMIT;                             /*!< Description cluster[n]: High/low limits for event monitoring			*/
} SAADC_CH_T;

typedef struct 
{
	__vo uint32_t  PTR;                               /*!< Data pointer                                                          */
	__vo uint32_t  MAXCNT;                            /*!< Maximum number of 16-bit samples to be written to output RAM		   */
	__vo uint32_t  AMOUNT;                            /*!< Number of 16-bit samples written to output RAM buffer since
                                                		the previous START task                                               	*/
} SAADC_RESULT_T;

typedef struct {                                    /*!< SAADC Structure                                                       */
	__vo uint32_t  TASKS_START;                       /*!< Starts the SAADC and prepares the result buffer in RAM                */
	__vo uint32_t  TASKS_SAMPLE;                      /*!< Takes one SAADC sample                                                */
	__vo uint32_t  TASKS_STOP;                        /*!< Stops the SAADC and terminates all on-going conversions               */
	__vo uint32_t  TASKS_CALIBRATEOFFSET;             /*!< Starts offset auto-calibration                                        */
	__vo uint32_t  RESERVED0[60];
	__vo uint32_t  EVENTS_STARTED;                    /*!< The SAADC has started                                                 */
	__vo uint32_t  EVENTS_END;                        /*!< The SAADC has filled up the result buffer                             */
	__vo uint32_t  EVENTS_DONE;                       /*!< A conversion task has been completed. Depending on the configuration,
                                                         multiple conversions might be needed for a result to be transferred
                                                          to RAM.                                                              */
	__vo uint32_t  EVENTS_RESULTDONE;                 /*!< Result ready for transfer to RAM                                      */
	__vo uint32_t  EVENTS_CALIBRATEDONE;              /*!< Calibration is complete                                               */
	__vo uint32_t  EVENTS_STOPPED;                    /*!< The SAADC has stopped                                                 */
	SAADC_EVENTS_CH_T EVENTS_CH[8];                /*!< Unspecified                                                           */
	__vo uint32_t  RESERVED1[106];
	__vo uint32_t  INTEN;                             /*!< Enable or disable interrupt                                           */
	__vo uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
	__vo uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
	__vo uint32_t  RESERVED2[61];
	__vo uint32_t  STATUS;                            /*!< Status                                                                */
	__vo uint32_t  RESERVED3[63];
	__vo uint32_t  ENABLER;                            /*!< Enable or disable SAADC                                               */
	__vo uint32_t  RESERVED4[3];
	SAADC_CH_T 	   CH[8];                              /*!< Unspecified                                                           */
	__vo uint32_t  RESERVED5[24];
	__vo uint32_t  RESOLUTION;                        /*!< Resolution configuration                                              */
	__vo uint32_t  OVERSAMPLE;                        /*!< Oversampling configuration. The RESOLUTION is applied before
                                                         averaging, thus for high OVERSAMPLE a higher RESOLUTION should
                                                          be used.                                                             */
  	__vo uint32_t  SAMPLERATE;                        /*!< Controls normal or continuous sample rate                             */
  	__vo uint32_t  RESERVED6[12];
	SAADC_RESULT_T RESULT;                         /*!< RESULT EasyDMA channel                                                */
} SAADC_RegDef_t;



#define PSEL_PIN           0
#define PSEL_PORT          5
#define PSEL_CONNECT       31

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

#define SAADC               ((SAADC_RegDef_t*) 	(SAADC_BASEADDR))



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
#include "driver_twi.h"
#include "driver_saadc.h"

#endif