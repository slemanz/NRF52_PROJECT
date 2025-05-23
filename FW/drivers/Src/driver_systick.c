#include "driver_systick.h"

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq)
{
    // reload with number of clocks persecond
    SYSTICK->LOAD   = (cpu_freq/freq) - 1;

    // clear systick current value register
    SYSTICK->VAL = 0;
}

void systick_counter_enable(void)
{
    // Enable systick and select internal clk src
    SYSTICK->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
}

void systick_interrupt_enable(void)
{
    // enable systick interrupt
    SYSTICK->CTRL |= CTRL_TICKINT;
}