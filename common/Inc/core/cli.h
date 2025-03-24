/*
 * =====================================================================
 *              File:           cli.c
 *              Author:         William Sleman
 *              Description:    Command Line Interface header file
 * =====================================================================
 */
#ifndef CLI_H_
#define CLI_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function pointer type
typedef void(*function_t)(void);

// Structure to hold command information
typedef struct
{
    char const *name;
    function_t execute;
    char const *help;
}commandStruct_t;

void ProcessCommands(uint8_t c);

#endif /* CLI_H_ */