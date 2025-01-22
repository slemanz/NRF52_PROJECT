#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "nrf52.h"

/*
 * This is a configuration structure for a GPIO pin
 */

typedef struct
{
	uint8_t GPIO_PinNumber; 	/*!< possible modes from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinDir;		/*!< possible modes from @GPIO_PIN_DIR >*/
	uint8_t GPIO_PinPuPd;		/*!< possible modes from @GPIO_PIN_PUPD >*/
}GPIO_PinConfig_t;


/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct
{
	GPIOP_RegDef_t *pGPIOx; /* hold the base address of the GPIO port which the pin belongs */
	GPIO_PinConfig_t GPIO_PinConfig; /* this holds GPIO pin configuration settings */
}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBER
 * GPIO pin possible number
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15
#define GPIO_PIN_NO_16		16
#define GPIO_PIN_NO_17		17
#define GPIO_PIN_NO_18		18
#define GPIO_PIN_NO_19		19
#define GPIO_PIN_NO_20		20
#define GPIO_PIN_NO_21		21
#define GPIO_PIN_NO_22		22
#define GPIO_PIN_NO_23		23
#define GPIO_PIN_NO_24		24
#define GPIO_PIN_NO_25		25
#define GPIO_PIN_NO_26		26
#define GPIO_PIN_NO_27		27
#define GPIO_PIN_NO_28		28
#define GPIO_PIN_NO_29		29
#define GPIO_PIN_NO_30		30
#define GPIO_PIN_NO_31		31


/*
 * @GPIO_PIN_DIR
 * GPIO pin possible modes
 */

#define GPIO_DIR_IN 		0
#define GPIO_DIR_OUT 		1

/*
 * @GPIO_PIN_PUPD
 * GPIO pin possible modes
 */

#define GPIO_PIN_NO_PUPD	0
#define GPIO_PIN_PD 		1
#define GPIO_PIN_PU 		3

/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIOP_RegDef_t *pGPIOx);


/*
 * Data read and write
 */
uint8_t  GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_GPIO_H_ */