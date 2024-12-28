// Author: William Sleman @ 2024/25
#include "nrf52.h"

#define GPIO_P0_BASEADDR        0x50000000U

void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

// blinky P0.16
int main(void)
 {
    MMIO32(GPIO_P0_BASEADDR + 0x514) |= (1 << 16); // set as output
    MMIO32(GPIO_P0_BASEADDR + 0x504) &= ~(1 << 16); // set as low

    while (1)
    {
        delay_cycles(5000000);
    }
}