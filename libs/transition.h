#ifndef TRANSITION_H
#define TRANSITION_H
#include "graph.h"

typedef enum DIRECTION{
    left  = 0,
    right = 1
} direction_e;

typedef struct STATE state_t;

// δ: Q X Γ ⇾ Q X Γ {left, right}
typedef struct TRANSITION
{
    // Q
    // Interface
    // Where does it point
    state_t* state;

    // Γ {left, right}
    char read_character;
    char write_character;
    direction_e direction;
} transition_t;


struct STATE
{
    // Edge control
    transition_t* transitions;
    uint64_t transitions_length;

    uint64_t state_number;
    
    // Content control
    bool* content;
    int64_t content_length;
};

transition_t* get_transition(const state_t* state, const char symbol);

#endif