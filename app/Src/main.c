// Author: William Sleman @ 2024/25
#include <stdio.h>
#include "nrf52.h"
#include "init_app.h"
#include "nor.h"
#include "temperature.h"
#include "cli.h"


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

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system ok...\n\r");
    saadc_selectInp(SAADC_PSEL_AIN2);
    uint16_t adc_value = saadc_read();

    /*
    uint8_t bufferWrite[8] = {0x22, 0x44, 0x45, 0x46, 0x57};
    NOR_EraseSector(1);
    NOR_WriteSector(bufferWrite, 1, 0, 5);
    */

    uint8_t bufferNor[64];
    NOR_ReadSector(bufferNor, 1, 0, 32);
    
    printf("Pot adc value: %d\n", (adc_value));

    uint16_t temperature_value = 0;

    while (1)
    {   
       if(uart_data_available())
       {
            uint8_t ch = uart_rcv_byte();
            uart_write_byte(ch);
            ProcessCommands(ch);
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
        

        if((system_get_ticks() - start_time2) >= 120000) // send hello world
        {
            temperature_value = temperature_get();
            printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
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