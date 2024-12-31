// Author: William Sleman @ 2024/25
#include "nrf52.h"

#define GPIO_P0_BASEADDR        0x50000000U

void setup_gpio(void);

// blue  -> P0.6
// green -> P0.16
// red   -> P0.24
#define LED_BLUE_PIN        GPIO_PIN_NO_6
#define LED_GREEN_PIN       GPIO_PIN_NO_16
#define LED_RED_PIN         GPIO_PIN_NO_24

const uint8_t leds_pin[] = {0, LED_BLUE_PIN, LED_RED_PIN, LED_GREEN_PIN};

void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

int main(void)
 {
    setup_gpio();

    uint8_t cnt = 0;
    while (1)
    {   
        GPIO_WriteToOutputPin(GPIOP0, LED_GREEN_PIN, GPIO_PIN_SET);
        GPIO_WriteToOutputPin(GPIOP0, LED_RED_PIN, GPIO_PIN_SET);
        GPIO_WriteToOutputPin(GPIOP0, LED_BLUE_PIN, GPIO_PIN_SET);

        if(leds_pin[cnt] != 0)
        {
            GPIO_WriteToOutputPin(GPIOP0, leds_pin[cnt], GPIO_PIN_RESET);
        }
        cnt++;
        cnt &= 0x3;
        delay_cycles(5000000);
    }
}

void setup_gpio(void)
{
    GPIO_Handle_t ledPins;
    ledPins.pGPIOx = GPIOP0;
    ledPins.GPIO_PinConfig.GPIO_PinDir = GPIO_DIR_OUT;
    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_GREEN_PIN;

    GPIO_Init(&ledPins);

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_BLUE_PIN;
    GPIO_Init(&ledPins);

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_RED_PIN;
    GPIO_Init(&ledPins);
}