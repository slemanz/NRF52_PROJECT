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



/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x00000000U
#define SRAM1_BASEADDR						0x20000000U


/*
 * Base addresses of peripherals
 */

#define GPIOP0_BASEADDR						(0x50000000U)
#define GPIOP1_BASEADDR						(0x50000300U)


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

/*
 * 	Peripheral definitions 
 */

#define GPIOP0			((GPIOP_RegDef_t*)(GPIOP0_BASEADDR + 0x504U))
#define GPIOP1			((GPIOP_RegDef_t*)(GPIOP1_BASEADDR + 0x504U))
#define GPIOP0_CNF		((GPIOP_CNF_t*)(GPIOP0_BASEADDR + 0x700U))
#define GPIOP1_CNF		((GPIOP_CNF_t*)(GPIOP1_BASEADDR + 0x700U))
/*
 * some generic macros
 */

#define ENABLE 						1
#define	DISABLE 					0
#define _SET						ENABLE
#define _RESET						DISABLE
#define GPIO_PIN_SET				_SET
#define GPIO_PIN_RESET				_RESET
#define FLAG_SET					_SET
#define FLAG_RESET					_RESET


/*
 * IRQ Priority levels
 */

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15

/*
 *		SCB
 */

#define SCB_BASE (0xE000ED00UL)
#define VTOR_OFFSET       MMIO32(SCB_BASE + 0x08U)



/*
 * Drivers includes
 */

#include "driver_gpio.h"

#endif