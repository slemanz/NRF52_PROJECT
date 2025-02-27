#ifndef CLI_H_
#define CLI_H_

#include <stdint.h>

// Function pointer type
typedef void(*function_t)(void);

// Structure to hold command information
typedef struct
{
    char const *name;
    function_t execute;
    char const *help;
}commandStruct_t;

void ProcessCommands(uint8_t ch);

#endif /* CLI_H_ */