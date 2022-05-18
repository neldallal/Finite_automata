/*
 * DFA.c
 *
 *  Created on: Jan 18, 2022
 *      Author 1: claudiacortell
 *      Author 2: Nadine Eldallal
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dfa.h"
#include "nfa.h"
#include "LinkedList.h"


/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates){
	DFA this = (DFA)malloc(sizeof(struct DFA));
	if (this == NULL) {
		return NULL;
	}
	this->numStates = nstates;

	//creating transitionTable
	this->transitionTable=(int**)malloc(nstates* sizeof(int*));
	for (int i = 0; i < nstates; i++){
		this->transitionTable[i] = (int*)malloc(128 * sizeof(int));
	}
	//initialize all entries to char 0, null
	for (int i = 0; i < nstates; i++){
		for (int j = 0; j < 128; j++){
			this->transitionTable[i][j] = 0;
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
 * Free the given DFA.
 */
//I think works?
void DFA_free(DFA dfa){
	for (int i = 0; i < dfa->numStates; i++){
		free(dfa->transitionTable[i]);
	}
	free(dfa->transitionTable);
	free(dfa->acceptingStates);
	free(dfa);
}

/**
 * Return the number of states in the given DFA.
 */
//WORKS
int DFA_get_size(DFA dfa){
	return dfa->numStates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
//WORKS
int DFA_get_transition(DFA dfa, int src, char sym){
	return (dfa->transitionTable[src][(int)sym])-48;
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
//WORKS
void DFA_set_transition(DFA dfa, int src, char sym, int dst){
	int dstToChar =dst+48;
	dfa->transitionTable[src][(int)sym] = dstToChar;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
//WORKS
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
	int dstToChar =dst+48;
	//iterate through the string
	int counter = 0;
	while (str[counter]!= 0){ //iterating through a char array, last element assumed to be 0(null)
		dfa->transitionTable[src][(int)str[counter]] = dstToChar;
		counter++;
	}
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
//WORKS
void DFA_set_transition_all(DFA dfa, int src, int dst){
	int dstToChar =dst+48;
	for (int i = 0; i < 128; i++){
		dfa->transitionTable[src][i] = dstToChar;
	}
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
//WORKS
void DFA_set_accepting(DFA dfa, int state, bool value){
	dfa->acceptingStates[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
//WORKS
bool DFA_get_accepting(DFA dfa, int state){
	return dfa->acceptingStates[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
//WORKS
bool DFA_execute(DFA dfa, char *input){
	int counter = 0;
	int currState = 0;
	bool isAccepted = DFA_get_accepting(dfa, currState);
	while (input[counter]!= 0){ //iterating through a char array, last element assumed to be 0(null)
		//if input is rejected, return false
		int a = dfa->transitionTable[currState][(int)input[counter]];
		char b = (char) a;
		if (b == 0){
			return false;
		}
		currState = DFA_get_transition(dfa, currState, input[counter]);
		isAccepted = DFA_get_accepting(dfa, currState);
		counter++;
	}
	return isAccepted;
}

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa){
	printf("Transition Table:\n");
	for (int i = 0; i < dfa->numStates; i++){
		printf("State %d:  ", i);
		for (int j = 0; j < 128; j++){
			printf("%d ",dfa->transitionTable[i][j]);
		}
		printf("\n");
	}
	printf("\nAccepting States:\n");
	for(int i = 0; i < dfa->numStates; i++){
		printf("State %d:  %d\n", i, dfa->acceptingStates[i]);
	}
	printf("\n");

}