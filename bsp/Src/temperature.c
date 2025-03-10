/*
 * =====================================================================
 *              File:           temperature.c
 *              Author:         William Sleman
 *              Description:    Temperature source file
 * =====================================================================
 */
#include "temperature.h"
#include "driver_twi.h"

// LM75A NXP

uint16_t temperature_get(void)
{
    uint8_t temperatureAddress = 0x4F;
    int8_t twi_read[2] = {0, 0};

    //TWI_MasterReceiveData(TWI1, 0x00, (uint8_t*)twi_read, 2, temperatureAddress);
    //uint16_t temperature_value = ((twi_read[0]*10) + ((twi_read[1] >> 7)*5));
    uint16_t temperature_value = ((twi_read[0] << 8 | twi_read[1]) >> 5) & 0x7FF;

    return temperature_value;
}