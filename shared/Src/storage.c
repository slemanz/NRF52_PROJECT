#include "storage.h"
#include "nor.h"
#include <stdio.h>

static uint8_t buffer[STORAGE_BUFFER_SIZE];
static void _storage_copySector(uint32_t sector);

static volatile uint32_t offset_temperature = 0;

static void _storage_copySector(uint32_t sector)
{
    NOR_EraseSector(STORAGE_SECTOR_COPY);

    uint32_t size = NOR_SIZE_SECTOR;
    uint32_t offset = 0;
    do
    {
        if(size >= STORAGE_BUFFER_SIZE)
        {
            NOR_WriteSector(buffer, STORAGE_SECTOR_COPY, offset, STORAGE_BUFFER_SIZE);
            size -= STORAGE_BUFFER_SIZE;
            offset += STORAGE_BUFFER_SIZE;
        }else
        {
            NOR_WriteSector(buffer, size, offset, STORAGE_BUFFER_SIZE);
            size = 0;
        }
    }while (size);
}

uint8_t storage_getCount(void)
{
    uint8_t count = 0;

    NOR_ReadSector(&count, STORAGE_SECTOR_INFO, 0, 1);

    return count;
}

void storage_updateCount(void)
{
    uint8_t count = storage_getCount() + 1;
    buffer[0] = count;

    _storage_copySector(0);
    NOR_EraseSector(STORAGE_SECTOR_INFO);
    NOR_WriteSector(buffer, STORAGE_SECTOR_INFO, 0, 1);
    
}

void storage_clean(void)
{
    uint8_t sector_count = storage_getCount();
    uint8_t count = 0;

    for(uint16_t i = 0; i <= sector_count; i++)
    {
        NOR_EraseSector(i);
    }
    NOR_WriteSector(&count, STORAGE_SECTOR_INFO, 0, 1);
}


void storage_temperatureAppend(uint16_t temperature_value)
{
    uint32_t sector_num = storage_getCount();
    if(sector_num == 0) return;

    uint16_t temp_value = temperature_value;
    uint8_t temp[3];
    temp[0] = 0xF5; // should be crc
    temp[1] = ((uint8_t*)&temp_value)[0];
    temp[2] = ((uint8_t*)&temp_value)[1];

    printf("append %ld\n", offset_temperature);
    if(offset_temperature == 0)
    {
        NOR_EraseSector(sector_num);
        printf("erased\n");
    }
    NOR_WriteSector(temp, sector_num, offset_temperature, 3);
    offset_temperature += 3;
}


void storage_temperatureExtract(void)
{
    printf("Extract Values\n");
    uint8_t temp[3];
    uint16_t temperature_value = 0;
    uint32_t offset_temp = 0;
    uint8_t count = storage_getCount();
    for(uint32_t i = 1; i <= count; i++)
    {
        printf("%ld:\n", i);
        NOR_ReadSector(temp, i, 0, 3);
        while(temp[0] == 0xF5)
        {
            ((uint8_t*)&temperature_value)[0] = temp[1];
            ((uint8_t*)&temperature_value)[1] = temp[2];

            printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
            offset_temp += 3;
            NOR_ReadSector(temp, i, offset_temp, 3);
        }
    }
}