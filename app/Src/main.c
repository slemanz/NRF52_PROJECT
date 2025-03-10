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
#include "nor.h"
#include "temperature.h"
#include "cli.h"
#include "storage.h"

int main(void)
 {
    for(uint32_t i = 0; i < 1000000; i++) __asm("NOP"); // stable the system
    system_init();

    uint64_t start_time = system_get_ticks();
    uint64_t start_time2 = system_get_ticks();

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_SET);
    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system ok...\n\r");

    uint8_t teste[10];


    TWI_MasterReceiveData(TWI1, teste, 4, 0x44);
    uint16_t temperature_value = (((teste[2] << 8) | (teste[3])) >> 2);
    printf("Temperatura: %d C\n", temperature_value);

    TWI_MasterReceiveData(TWI1, teste, 4, 0x44);
    printf("%d, %d, %d, %d \n", teste[0], teste[1], teste[2], teste[3]);
    printf("%d, %d, %X, %X \n", teste[0], teste[1], teste[2], teste[3]);
    
    temperature_value = (((teste[2] << 8) | (teste[3]) ) >> 2 );
    float temperatura = ((temperature_value/16383.0)*165.0 - 40.0)*10;
    temperature_value = (int16_t)temperatura;
    printf("Temperatura: %d C\n", temperature_value);
    

    /*
    saadc_selectInp(SAADC_PSEL_AIN2);
    uint16_t adc_value = saadc_read();
    printf("Input: %d\n", (adc_value));
    */

    //storage_clean();
    /*
    storage_updateCount();
    uint8_t count_data = storage_getCount();
    printf("Count: %d\n", count_data);
    while(1);
    storage_temperatureAppend(temperature_get());
    */


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
        

        if((system_get_ticks() - start_time2) >= 120000) 
        {
            TWI_MasterReceiveData(TWI1, teste, 4, 0x44);
            temperatura = ((temperature_value/16383.0)*165.0 - 40.0)*10;
            temperature_value = (int16_t)temperatura;
            printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
            //storage_temperatureAppend(temperature_get());
            start_time2 = system_get_ticks();
        }
    }
}