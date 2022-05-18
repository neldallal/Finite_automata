/*
 * nfa.c
 *
 *  Created on: Jan 20, 2022
 *      Author 1: claudiacortell
 *      Author 2: Nadine Eldallal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nfa.h"
#include "dfa.h"



/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates){
	NFA this = (NFA)malloc(sizeof(struct NFA));
	if (this == NULL) {
		return NULL;
	}
	this->numStates = nstates;

	//creating transitionTable
	this->transitionTable=(Set**)malloc(nstates* sizeof(Set*));	//(# of state) rows
	for (int i = 0; i < nstates; i++){
		this->transitionTable[i] = (Set*)malloc(128 * sizeof(Set));	//(128) columns, each one is a Set
	}

	//initialize all entries to a new Set (with nstates possible spots), starts as empty
	for (int i = 0; i < nstates; i++){
		for (int j = 0; j < 128; j++){
			this->transitionTable[i][j] = new_IntHashSet(nstates);
		}
	}

	//creating acceptingStates table
	this->acceptingStates=(bool*)malloc(nstates*sizeof(bool));
	for (int i = 0; i < nstates; i++){
		this->acceptingStates[i] = false;
	}

	return this;
}

/**
 * Free the given NFA.
 */
//I don't know or think this is the proper way to free a Set
void NFA_free(NFA nfa){
	for (int i = 0; i < nfa->numStates; i++){
		for (int j = 0; j <128; j++){
			IntHashSet_free(nfa->transitionTable[i][j]); //I think this is right?
		}
        free(nfa->transitionTable[i]);
	}
	free(nfa->transitionTable);
	free(nfa->acceptingStates);
	free(nfa);
}

/**
 * Return the number of states in the given NFA.
 */
//WORKS
int NFA_get_size(NFA nfa){
	return nfa->numStates;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
//WORKS
Set NFA_get_transitions(NFA nfa, int state, char sym){
	return (nfa->transitionTable[state][(int)sym]);
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
//WORKS
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
	IntHashSet_insert(nfa->transitionTable[src][(int)sym], dst);
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
//WORKS
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
	//iterate through the string
	int counter = 0;
	while (str[counter]!= 0){ //iterating through a char array, last element assumed to be 0(null)
		IntHashSet_insert(nfa->transitionTable[src][(int)str[counter]],dst);
		counter++;
	}
}

/**
 * Add a transition for the given NFA for each input symbol.
 */
//WORKS
void NFA_add_transition_all(NFA nfa, int src, int dst){
	for (int i = 0; i < 128; i++){
		IntHashSet_insert(nfa->transitionTable[src][i],dst);
	}
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
//WORKS
void NFA_set_accepting(NFA nfa, int state, bool value){
	nfa->acceptingStates[state] = value;
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
//WORKS
bool NFA_get_accepting(NFA nfa, int state){
	return nfa->acceptingStates[state];
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input){
	int counter = 0;
	int currState = 0;

	IntHashSet allStates = new_IntHashSet(nfa->numStates);
    IntHashSet x;

	IntHashSet_insert(allStates,0);

	while (input[counter]!=0) {
		IntHashSetIterator iterator = IntHashSet_iterator(allStates);
		x = new_IntHashSet(nfa->numStates);
		while (IntHashSetIterator_hasNext(iterator)) {
			currState = IntHashSetIterator_next(iterator);
			if (IntHashSet_isEmpty(nfa->transitionTable[currState][(int)input[counter]]) == true){
			} else{
				//receives a set of the next possible states, add it to x
				IntHashSet_union(x, NFA_get_transitions(nfa, currState, input[counter]));
			}
		}
		free(allStates);
		allStates = x;
		free(iterator);
		counter++;
	}

	bool isAccepted = false;
	//iterate through allStates, set isAccepted to true if a state in there is accepting
	IntHashSetIterator iterator2 = IntHashSet_iterator(allStates);
	int c = 0;
	while (IntHashSetIterator_hasNext(iterator2)) {
		c = IntHashSetIterator_next(iterator2);
		if (NFA_get_accepting(nfa, c)==true){
			isAccepted = true;
		}
	}
	free(iterator2);
	//Free hashsets
	IntHashSet_free(allStates);
	return isAccepted;
}


///**
// * Print the given NFA to System.out.
// */
//WORKS
void NFA_print(NFA nfa){

	printf("Transition Table:\n");
	for (int i = 0; i < nfa->numStates; i++){
		printf("State %d:  ", i);
		for (int j = 0; j < 128; j++){
			IntHashSet_print(nfa->transitionTable[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\nAcceping States:\n");
	for(int i = 0; i < nfa->numStates; i++){
		printf("State %d:  %d\n", i, nfa->acceptingStates[i]);
	}
	printf("\n");

}
