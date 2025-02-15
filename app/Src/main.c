// Author: William Sleman @ 2024/25
#include <stdio.h>
#include "nrf52.h"
#include "init_app.h"


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

    uint8_t sendSpi[] = "Testando";

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();
    uint8_t cnt = 0;

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system ok...\n\r");

    while (1)
    {   
       if(uart_data_available())
       {
            uart_write_byte(uart_rcv_byte());
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
        

        if((system_get_ticks() - start_time2) >= 2000) // send hello world
        {
            //printf("Working\n");
            GPIO_WriteToOutputPin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
            SPI_SendData(SPI0, sendSpi, (sizeof(sendSpi) - 1));
            GPIO_WriteToOutputPin(CS_PORT, CS_PIN, GPIO_PIN_SET);
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