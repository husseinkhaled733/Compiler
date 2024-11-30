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
    unordered_set<State* > finalStates;
    unordered_set<State* > normalStates;
    unordered_set<char> possibleInputs;
    State* convertNFAtoDFA(State *startState);
    string getStateKey(State *state, const vector<char> &inputs, const vector<unordered_set<State *>> &partitions);
    State* minimizeDFA(State *startState);
private:
    std::set<State*> epsilonClosure(const std::set<State* >& states);
    void handleTokenPriorities(map<set<State *>, State *> &dfaStates, const set<State *> &nextSet);
};
#endif //DFA_H
