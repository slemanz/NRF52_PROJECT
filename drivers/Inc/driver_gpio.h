/*
 * ==========================================================================================
 * 		File: driver_gpio.h
 * 		Author: William Sleaman
 *
 * 		Description:
 * 		This header file defines structures and function prototypes for configuring and 
 * 		managing General Purpose Input/Output (GPIO) pins. It supports pin initialization, 
 * 		reading, writing, toggling, and configuring pin modes, pull-up/down settings.
 *
 * 		Note:
 * 		For function definitions and detailed API behavior, see the implementation file: 
 * 		driver_gpio.c.
 * ==========================================================================================
 */
#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include "nrf52.h"

/*
 ********************************************************************************************
 * @struct          - GPIO_PinConfig_t
 *
 * @brief           - Configuration structure for a GPIO pin, holding
 *                    settings such as pin number, direction, pull-up/pull-down
 *                    configuration, state, and input buffer status.
 *
 * @field           - GPIO_PinNumber: Specifies the GPIO pin number to configure,
 *                    defined by possible modes from @GPIO_PIN_NUMBER.
 *
 * @field           - GPIO_PinDir: Specifies the direction of the GPIO pin,
 *                    defined by possible modes from @GPIO_PIN_DIR.
 *
 * @field           - GPIO_PinPuPd: Specifies the pull-up or pull-down configuration,
 *                    defined by possible modes from @GPIO_PIN_PUPD.
 *
 * @field           - GPIO_PinState: Specifies the initial state of the pin,
 *                    defined by possible modes from @GPIO_PIN_STATE.
 *
 * @field           - GPIO_InpBuf: Specifies the status of the input buffer,
 *                    defined by possible modes from @GPIO_INP_BUF.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinDir;
	uint8_t GPIO_PinPuPd;
	uint8_t GPIO_PinState;
	uint8_t GPIO_InpBuf;
}GPIO_PinConfig_t;


/**************************************************************************
 * @struct          - GPIO_Handle_t
 *
 * @brief           - Handle structure for a GPIO pin, containing the base
 *                    address of the GPIO port and the configuration settings
 *                    for the associated pin.
 *
 * @field           - pGPIOx: Pointer to the base address of the GPIO port 
 *                    to which the pin belongs (e.g., PORTA, PORTB).
 *
 * @field           - GPIO_PinConfig: Holds the configuration settings for 
 *                    the GPIO pin, encapsulated in the GPIO_PinConfig_t structure.
 *
 * @Note            - none
 *
 **************************************************************************/

typedef struct
{
	GPIOP_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig; 
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

/*
 * @GPIO_PIN_STATE
 * GPIO pin possible states
 */

#define GPIO_PIN_SET				1
#define GPIO_PIN_RESET				0

/*
 * @GPIO_INPUT_BUFFER
 * GPIO pin possible states
 */

#define GPIO_INP_BUF_CONNECT		0
#define GPIO_INP_BUF_DISCONNECT		1

/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIOP_RegDef_t *pGPIOx); // not implemented yet


/*
 * Data read and write
 */
uint8_t  GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_DRIVER_GPIO_H_ */