#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SYMBOLS_SIZE 30 + 1 // for \'0'
#define NUMBER_OF_STATES_SIZE 2 + 1 // for \'0' - cause the max number of states is 50
#define NUMBER_OF_TRANSITION_SIZE 4 + 1 // for \'0' - cause the max number of transitions is 1500 (MAX_SYMBOLS X MAX_STATES) (30X50)
#define NUMBER_OF_WORDS_SIZE 4 + 1 // for \'0' - isnt defined so i chose the same size of int in x64 system
#define TRANSITION_SIZE 11+ 1 // for \'0' - cause can be '50 a x D 49'
#define WORD_MAX_SIZE 100 + 1 // for \'0'

int main(int argc, char const *argv[]){
    
    FILE * fpointer = fopen("TM_definition.txt", "r");

    char input_symbols[INPUT_SYMBOLS_SIZE]; 
    fgets(input_symbols, INPUT_SYMBOLS_SIZE, fpointer);
    printf("Input symbols: %s", input_symbols);

    char number_of_states[NUMBER_OF_STATES_SIZE]; 
    fgets(number_of_states, NUMBER_OF_STATES_SIZE, fpointer);
    int num_states = atoi(number_of_states);
    printf("Number of states: %d\n", num_states);
    printf("Initial state: 1\n");
    printf("Final state: %d\n", num_states);

    char number_of_transitions[NUMBER_OF_TRANSITION_SIZE]; 
    fgets(number_of_transitions, NUMBER_OF_TRANSITION_SIZE, fpointer);
    int num_transitions;
    num_transitions = atoi(number_of_transitions);
    printf("Number of transitions under: %d\n", num_transitions);

    // Size 11 due to maximum transitions is 50
    // So 9 + 2 in string has 2 state positions
    char transitions[50][11];
    for(int i = 0; i < num_transitions; i++){
        char * pointer = &transitions[i][0];
        fgets(pointer, 11, fpointer);
        printf("%s", pointer);
    }

    char number_of_words[4]; 
    fgets(number_of_words, 4, fpointer);
    int num_words = atoi(number_of_words);
    printf("Number of words under: %d\n", num_words);

    char words[10][WORD_MAX_SIZE];
    for(int i = 0; i < num_words; i++){
        char * pointer = &words[i][0];
        fgets(pointer, WORD_MAX_SIZE, fpointer);
        printf("%s", pointer);
    }

    fclose(fpointer);

    return 0;
}
