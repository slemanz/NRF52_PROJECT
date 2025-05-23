#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include "nrf52.h"

void interrupt_config(uint8_t IRQNumber, uint8_t EnorDi);
void interrupt_priorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

#endif /* INC_DRIVER_INTERRUPT_H_ */
