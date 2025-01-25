// Author: William Sleman @ 2024/25
#include "nrf52.h"
#include "system.h"

const uint8_t leds_pin[] = {0, LED_BLUE_PIN, LED_RED_PIN, LED_GREEN_PIN};

int main(void)
 {
    system_init();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    uint8_t cnt = 0;

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);

    while (1)
    {   
        if((system_get_ticks() - start_time) >= 1000)
        {
            GPIO_WriteToOutputPin(GPIOP0, LED_GREEN_PIN, GPIO_PIN_SET);
            GPIO_WriteToOutputPin(GPIOP0, LED_RED_PIN, GPIO_PIN_SET);
            GPIO_WriteToOutputPin(GPIOP0, LED_BLUE_PIN, GPIO_PIN_SET);

            if(leds_pin[cnt] != 0) GPIO_WriteToOutputPin(GPIOP0, leds_pin[cnt], GPIO_PIN_RESET);

            cnt++;
            cnt &= 0x3;
            start_time = system_get_ticks();
        }
        

        if((system_get_ticks() - start_time2) >= 2000) // send hello world
        {
            uart_write_byte('T');
            start_time2 = system_get_ticks();
        }

        if(!GPIO_ReadFromInputPin(BUTTON1_PORT, BUTTON1_PIN))
        {
            GPIO_WriteToOutputPin(GPIOP0, LED1_EXT_PIN, GPIO_PIN_SET);
        }else
        {
            GPIO_WriteToOutputPin(GPIOP0, LED1_EXT_PIN, GPIO_PIN_RESET);
        }
    }
}