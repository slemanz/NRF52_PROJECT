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


int main(void)
 {
    system_waitStable();
    system_init();


    system_waitStable();
    printf("Init system ok...\n\r");

    //storage_clean();
    storage_updateCount();
    storage_temperatureAppend();

    uint64_t start_time = ticks_get();
    while(1)
    {
        while(status_read() != STATUS_OK);
        command_update();


        // append every 10 minutes
        if((system_get_ticks() - start_time) >= 600000) 
        {
            storage_temperatureAppend();
            start_time = ticks_get();
        }
    }
}