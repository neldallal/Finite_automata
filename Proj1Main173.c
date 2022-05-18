/*
 * Proj1Main173.c
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
#include "NFA_to_DFA.h"
#include "LinkedList.h"
#include "IntHashSet.h"


bool DFA_run(DFA dfa, char* input);
void DFA_repl(DFA dfa);
DFA DFA_for_contains_automaton();
DFA DFA_for_ends_with_ed();
DFA DFA_for_contains_two_2s();
DFA DFA_for_odd_num_0_1();
DFA DFA_for_three_c();

bool NFA_run(NFA nfa, char* input);
void NFA_repl(NFA nfa);
NFA NFA_for_ending_in_head();
NFA NFA_for_contains_zz();
NFA NFA_for_not_woodpecker_anagram();
NFA NFA_for_ends_in_est();

int main(int argc, char *argv[]) {
	printf("Hello! Claudia and Nadine's CSC173 Project 1\n\n");
	//DFA STUFF

	printf("1. DFA for exactly the string \"automaton\":\n");
	DFA d1 = DFA_for_contains_automaton();
	DFA_repl(d1);
	DFA_free(d1);


	printf("\n2. DFA for strings ending in \"ed\":\n");
	DFA d2 = DFA_for_ends_with_ed();
	DFA_repl(d2);
	DFA_free(d2);


	printf("\n3. DFA for strings with exactly two 2's:\n");
	DFA d3 =DFA_for_contains_two_2s();
	DFA_repl(d3);
	DFA_free(d3);


	printf("\n4. DFA for binary input with odd number of both 0's and 1's:\n");
	DFA d4 =DFA_for_odd_num_0_1();;
	DFA_repl(d4);
	DFA_free(d4);


	printf("\n5. DFA for strings with at least 3 c's:\n");
	DFA d5 = DFA_for_three_c();
	DFA_repl(d5);
	DFA_free(d5);


	//NFA STUFF
	printf("\n\n1. NFA for strings ending in \"head\":\n");
	NFA n1 = NFA_for_ending_in_head();
	NFA_repl(n1);
	NFA_free(n1);

	printf("\n2. NFA for strings containing \"zz\":\n");
	NFA n2 = NFA_for_contains_zz();
	NFA_repl(n2);
	NFA_free(n2);

	printf("\n3. NFA for are not anagrams of \"woodpecker\":\n");
	NFA n3 = NFA_for_not_woodpecker_anagram();
	NFA_repl(n3);
	NFA_free(n3);

	printf("\n4. NFA for strings ending in \"est\":\n");
	NFA n4 = NFA_for_ends_in_est();
	NFA_repl(n4);
	NFA_free(n4);

	//NFA TO DFA STUFF
	printf("\n\nConverting NFA to DFA, running as a DFA:\n");

    printf("\n\nNFA to DFA - ENDS IN HEAD");
    NFA n6 = NFA_for_ending_in_head();
    DFA d6 = NFA_to_DFA(n6);
    printf("\nThis dfa has %d states.\n", DFA_get_size(d6));
    NFA_free(n6);
    DFA_repl(d6);
    DFA_free(d6);

    printf("\n\n NFA to DFA - CONTAINS ZZ\n");
    NFA n7 = NFA_for_contains_zz();
    DFA d7 = NFA_to_DFA(n7);
    printf("\nThis dfa has %d states.\n", DFA_get_size(d7));
    NFA_free(n7);
    DFA_repl(d7);
    DFA_free(d7);

    /*printf("\n\n NFA to DFA - NOT ANAGRAM OF WOODPECKER\n");
    NFA n8 = NFA_for_not_woodpecker_anagram();
    DFA d8 = NFA_to_DFA(n8);
    printf("\nThis dfa has %d states.\n", DFA_get_size(d8));
    DFA_repl(d8);
    DFA_free(d8);*/

}


bool DFA_run(DFA dfa, char* input){
	return DFA_execute(dfa, input);
}

