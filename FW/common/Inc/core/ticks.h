#ifndef INC_TICKS_H_
#define INC_TICKS_H_

#include <stdint.h>

void ticks_increment(void);
uint64_t ticks_get(void);

#endif /* INC_TICKS_H_ */