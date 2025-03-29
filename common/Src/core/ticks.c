#include "core/ticks.h"

static uint64_t ticks = 0;

void ticks_increment(void)
{
    ticks++;
}

uint64_t ticks_get(void)
{
    return ticks;
}