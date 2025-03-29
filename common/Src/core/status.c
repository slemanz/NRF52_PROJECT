#include "core/status.h"
#include "core/ticks.h"
#include "bsp/led_rgb.h"

static status_e status = STATUS_OK;
static status_e last_status = STATUS_OK;
static uint64_t time = 0;
static uint8_t toggle = 0;

static void status_ledUpdate();

static void status_ledUpdate()
{
    if(status == STATUS_OK)
    {
        last_status = STATUS_OK;
        if((ticks_get() - time) >= 500)
        {
            if(!toggle)
            {
                led_rgb_setColor(LED_GREEN);
                toggle = 1;
            }else
            {
                led_rgb_setColor(LED_NONE);
                toggle = 0;
            }
            time = ticks_get();
        }
    }else if((status == STATUS_FAULT) && (last_status == STATUS_OK))
    {
        last_status = STATUS_FAULT;
        led_rgb_setColor(LED_RED);
    }
}

void status_update(void)
{
    status_ledUpdate();
}

status_e status_read(void)
{
    status_update();
    return status;
}