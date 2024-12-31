#include "driver_gpio.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    if(pGPIOHandle->pGPIOx == GPIOP0)
    {
        temp |= ((1 << 1) | (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0));
        GPIOP0_CNF->CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;

    }else if(pGPIOHandle->pGPIOx == GPIOP1)
    {
        temp |= ((1 << 1) | (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0));
        GPIOP1_CNF->CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;
    }
}

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