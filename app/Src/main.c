// Author: William Sleman @ 2024/25
#include <stdio.h>
#include "nrf52.h"
#include "init_app.h"
#include "nor.h"


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
    

    /*
    uint8_t bufferNor[64];
    uint8_t bufferWrite[8] = {0x55, 0x55, 0x66, 0x66, 0x55};
    NOR_EraseSector(0);
    NOR_WriteSector(bufferWrite, 0, 0, 5);

    NOR_ReadSector(bufferNor, 0, 0, 32);
    */


    // A0 -> P0.4
    volatile int16_t result = 0;

    SAADC_Handle_t SAADCHandle;
    SAADCHandle.CHANNEL = SAADC_CHANNEL_0;
    SAADCHandle.RESN    = SAADC_RES_BYPASS;
    SAADCHandle.RESP    = SAADC_RES_BYPASS;
    SAADCHandle.GAIN    = SAADC_GAIN_1_5;
    SAADCHandle.REFSEL  = SAADC_REFSEL_INTERNAL;
    SAADCHandle.MODE    = SAADC_MODE_SE;
    SAADCHandle.TACQ    = SAADC_TACQ_15US;

    SAADCHandle.PSELP   = SAADC_PSEL_AIN1;
    SAADCHandle.PSELN   = SAADC_PSEL_NC;

    saadc_setResolution(SAADC_RESOLUTION_12BIT);
    saadc_init(&SAADCHandle);
    //SAADC->OVERSAMPLE = SAADC_OVERSAMPLE_32X;

    SAADC->RESULT.MAXCNT = 1;
    SAADC->RESULT.PTR   = (uint32_t)&result;

    SAADC->ENABLER = 1;
    saadc_calibrate();

    for(uint32_t i = 0; i < 10; i++)
    {
        SAADC->TASKS_START = 1;
        while (SAADC->EVENTS_STARTED == 0);
        SAADC->EVENTS_STARTED = 0;

        // Do a SAADC sample, will put the result in the configured RAM buffer.
        SAADC->TASKS_SAMPLE = 1;
        while (SAADC->EVENTS_END == 0);
        SAADC->EVENTS_END = 0;

        uint16_t adc_value = result;
        printf("Result: %u\n", adc_value);
    }


    SAADC->EVENTS_END = 0;
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
        

        if((system_get_ticks() - start_time2) >= 3000) // send hello world
        {
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