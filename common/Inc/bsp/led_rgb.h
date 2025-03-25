#ifndef INC_LED_RGB_H_
#define INC_LED_RGB_H_

#include <stdint.h>

typedef enum
{
    NONE,
    LED_RED,
    LED_GREEN,
    LED_BLUE
}led_color_e;

void led_rgb_setColor(led_color_e color);

#endif /* INC_LED_RGB_H_ */