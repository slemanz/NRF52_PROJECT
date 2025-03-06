/*
 * =====================================================================
 *              File:           temperature.c
 *              Author:         William Sleman
 *              Description:    Temperature source file
 * =====================================================================
 */
#include "temperature.h"
#include "driver_twi.h"

uint8_t temperature_get(void)
{
    uint8_t temperatureAddress = 0x4F;
    int8_t twi_read[2];

    TWI_MasterReceiveData(TWI1, 0x00, (uint8_t*)twi_read, 2, temperatureAddress);
    uint16_t temperature_value = (twi_read[0] << 8 | twi_read[1]) >> 5;

    return temperature_value;
}