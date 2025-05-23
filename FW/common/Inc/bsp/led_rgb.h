#ifndef INC_LED_RGB_H_
#define INC_LED_RGB_H_

#include <stdint.h>
#include <stddef.h>

typedef enum {
    LED_NONE,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_COUNT
} led_color_e;

void led_rgb_setColor(led_color_e color);

#endif /* INC_LED_RGB_H_ */