//WORKS
void DFA_repl(DFA dfa){
	char* input = (char*) malloc(127*sizeof(char));
	do {
		printf("Enter an input (\"q\" to quit):");
		scanf("%s",input);
		if (input[0]!='q'||input[1]!=0){
			//DFA_print(dfa);
			bool d = DFA_execute(dfa,input);
			if (d == true) {
				printf("Input \"%s\" is accepted.\n", input);
			}
			else {
				printf("Input \"%s\" is NOT accepted.\n", input);
			}
		}
	} while(input[0] != 'q'||input[1]!=0);
    free(input);
	return;

}

//DFA 1 - done
DFA DFA_for_contains_automaton(){
	DFA this = new_DFA(11);
	DFA_set_accepting(this, 9, true);

	DFA_set_transition_all(this, 0, 10);
	DFA_set_transition(this, 0, 'a', 1);

	DFA_set_transition_all(this, 1, 10);
	DFA_set_transition(this, 1, 'u', 2);

	DFA_set_transition_all(this, 2, 10);
	DFA_set_transition(this, 2, 't', 3);

	DFA_set_transition_all(this, 3, 10);
	DFA_set_transition(this, 3, 'o', 4);

	DFA_set_transition_all(this, 4, 10);
	DFA_set_transition(this, 4, 'm', 5);

	DFA_set_transition_all(this, 5, 10);
	DFA_set_transition(this, 5, 'a', 6);

	DFA_set_transition_all(this, 6, 10);
	DFA_set_transition(this, 6, 't', 7);

	DFA_set_transition_all(this, 7, 10);
	DFA_set_transition(this, 7, 'o', 8);

	DFA_set_transition_all(this, 8, 10);
	DFA_set_transition(this, 8, 'n', 9);

	DFA_set_transition_all(this, 9, 10);

	DFA_set_transition_all(this,10,10);

	return this;
}

//DFA 2 - done
DFA DFA_for_ends_with_ed(){
	DFA this = new_DFA(3);
	DFA_set_accepting(this, 2, true);

	DFA_set_transition_all(this, 0, 0);
	DFA_set_transition(this, 0, 'e', 1);

	DFA_set_transition_all(this, 1, 0);
	DFA_set_transition(this, 1, 'e', 1);
	DFA_set_transition(this, 1, 'd', 2);

	DFA_set_transition_all(this, 2, 0);
	DFA_set_transition(this, 2, 'e', 1);
	return this;
}

//DFA 3 - done
DFA DFA_for_contains_two_2s(){
	DFA this = new_DFA(4);
	DFA_set_accepting(this, 2, true);

	DFA_set_transition_all(this, 0, 0);
	DFA_set_transition(this, 0, '2', 1);

	DFA_set_transition_all(this, 1, 1);
	DFA_set_transition(this, 1, '2', 2);

	DFA_set_transition_all(this, 2, 2);
	DFA_set_transition(this, 2, '2', 3);

	DFA_set_transition_all(this, 3, 3);

	return this;
}

//DFA 4 - done
DFA DFA_for_odd_num_0_1(){
	DFA this = new_DFA(4);
	DFA_set_accepting(this, 3, true);

	DFA_set_transition(this, 0, '0', 2);
	DFA_set_transition(this, 0, '1', 1);

	DFA_set_transition(this, 1, '0', 3);
	DFA_set_transition(this, 1, '1', 0);

	DFA_set_transition(this, 2, '0', 0);
	DFA_set_transition(this, 2, '1', 3);

	DFA_set_transition(this, 3, '0', 1);
	DFA_set_transition(this, 3, '1', 2);

	return this;
}

//DFA 5 - done
DFA DFA_for_three_c(){
	DFA this = new_DFA(4);
	DFA_set_accepting(this, 3, true);

	DFA_set_transition_all(this, 0, 0);
	DFA_set_transition(this, 0, 'c', 1);

	DFA_set_transition_all(this, 1, 1);
	DFA_set_transition(this, 1, 'c', 2);

	DFA_set_transition_all(this, 2, 2);
	DFA_set_transition(this, 2, 'c', 3);

	DFA_set_transition_all(this, 3, 3);

	return this;
}



bool NFA_run(NFA nfa, char* input){
	return true; //CHANGE LATER
}

