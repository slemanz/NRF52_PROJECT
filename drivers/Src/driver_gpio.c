#include "driver_gpio.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    if(pGPIOHandle->pGPIOx == GPIOP0)
    {
        temp |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0);
        GPIOP0_CNF->CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;

    }else if(pGPIOHandle->pGPIOx == GPIOP1)
    {
        temp |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0);
        GPIOP1_CNF->CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;
    }
}
