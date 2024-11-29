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
    handleTokenPriorities(dfaStates, startSet);
    dfaStartState = dfaStates[startSet];
    while (!needToProcess.empty()) {
        State* currentState = dfaStates[needToProcess.front()];
        set<State*> currentNFASet = needToProcess.front();
        needToProcess.pop();
        if (currentState->isFinal) {
            finalStates.insert(currentState);
        }
        else {
            normalStates.insert(currentState);
        }
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
            if (!dfaStates.contains(nextSet)) {
                needToProcess.push(nextSet);
                dfaStates[nextSet] = new State();
                handleTokenPriorities(dfaStates, nextSet);
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
            for (vector<State* > nextStates = state->transitions[epsilon]; State* nextState : nextStates) {
                if (!closure.contains(nextState)) {
                    closure.insert(nextState);
                    stack.push(nextState);
                }
            }
        }
    }

    return closure;
}
void DFA::handleTokenPriorities(map<set<State *>, State *>& dfaStates, const set<State *>& nextSet) {
    for (const State* state : nextSet) {
        if (state->isFinal) {
            dfaStates[nextSet]->isFinal = true;
            if (dfaStates[nextSet]->token.empty()) {
                dfaStates[nextSet]->token = state->token;
            }
            // Choose the token with the highest priority
            else if (priorities[state->token] < priorities[dfaStates[nextSet]->token]) {
                dfaStates[nextSet]->token = state->token;
            }
        }
    }
}
