// Author: William Sleman @ 2024/25
//#include "nrf52.h"
#include <stdint.h>

#define GPIO_P0_BASEADDR        0x50000000U
#define MMIO32(addr) (*(volatile uint32_t *)(addr))

// blue  -> P0.6
// green -> P0.24
// red   -> P0.16
const uint8_t leds_pin[] = {0, 6, 16, 24};

void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

// blinky P0.16
int main(void)
 {
    MMIO32(GPIO_P0_BASEADDR + 0x514) |= (1 << 6); // set as output
    MMIO32(GPIO_P0_BASEADDR + 0x514) |= (1 << 16); // set as output
    MMIO32(GPIO_P0_BASEADDR + 0x514) |= (1 << 24); // set as output

    uint8_t cnt = 0;
    while (1)
    {   
        MMIO32(GPIO_P0_BASEADDR + 0x504) |=  (1 << 6); // set as high
        MMIO32(GPIO_P0_BASEADDR + 0x504) |=  (1 << 16); // set as high
        MMIO32(GPIO_P0_BASEADDR + 0x504) |=  (1 << 24); // set as high
        if(leds_pin[cnt] != 0)
        {
            MMIO32(GPIO_P0_BASEADDR + 0x504) &= ~(1 << leds_pin[cnt]); // set as low
        }
        cnt++;
        cnt &= 0x3;
        delay_cycles(5000000);
    }
}