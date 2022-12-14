#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H
#include <stdbool.h>
#include "transition.h"

typedef struct TURING_MACHINE
{
    state_t* current_state;
    state_t* initial_state;
    state_t* accepted_state;

    // Tape control
    node_t* finite_control;
    node_t* tape;
} turing_machine_t;

turing_machine_t* create_machine(char* tape, state_t* initial_state, state_t* accepted_state);
turing_machine_t* change_tape(turing_machine_t* machine, const char* tape);
void destroy_machine(turing_machine_t* machine, const uint64_t states_lenght);
bool start_processing(turing_machine_t* machine);


#endif