#include "nrf52.h"

// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

int main(void)
 {

    while (1)
    {
        delay_cycles(5000000);
    }
}