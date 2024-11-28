//
// Created by husseinkhaled on 11/28/24.
//

#include "DFA.h"
#include "State.h"
#include "Utils.h"
using namespace std;

State* DFA::convertNFAtoDFA(State *startState) {
    map<set<State*>,State*> dfaStates;
    queue<set<State*>> needToProcess;
    set<State*> startSet;
    startSet.insert(startState);
    startSet = epsilonClosure(startSet);
    needToProcess.push(startSet);
    dfaStates[startSet] = new State();
    dfaStartState = dfaStates[startSet];
    while (!needToProcess.empty()) {
        State* currentState = dfaStates[needToProcess.front()];
        set<State*> currentNFASet = needToProcess.front();
        needToProcess.pop();
        cout << "Current NFA Set: ";
        for (State* state : currentNFASet) {
            cout << state->token << " ";
        }
        cout << endl;
        map<char, set<State*>> transitions;
        for (State* state : currentNFASet) {
            for (auto& [input, next] : state->transitions) {
                if (input != epsilon) {
                    for (State* nextState : next) {
                        transitions[input].insert(nextState);
                    }
                }
            }
        }
        for (auto& [input, next] : transitions) {
            set<State*> nextSet = epsilonClosure(next);
            cout << "Transition on " << input << " to: ";
            for (State* state : nextSet) {
                cout << state->token << " ";
            }
            cout << endl;
            if (!dfaStates.contains(nextSet)) {
                needToProcess.push(nextSet);
                dfaStates[nextSet] = new State();
            }
            currentState->addTransition(input, dfaStates[nextSet]);
        }
    }

    return dfaStartState;
}

set<State* > DFA::epsilonClosure(const set<State* >& states) {
    std::set<State*> closure = states;
    std::stack<State*> stack;
    for (State* state : states) {
        stack.push(state);
    }
    while (!stack.empty()) {
        State* state = stack.top();
        stack.pop();

        if (state->transitions.contains(epsilon)) {
            vector<State* > nextStates = state->transitions[epsilon];
            for (State* nextState : nextStates) {
                if (!closure.contains(nextState)) {
                    closure.insert(nextState);
                    stack.push(nextState);
                }
            }
        }
    }

    return closure;
}

