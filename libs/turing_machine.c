#include "turing_machine.h"

turing_machine_t* create_machine(char* tape, state_t* initial_state, state_t* accepted_state){
    turing_machine_t* machine = malloc(sizeof(turing_machine_t));
    machine->current_state  = initial_state;
    machine->initial_state  = initial_state;
    machine->accepted_state = accepted_state;

    int64_t i   = 0;
    node_t* aux = NULL;
    while (tape[i] != '\0')
    {
        aux = malloc(sizeof(node_t));

        // Melhorar para liberar espaços já alocados
        if(aux == NULL) return NULL;

        if(machine->tape_head == NULL)
            machine->tape_head = aux;
        
        aux->content        = &tape[i];
        aux->content_length = 1;
        aux->edge_length    = 1;
        aux->edge           = malloc(sizeof(edge_t));
        aux->edge->node     = NULL;
        aux                 = aux->edge->node;
        i++;
    }
    
    return machine;
}

bool start_processing(turing_machine_t* machine){
    while(machine->current_state != machine->accepted_state){
        state_t* aux = machine->current_state;
        char character = *((char*)machine->tape_head->content);
        for(int64_t i = 0; aux->transition->read_character == character; i++);

        machine->tape_head;
    }
    return true;
}