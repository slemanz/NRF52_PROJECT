#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include "nrf52.h"

#define CPU_FREQ        (48000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

void system_init(void);

uint64_t system_get_ticks(void);

#endif
