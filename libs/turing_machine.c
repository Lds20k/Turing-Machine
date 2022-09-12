#include <stdio.h>
#include <stdlib.h>

#include "turing_machine.h"

turing_machine_t* create_machine(char* tape, state_t* initial_state, state_t* accepted_state){
    turing_machine_t* machine = malloc(sizeof(turing_machine_t));
    machine->current_state  = initial_state;
    machine->initial_state  = initial_state;
    machine->accepted_state = accepted_state;
    machine->tape_head = NULL;

    int64_t i   = 0;
    node_t* aux = NULL;
    while (tape[i] != '\0' && tape[i] != '\n')
    {
        if(aux == NULL){
            aux = create_dl_list(&tape[i], 1);
            if(aux == NULL) return NULL;
            machine->tape_head = aux;
        }else{
            aux = dl_list_add_node(aux, right, &tape[i], 1);
            if(aux == NULL){
                destruct_dl_list(machine->tape_head);
                machine->tape_head = NULL;
                return NULL;
            }
        }
        i++;
    }
    machine->tape = machine->tape_head;
    return machine;
}

node_t* move_tape_head(node_t** tape_head, direction_e direction){
    if((*tape_head)->edges[direction].node != NULL){
        *tape_head = (*tape_head)->edges[direction].node;
        return *tape_head;
    } else {
        char* empty = malloc(sizeof(char));
        empty[0] = '-';
        (*tape_head)->edges[direction].node = dl_list_add_node(*tape_head, direction, empty, 1);
        return (*tape_head)->edges[direction].node;
    }
}

void print_machine_state(const turing_machine_t* machine){
    node_t* aux = machine->tape;
    while (aux != NULL)
    {
        if(aux == machine->tape_head)
            printf("(Q%li)=[%c] ", machine->current_state->state_number, *(char*)aux->content);
        else
            printf("%c ", *(char*)aux->content);
        
        aux = (aux->edges[1].node != NULL) ? aux->edges[1].node : NULL;
    }
    printf("\n");
}

bool start_processing(turing_machine_t* machine){
    while(machine->current_state != machine->accepted_state){
        print_machine_state(machine);
        char symbol = *((char*)machine->tape_head->content);
        transition_t* transition = get_transition(machine->current_state, symbol);
        if(transition == NULL) return false;
        
        *((char*)machine->tape_head->content) = transition->write_character;
        move_tape_head(&machine->tape_head, transition->direction);
        machine->current_state = transition->state;
    }
    return machine->current_state == machine->accepted_state;
}