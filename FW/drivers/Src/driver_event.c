#include "driver_event.h"

uint8_t event_read(__vo uint32_t* reg)
{
    return (*reg & (1 << 0));
}


void event_clear(__vo uint32_t* reg)
{
    *reg = 0;
}


void event_pooling(__vo uint32_t* reg)
{
    while(!(event_read(reg))); // wait event be generated
    event_clear(reg);
}