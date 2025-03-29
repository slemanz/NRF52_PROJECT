/*
 * =====================================================================
 *              File:           main.c
 *              Author:         William Sleman
 *              Description:    main source file
 * =====================================================================
 */
#include <stdio.h>
#include "nrf52.h"
#include "init_app.h"
#include "core/cli.h"
#include "core/storage.h"
#include "bsp/nor.h"
#include "bsp/temperature.h"
#include "bsp/led_rgb.h"

int main(void)
 {
    for(uint32_t i = 0; i < 1000000; i++) __asm("NOP"); // stable the system
    system_init();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system ok...\n\r");


    uint16_t temperature_value = 0;
    temperature_value = temperature_get();
    printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
    

    led_rgb_setColor(LED_RED);
    while(1);
    /*
    saadc_selectInp(SAADC_PSEL_AIN2);
    uint16_t adc_value = saadc_read();
    printf("Input: %d\n", (adc_value));
    */

    //storage_clean();
    storage_updateCount();
    uint8_t count_data = storage_getCount();
    printf("Count: %d\n", count_data);
    storage_temperatureAppend(temperature_get());


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
            GPIO_ToggleOutputPin(GPIOP0, LED_GREEN_PIN);
            start_time = system_get_ticks();
        }
        

        // append every 10 minutes
        if((system_get_ticks() - start_time2) >= 600000) 
        {
            temperature_value = temperature_get();
            //printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
            storage_temperatureAppend(temperature_value);
            start_time2 = system_get_ticks();
        }
    }
}