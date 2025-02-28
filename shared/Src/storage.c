#include "storage.h"
#include "nor.h"

static uint8_t buffer[STORAGE_BUFFER_SIZE];
static void _storage_copySector(uint32_t sector);

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