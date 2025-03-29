/*
 * =====================================================================
 *              File:           main.c
 *              Author:         William Sleman
 *              Description:    main source file
 * =====================================================================
 */
#include <stdio.h>
#include "init_app.h"
#include "core/cli.h"
#include "core/storage.h"
#include "core/ticks.h"
#include "core/status.h"

#include "driver_uart.h"

int main(void)
 {
    for(uint32_t i = 0; i < 1000000; i++) __asm("NOP"); // stable the system
    system_init();

    uint64_t start_time = ticks_get();

    for(uint32_t i = 0; i < 500000; i++) __asm("NOP"); // stable the system
    printf("Init system ok...\n\r");

    //storage_clean();
    storage_updateCount();
    storage_temperatureAppend();

    while(1)
    {
        while(status_read() != STATUS_OK);

        if(uart_data_available())
        {
                uint8_t ch = uart_rcv_byte();
                uart_write_byte(ch);
                ProcessCommands(ch);
        }

        // append every 10 minutes
        if((system_get_ticks() - start_time) >= 600000) 
        {
            storage_temperatureAppend();
            start_time = ticks_get();
        }
    }
}