//copied from DFA_repl
void NFA_repl(NFA nfa){
	char* input = (char*) malloc(127*sizeof(char));
	do {
		printf("Enter an input (\"q\" to quit):");
		scanf("%s",input);
		if (input[0]!='q'||input[1]!=0){
			//NFA_print(nfa);
			bool d = NFA_execute(nfa,input);
			if (d == true) {
				printf("Input \"%s\" is accepted.\n", input);
			}
			else {
				printf("Input \"%s\" is NOT accepted.\n", input);
			}
		}
	} while(input[0] != 'q'||input[1]!=0);
    free(input);
	return;
}

//NFA - a
NFA NFA_for_ending_in_head(){
	NFA this = new_NFA(5);
	NFA_set_accepting(this, 4, true);

	NFA_add_transition_all(this, 0, 0);
	NFA_add_transition(this, 0, 'h', 1);

	NFA_add_transition(this, 1, 'e', 2);

	NFA_add_transition(this, 2, 'a', 3);

	NFA_add_transition(this, 3, 'd', 4);

	return this;
}

//NFA - b
NFA NFA_for_contains_zz(){
	NFA this = new_NFA(3);
	NFA_set_accepting(this, 2, true);

	NFA_add_transition_all(this, 0, 0);
	NFA_add_transition(this, 0, 'z', 1);

	NFA_add_transition(this, 1, 'z', 2);
	NFA_add_transition_all(this, 2, 2);
	return this;
}

//NFA - c
NFA NFA_for_not_woodpecker_anagram(){
	NFA this = new_NFA(19);
	NFA_set_accepting(this, 2, true);
	NFA_set_accepting(this, 4, true);
	NFA_set_accepting(this, 7, true);
	NFA_set_accepting(this, 9, true);
	NFA_set_accepting(this, 12, true);
	NFA_set_accepting(this, 14, true);
	NFA_set_accepting(this, 16, true);
	NFA_set_accepting(this, 18, true);

	NFA_add_transition_all(this, 0, 0);
	NFA_add_transition(this, 0, 'c', 1);
	NFA_add_transition(this, 0, 'd', 3);
	NFA_add_transition(this, 0, 'e', 5);
	NFA_add_transition(this, 0, 'k', 8);
	NFA_add_transition(this, 0, 'o', 10);
	NFA_add_transition(this, 0, 'p', 13);
	NFA_add_transition(this, 0, 'r', 15);
	NFA_add_transition(this, 0, 'w', 17);

	NFA_add_transition_all(this, 1 ,1);
	NFA_add_transition(this, 1, 'c', 2);

	NFA_add_transition_all(this, 2, 2);

	NFA_add_transition_all(this, 3 ,3);
	NFA_add_transition(this, 3, 'd', 4);

	NFA_add_transition_all(this, 4, 4);

	NFA_add_transition_all(this, 5 ,5);
	NFA_add_transition(this, 5, 'e', 6);

	NFA_add_transition_all(this, 6 ,6);
	NFA_add_transition(this, 6, 'e', 7);

	NFA_add_transition_all(this, 7, 7);

	NFA_add_transition_all(this, 8 ,8);
	NFA_add_transition(this, 8, 'k', 9);

	NFA_add_transition_all(this, 9, 9);

	NFA_add_transition_all(this, 10 ,10);
	NFA_add_transition(this, 10, 'o', 11);

	NFA_add_transition_all(this, 11 ,11);
	NFA_add_transition(this, 11, 'o', 12);

	NFA_add_transition_all(this, 12, 12);

	NFA_add_transition_all(this, 13 ,13);
	NFA_add_transition(this, 13, 'p', 14);

	NFA_add_transition_all(this, 14, 14);

	NFA_add_transition_all(this, 15, 15);
	NFA_add_transition(this, 15, 'r', 16);

	NFA_add_transition_all(this, 16, 16);

	NFA_add_transition_all(this, 17 ,17);
	NFA_add_transition(this, 17, 'w', 18);

	NFA_add_transition_all(this, 18, 18);

	return this;
}
//4th NFA for pattern we decide
NFA NFA_for_ends_in_est(){
	NFA this = new_NFA(4);
	NFA_set_accepting(this, 3, true);

	NFA_add_transition_all(this, 0, 0);
	NFA_add_transition(this, 0, 'e', 1);

	NFA_add_transition(this, 1, 's', 2);

	NFA_add_transition(this, 2, 't', 3);
	return this;
}
