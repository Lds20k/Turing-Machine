#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H
#include "transition.h"

typedef struct TURING_MACHINE
{
    node_t* current_state;

    // Tape control
    void* tape;
    int64_t tape_length;
} turing_machine_t;



#endif