#include <stdlib.h>

#include "transition.h"

transition_t* get_transition(const state_t* state, const char symbol){
    transition_t* transitions = state->transitions;
    uint64_t i;
    for(i = 0; transitions[i].read_character != symbol; i++)
        // Qreject
        if(i + 2 > state->transitions_length) return NULL;
    return &transitions[i];
}
