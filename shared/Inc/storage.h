#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdint.h>

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t hour;
    uint8_t minute;
}storage_date_t;


uint8_t storage_getCount(void);
void    storage_updateCount(uint8_t count);

void    storage_addDate(storage_date_t date);

#endif /* STORAGE_H_ */