#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void printlist(const node_t* root){
    node_t* aux = (node_t*)root;
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    while(aux != NULL){
        printf("%s(%c)", aux->edges->node != NULL? "<-" : "" , *(char*)aux->content);
        aux = aux->edges_length > 1 ? aux->edges[1].node : NULL;
    }
    printf("\n");
}

edge_t* create_edges(node_t* node, const uint64_t quantity){
    edge_t* edges = NULL;
    node->edges_length = quantity;

    edges = malloc(quantity * sizeof(edge_t));
    if(edges == NULL) return NULL;
    for(uint64_t i = 0; i < quantity; i++)
        edges[i].node = NULL;
    
    node->edges = edges;
    return edges;
}

node_t* create_node(){
    node_t* node = malloc(sizeof(node_t));
    if(node == NULL)
        return NULL;
    
    node->edges = NULL;
    node->edges_length = 0;
    node->content = NULL;
    node->content_length = 0;
    return node;
}

node_t* create_dl_list(const void* content, const uint64_t content_length){
    node_t* aux = create_node();
    aux->content = (void*)content;
    aux->content_length = content_length;
    create_edges(aux, 2);
    if(aux->edges == NULL){
        free(aux);
        return NULL;
    }
    return aux;
}

node_t* dl_list_add_node(const node_t* ancestor_or_descendant, const bool ancestor, const void* content, const uint64_t content_length){
    node_t* aux = create_node();
    if(aux == NULL) return NULL;

    aux->content = (void*)content;
    aux->content_length = content_length;

    create_edges(aux, 2);
    if(aux->edges == NULL){
        free(aux);
        return NULL;
    }
    aux->edges[!ancestor].node = (node_t*)ancestor_or_descendant;
    ancestor_or_descendant->edges[ancestor].node = aux;

    return aux;
}

void destruct_dl_list(const node_t* root){
    node_t* node = (node_t*)root;
    while (node != NULL)
    {   
        node_t* aux = node->edges->node;
        free(node->content);
        free(node->edges);
        free(node);
        node = aux;
    }
}
