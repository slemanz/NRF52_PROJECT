#ifndef INC_DRIVER_SYSTICK_H_
#define INC_DRIVER_SYSTICK_H_

#include "nrf52.h"

#define SYSTICK_LOAD_VAL            16000
#define CTRL_ENABLE                 (1U << 0)
#define CTRL_CLKSRC                 (1U << 2)
#define CTRL_COUNTFLAG              (1U << 16)
#define CTRL_TICKINT                (1U << 1)

#define ONE_SEC_LOAD                16000000

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq);
void systick_counter_enable(void);
void systick_interrupt_enable(void);

#endif
