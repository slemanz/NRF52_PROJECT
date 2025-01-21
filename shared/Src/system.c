#include "system.h"


static volatile uint64_t ticks = 0;


static void system_systickInit(void);


void system_init(void)
{
    system_systickInit();
}

uint64_t system_get_ticks(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}

static void system_systickInit(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();

}