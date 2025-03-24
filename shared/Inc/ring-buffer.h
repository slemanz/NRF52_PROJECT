/*
 * =====================================================================
 *              File:           ring-buffer.h
 *              Author:         William Sleman
 *              Description:    ring-buffer header file
 * =====================================================================
 */
#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct ring_buffer_t
{
    uint8_t  *buffer;
    uint32_t mask; // the mask should be always 2^n
    uint32_t read_index;
    uint32_t write_index;
} ring_buffer_t;

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size);
bool ring_buffer_empty(ring_buffer_t *rb);
bool ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);
bool ring_buffer_write(ring_buffer_t *rb, uint8_t byte);

#endif /* INC_RING_BUFFER_H_ */