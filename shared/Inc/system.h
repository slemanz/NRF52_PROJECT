#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include "nrf52.h"

#define CPU_FREQ        (64000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

#define LED_BLUE_PIN        GPIO_PIN_NO_6
#define LED_GREEN_PIN       GPIO_PIN_NO_16
#define LED_RED_PIN         GPIO_PIN_NO_24
#define LED_BUILT_IN        GPIO_PIN_NO_13
#define LED1_EXT_PIN        GPIO_PIN_NO_5

#define BUTTON1_PORT           GPIOP1
#define BUTTON1_PIN            GPIO_PIN_NO_2

void system_init(void);

uint64_t system_get_ticks(void);

#endif
