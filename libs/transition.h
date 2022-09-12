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
    transition_t* transition;
    int64_t transition_length;

    // Content control
    bool* content;
    int64_t content_length;
};

#endif