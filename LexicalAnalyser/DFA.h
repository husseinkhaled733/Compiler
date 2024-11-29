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
    set<State* > finalStates;
    set<State* > normalStates;
    State* convertNFAtoDFA(State *startState);
    State* minimizeDFA(State *startState);
private:
    std::set<State*> epsilonClosure(const std::set<State* >& states);
    void handleTokenPriorities(map<set<State *>, State *> &dfaStates, const set<State *> &nextSet);
};
#endif //DFA_H
