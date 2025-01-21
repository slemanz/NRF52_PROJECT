#include "system.h"


static volatile uint64_t ticks = 0;


static void system_systickInit(void);
static void system_setupGpio(void);


void system_init(void)
{
    system_systickInit();
    system_setupGpio();
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

static void system_setupGpio(void)
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

    ledPins.GPIO_PinConfig.GPIO_PinNumber = LED_BUILT_IN;
    GPIO_Init(&ledPins);

    // init all in HIGH
    GPIO_WriteToOutputPin(GPIOP0, LED_GREEN_PIN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RED_PIN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_BLUE_PIN, GPIO_PIN_SET);

    GPIO_WriteToOutputPin(GPIOP0, LED_BUILT_IN, GPIO_PIN_RESET);
}