#include <stdio.h>
#include <stdlib.h>

#include "turing_machine.h"


turing_machine_t* create_machine(char* tape, state_t* initial_state, state_t* accepted_state){
    turing_machine_t* machine = malloc(sizeof(turing_machine_t));
    machine->current_state  = initial_state;
    machine->initial_state  = initial_state;
    machine->accepted_state = accepted_state;
    machine->finite_control = NULL;

    int64_t i   = 0;
    node_t* aux = NULL;
    while (tape[i] != '\0' && tape[i] != '\n')
    {
        if(aux == NULL){
            char* symbol = malloc(sizeof(char));
            if(symbol == NULL) return NULL;
            *symbol = tape[i];

            aux = create_dl_list(symbol, 1);
            if(aux == NULL) return NULL;
            machine->finite_control = aux;
        }else{
            char* symbol = malloc(sizeof(char));
            if(symbol == NULL) return NULL;
            *symbol = tape[i];

            aux = dl_list_add_node(aux, right, symbol, 1);
            if(aux == NULL){
                destroy_dl_list(machine->finite_control);
                machine->finite_control = NULL;
                return NULL;
            }
        }
        i++;
    }
    machine->tape = machine->finite_control;
    return machine;
}


node_t* move_finite_control(node_t** finite_control, direction_e direction){
    if((*finite_control)->edges[direction].node != NULL){
        *finite_control = (*finite_control)->edges[direction].node;
        return *finite_control;
    } else {
        char* empty = malloc(sizeof(char));
        empty[0] = '-';
        (*finite_control)->edges[direction].node = dl_list_add_node(*finite_control, direction, empty, 1);
        return (*finite_control)->edges[direction].node;
    }
}


turing_machine_t* change_tape(turing_machine_t* machine, const char* tape) {
    destroy_dl_list(machine->tape);
    machine->finite_control = NULL;
    machine->current_state = machine->initial_state;

    int64_t i   = 0;
    node_t* aux = NULL;
    while (tape[i] != '\0' && tape[i] != '\n')
    {
        if(aux == NULL){
            char* symbol = malloc(sizeof(char));
            if(symbol == NULL) return NULL;
            *symbol = tape[i];

            aux = create_dl_list(symbol, 1);
            if(aux == NULL) return NULL;
            machine->finite_control = aux;
        }else{
            char* symbol = malloc(sizeof(char));
            if(symbol == NULL) return NULL;
            *symbol = tape[i];
            
            aux = dl_list_add_node(aux, right, symbol, 1);
            if(aux == NULL){
                destroy_dl_list(machine->finite_control);
                machine->finite_control = NULL;
                return NULL;
            }
        }
        i++;
    }
    machine->tape = machine->finite_control;
    return machine;
}


void destroy_machine(turing_machine_t* machine, const uint64_t states_lenght){
    destroy_dl_list(machine->tape);

    state_t* aux = machine->initial_state;
    for(uint64_t i = 0; i < states_lenght; i++){
        free(aux[i].transitions);
        aux[i].transitions_length = 0;
    }

    free(machine->initial_state);
    free(machine);
}


void print_machine_state(const turing_machine_t* machine){
    node_t* aux = machine->tape;
    while (aux != NULL)
    {
        if(aux == machine->finite_control)
            printf("(Q%li)=[%c] ", machine->current_state->state_number, *(char*)aux->content);
        else
            printf("%c ", *(char*)aux->content);
        
        aux = (aux->edges[1].node != NULL) ? aux->edges[1].node : NULL;
    }
    printf("\n");
}


bool start_processing(turing_machine_t* machine){
    while(machine->current_state != machine->accepted_state){
        // print_machine_state(machine);
        char symbol = *((char*)machine->finite_control->content);
        transition_t* transition = get_transition(machine->current_state, symbol);
        if(transition == NULL) return false;
        
        *((char*)machine->finite_control->content) = transition->write_character;
        move_finite_control(&machine->finite_control, transition->direction);
        machine->current_state = transition->state;
    }
    return machine->current_state == machine->accepted_state;
}
