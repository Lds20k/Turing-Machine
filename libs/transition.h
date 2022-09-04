#ifndef TRANSITION_H
#define TRANSITION_H
#include "graph.h"

enum DIRECTION{
    left  = 0,
    right = 1
};

typedef enum DIRECTION direction_t;

// δ: Q X Γ ⇾ Q X Γ {left, right}
struct TRANSITION
{
    // Q
    // Interface
    // Where does it point
    node_t* state;

    // Γ {left, right}
    char read_character;
    char write_character;
    direction_t direction;
};

typedef struct TRANSITION transition_t;

#endif