//
// Created by husseinkhaled on 11/28/24.
//

#ifndef DFA_H
#define DFA_H
#include "State.h"
using namespace std;

class DFA {
public:
    State* dfaStartState;
    State* convertNFAtoDFA(State *startState);
    State* minimizeDFA(State *startState);
    std::set<State*> epsilonClosure(const std::set<State* >& states);
};
#endif //DFA_H
