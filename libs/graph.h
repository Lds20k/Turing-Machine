#ifndef GRAPH_H
#define GRAPH_H
#include <stdint.h>

typedef struct NODE node_t;

typedef struct EDGE
{
    // Where does it point
    node_t* direction;
} edge_t;

struct NODE
{
    // Edge control
    edge_t* edge;
    int64_t edge_length;

    // Content control
    void* content;
    int64_t content_length;
};

node_t add_node(node_t );

#endif