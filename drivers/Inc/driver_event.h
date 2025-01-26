#ifndef INC_DRIVER_EVENT_H_
#define INC_DRIVER_EVENT_H_

#include "nrf52.h"

uint8_t event_read(__vo uint32_t* reg);
void event_clear(__vo uint32_t* reg);
void event_pooling(__vo uint32_t* reg);

#endif /* INC_DRIVER_EVENT_H_ */
