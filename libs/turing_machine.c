#include "turing_machine.h"

turing_machine_t* create_machine(char* tape, node_t* initial_state){
    turing_machine_t* machine = malloc(sizeof(turing_machine_t));
    machine->current_state = initial_state;

    int64_t i = 0;
    node_t* aux = NULL;
    while (tape[i] != '\0')
    {
        aux = malloc(sizeof(node_t));

        // Melhorar para liberar espaços já alocados
        if(aux == NULL) return NULL;

        if(machine->tape == NULL)
            machine->tape = aux;
        
        aux->content = tape[i];
        aux->edge_length = 1;
        aux->edge = malloc(sizeof(edge_t));
        aux = aux->edge->direction;
        i++;
    }
    
    return machine;
}

node_t* start_processing(turing_machine_t* machine){
    return;
}