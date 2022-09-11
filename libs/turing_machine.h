#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H
#include "transition.h"

typedef struct TURING_MACHINE
{
    node_t* current_state;

    // Tape control
    node_t* tape;
} turing_machine_t;

turing_machine_t* create_machine(char* tape, node_t* initial_state);
node_t* start_processing(turing_machine_t* machine);

#endif