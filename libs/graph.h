#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#include <stdint.h>

typedef struct NODE node_t;

typedef struct EDGE
{
    // Where does it point
    node_t* node;
} edge_t;

struct NODE
{
    // Edge control
    edge_t* edges;
    uint64_t edges_length;

    // Content control
    void* content;
    uint64_t content_length;
};

void printlist(const node_t* root);

/*
return root of the list
*/
node_t* create_dl_list(const void* content, const uint64_t content_length);

/*
return descendant node
*/
node_t* dl_list_add_node(const node_t* ancestor_or_descendant, const bool ancestor, const void* content, const uint64_t content_length);

/*
destruct all nodes of the list
*/
void destruct_dl_list(const node_t* root);

#endif