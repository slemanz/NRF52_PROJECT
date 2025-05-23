/*
 * =====================================================================
 *              File:           temperature.c
 *              Author:         William Sleman
 *              Description:    Temperature source file
 * =====================================================================
 */
#include "core/ticks.h"
#include "bsp/temperature.h"
#include "driver_twi.h"

// HS300x - RENESAS

uint16_t temperature_get(void)
{
    uint8_t temperatureAddress = 0x44;
    uint16_t temperature_value = 0;
    float temperature_float = 0;
    uint8_t twi_read[4];
    uint8_t twi_send[1] = {0x00};

    TWI_MasterSendData(TWI1, twi_send, 1, temperatureAddress);
    
    // 40ms wait time to get measure
    uint64_t start_time = ticks_get();
    while((ticks_get() - start_time) <= 40); 

    TWI_MasterReceiveData(TWI1, twi_read, 4, 0x44);
    temperature_value = (((twi_read[2] << 8) | (twi_read[3]) ) >> 2 );
    temperature_float = ((temperature_value/16383.0)*165.0 - 40.0)*10;
    temperature_value = (uint16_t)temperature_float;

    return temperature_value;
}