#ifndef INC_STATUS_H_
#define INC_STATUS_H_

#include <stdint.h>
#include <stddef.h>

typedef enum {
    STATUS_OK,
    STATUS_FAULT
} status_e;

void status_update(void);
status_e status_read(void);

#endif /* INC_STATUS_H_ */