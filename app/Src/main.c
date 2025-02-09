// Author: William Sleman @ 2024/25
#include <stdio.h>
#include "nrf52.h"
#include "system.h"

const uint8_t leds_pin[] = {0, LED_BLUE_PIN, LED_RED_PIN, LED_GREEN_PIN};

// retarget printf
extern int __io_putchar(int ch)
{
    uart_write_byte((uint8_t)ch);
    return ch;
}

uint8_t rcv = 0;

int main(void)
 {
    system_init();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    uint8_t cnt = 0;

    *NVIC_ISER0 |= ( 1 << 2);

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 10000; i++); // stable the system
    printf("Init system\n\r");
    
    event_clear(&UART_EVENTS->RXDRDY);


    while (1)
    {   
        /*
        if(event_read(&UART_EVENTS->RXDRDY))
        {
            event_clear(&UART_EVENTS->RXDRDY);
            uint8_t temp = UART->RXD;
            printf("Opa\n");
            (void)temp;
        }*/

       if(rcv != 0)
       {
            printf("%c", rcv);
            rcv = 0;
       }

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
        

        if((system_get_ticks() - start_time2) >= 30000) // send hello world
        {
            printf("Working\n");
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


void ID2_IRQHandler(void)
{
    if(UART_EVENTS->RXDRDY)
    {
        event_clear(&UART_EVENTS->RXDRDY);
        rcv = UART->RXD;
    }
}