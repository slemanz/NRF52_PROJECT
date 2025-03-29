/*
 * =====================================================================
 *              File:           storage.c
 *              Author:         William Sleman
 *              Description:    storage header file
 * =====================================================================
 */
#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdint.h>

#define STORAGE_SECTOR_INFO                 0
#define STORAGE_SECTOR_COPY                 512
#define STORAGE_BUFFER_SIZE                 64

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t hour;
    uint8_t minute;
}storage_date_t;


uint8_t storage_getCount(void);
void    storage_updateCount(void);

void storage_clean(void);
void storage_temperatureAppend(void);
void storage_temperatureExtract(void);

#endif /* STORAGE_H_ */