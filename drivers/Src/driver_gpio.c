/*
 * ==========================================================================================
 *      File: driver_gpio.c
 *      Author: William Sleaman
 *
 *      Description:
 *      This source file contains the implementation of functions for configuring and 
 *      managing General Purpose Input/Output (GPIO) pins. It includes functions for 
 *      initializing pins, reading input states, writing to output pins, and toggling 
 *      output states. 
 *
 *      Note:
 * 		For details on the structures and function prototypes, see the header file: 
 * 		driver_gpio.h.
 * ==========================================================================================
 */
#include "driver_gpio.h"


/*
 ********************************************************************************************
 * @fn              - GPIO_Init
 *
 * @brief           - Initializes the specified GPIO pin based on the 
 *                    configuration settings provided in the GPIO_Handle_t 
 *                    structure.
 *
 * @param[in]       - pGPIOHandle: Pointer to a GPIO_Handle_t structure 
 *                    containing the GPIO port and pin configuration settings.
 *
 * @return          - none
 *
 * @Note            - If the pin is configured as an output, the output 
 *                    state is set to the state defined in the configuration.
 *
 ********************************************************************************************
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    temp |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPd << 2) | (pGPIOHandle->GPIO_PinConfig.GPIO_InpBuf << 1) |
            (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0); 

    pGPIOHandle->pGPIOx->PIN_CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinDir == GPIO_DIR_OUT)
    {
        GPIO_WriteToOutputPin(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinState);
    }
}


/*
 ********************************************************************************************
 * @fn              - GPIO_ReadFromInputPin
 *
 * @brief           - Reads the state of a specified input GPIO pin.
 *
 * @param[in]       - pGPIOx: Pointer to the GPIO port to read the pin from.
 *
 * @param[in]       - PinNumber: The number of the pin to read.
 *
 * @return          - uint8_t: Returns GPIO_PIN_SET if the pin is high, 
 *                    otherwise returns GPIO_PIN_RESET.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

uint8_t GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    if(pGPIOx->IN & (1 << PinNumber))
    {
        return GPIO_PIN_SET;
    }
    return GPIO_PIN_RESET;
}


/*
 ********************************************************************************************
 * @fn              - GPIO_WriteToOutputPin
 *
 * @brief           - Writes a value to a specified output GPIO pin, setting
 *                    or clearing the output state.
 *
 * @param[in]       - pGPIOx: Pointer to the GPIO port to write to.
 *
 * @param[in]       - PinNumber: The number of the pin to write to.
 *
 * @param[in]       - value: The value to write to the pin (GPIO_PIN_SET 
 *                    or GPIO_PIN_RESET).
 *
 * @return          - none
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
    if(value == GPIO_PIN_SET)
    {
        pGPIOx->OUT |= (1 << PinNumber);
    }else
    {
        pGPIOx->OUT &= ~(1 << PinNumber);
    }
}


/*
 ********************************************************************************************
 * @fn              - GPIO_ToggleOutputPin
 *
 * @brief           - Toggles the state of a specified output GPIO pin.
 *
 * @param[in]       - pGPIOx: Pointer to the GPIO port containing the pin.
 *
 * @param[in]       - PinNumber: The number of the pin to toggle.
 *
 * @return          - none
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
        pGPIOx->OUT ^= (1 << PinNumber);
}