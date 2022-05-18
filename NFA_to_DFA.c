/*
 * NFA_to_DFA.c
 *
 *  Created on: Jan 18, 2022
 *      Author 1: claudiacortell
 *      Author 2: Nadine Eldallal
 *
 * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "NFA_to_DFA.h"
#include "LinkedList.h"
#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"

DFA NFA_to_DFA(NFA nfa) {
    IntHashSet set = new_IntHashSet(nfa-> numStates);

    LinkedList state_labels = new_LinkedList();
    IntHashSet_insert(set, 0);
    LinkedList_add_at_front(state_labels, set);

    //create the linked list of IntHashSets to act as dfa state labels
    int counter = 0;

    IntHashSet set2;
    do {
        IntHashSet it_set = LinkedList_elementAt(state_labels, counter);
        //printf("%s", "entering for loop\n");
        for (int char_id=0; char_id<128; char_id++) {
            //printf("%d", char_id);
            IntHashSetIterator it = IntHashSet_iterator(it_set);
            set2 = new_IntHashSet(nfa->numStates);

            while(IntHashSetIterator_hasNext(it)) {
                IntHashSet_union(set2, NFA_get_transitions(nfa,
                                                           IntHashSetIterator_next(it), char_id));
            }

            free(it);
            bool contained = false;

            //add set of labels if not already in the linked list
            LinkedListIterator it_list = LinkedList_iterator(state_labels);

            while(LinkedListIterator_hasNext(it_list)) {
                IntHashSet set1 = LinkedListIterator_next(it_list);
                if (IntHashSet_equals(set2, set1)==true) {
                    contained = true;
                }
            }
            free(it_list);


            if((contained == false) && (IntHashSet_isEmpty(set2))==false) {
                LinkedList_add_at_end(state_labels, set2);
            }
            else {
                IntHashSet_free(set2);
                set2 = NULL;
            }
        }

        counter++;

    } while(counter < NFA_get_size(nfa));

    //initialize dfa
    int dfa_numstates = LinkedList_size(state_labels);
    DFA dfa = new_DFA(dfa_numstates);

    //set DFAs arcs
    for (int i=0; i< DFA_get_size(dfa); i++) {
        IntHashSet set4 = LinkedList_elementAt(state_labels, i);
        for (int j=0; j<128; j++) {
            IntHashSetIterator setIterator = IntHashSet_iterator(set4);
            IntHashSet set5 = new_IntHashSet(nfa->numStates);
            while(IntHashSetIterator_hasNext(setIterator)) {
                IntHashSet_union(set5,
                                 NFA_get_transitions(nfa, IntHashSetIterator_next(setIterator), j));
            }
            int curr = 0;
            while (!IntHashSet_equals(set5, LinkedList_elementAt(state_labels, curr)) &&
                    curr<LinkedList_size(state_labels)) {
                curr++;
            }
            DFA_set_transition(dfa, i, j, curr);
            IntHashSet_free(set5);

            set5 = NULL;
            free(setIterator);
        }
    }

    //Set DFA accepting states
    int dfa_state_index = 0;
    IntHashSet newSet;
    LinkedListIterator acceptIterator = LinkedList_iterator(state_labels);
    while(LinkedListIterator_hasNext(acceptIterator)) {
        newSet = LinkedListIterator_next(acceptIterator);
        IntHashSetIterator set_iter = IntHashSet_iterator(newSet);
        while (IntHashSetIterator_hasNext(set_iter)) {
            int curr = IntHashSetIterator_next(set_iter);
            if (NFA_get_accepting(nfa, curr) == true) {
                DFA_set_accepting(dfa, dfa_state_index, true);
            }
        }
        free(set_iter);
        dfa_state_index++;
    }
    IntHashSet_free(set);
    set = NULL;
    LinkedList_free(state_labels, false);
    state_labels = NULL;
    free(acceptIterator);

    return dfa;
}