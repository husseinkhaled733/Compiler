//
// Created by husseinkhaled on 11/28/24.
//

#ifndef DFA_H
#define DFA_H
#include "../State.h"
using namespace std;

class DFA {
public:
    State* dfaStartState;
    State* minimizedDFAStartState;
    // To use in minimizeDFA
    vector<unordered_set<State*>> partitions;
    vector<char> inputs;
    State* convertNFAtoDFA(State *startState);
    static string getStateKey(State *state, const vector<char> &inputs, const vector<unordered_set<State *>> &partitions);
    State* minimizeDFA(State *startState);
    void printDFA() const;
    void printMinimizedDFA() const;
private:
    static void epsilonClosure(set<State *> &states);
    static void handleTokenPriorities(State *newState, const State *currentState);
};
#endif //DFA_H
