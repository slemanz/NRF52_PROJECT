#include "bsp/led_rgb.h"
#include "driver_gpio.h"

#define LED_RGB_BLUE            GPIO_PIN_NO_6
#define LED_RGB_GREEN           GPIO_PIN_NO_16
#define LED_RGB_RED             GPIO_PIN_NO_24

static void led_setRed(void);
static void led_setGreen(void);
static void led_setBlue(void);
static void led_setNone(void);

static void led_setRed(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}

static void led_setGreen(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}
static void led_setBlue(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_RESET);
}

static void led_setNone(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}

static void (*led_functions[LED_COUNT])(void) = {
    led_setNone,            // NONE
    led_setRed,             // LED_RED
    led_setGreen,           // LED_GREEN
    led_setBlue             // LED_BLUE
};

void led_rgb_setColor(led_color_e color)
{
    if (led_functions[color] != NULL)
    {
            led_functions[color]();
    }
}