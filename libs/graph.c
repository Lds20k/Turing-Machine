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
    memset(edges, 0, quantity * sizeof(edge_t));
    
    node->edges = edges;
    return edges;
}

node_t* create_node(){
    node_t* node = malloc(sizeof(node_t));
    if(node == NULL)
        return NULL;
    memset(node, 0, sizeof(node_t));
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

void destroy_dl_list_side(node_t* root, bool side){
    node_t* node = root->edges[side].node;
    while (node != NULL)
    {   
        node_t* aux = node->edges[side].node;
        node->content_length = 0;
        node->edges_length = 0;
        free(node->content);
        free(node->edges);
        free(node);
        node = aux;
    }
}

void destroy_dl_list(node_t* root){
    destroy_dl_list_side(root, 0);
    destroy_dl_list_side(root, 1);
    free(root->content);
    free(root->edges);
    free(root);

    // while (node != NULL)
    // {   
    //     node_t* aux = node->edges->node;
    //     free(node->content);
    //     free(node->edges);
    //     free(node);
    //     node = aux;
    // }
}
