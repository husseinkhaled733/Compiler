//
// Created by husseinkhaled on 11/28/24.
//

#include "DFA.h"
#include "../State.h"
#include "../Utils.h"
#include "../StateIdManager.h"

using namespace std;

State* DFA::convertNFAtoDFA(State *startState) {
    map<set<State*>,State*> dfaStates;
    queue<set<State*>> needToProcess;
    // To partition the final states based on their tokens
    unordered_map<string,unordered_set<State* >> tokensPartitions;
    set<State*> startSet;
    unordered_set<char> possibleInputs;
    startSet.insert(startState);
    epsilonClosure(startSet);
    needToProcess.push(startSet);
    dfaStates[startSet] = new State(StateIdManager::getInstance().getNextId());
    dfaStartState = dfaStates[startSet];
    for (const State* state : startSet) {
        handleTokenPriorities(dfaStartState, state);
        dfaStartState->id += state->id;
    }
    while (!needToProcess.empty()) {
        State* currentState = dfaStates[needToProcess.front()];
        set<State*> currentNFASet = needToProcess.front();
        needToProcess.pop();
        if (currentState->isFinal) {
            tokensPartitions[currentState->token].insert(currentState);
            cout << "Final State: " << currentState->token << endl;
        }
        else {
            normalStates.insert(currentState);
        }
        // Construct the transitions for the new states
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
        // Epsilon closure for the new states
        for (auto& [input, next] : transitions) {
            epsilonClosure(next);
            if (!dfaStates.contains(next)) {
                needToProcess.push(next);
                dfaStates[next] = new State(StateIdManager::getInstance().getNextId());
                for (const State* state : next) {
                    dfaStates[next]->id += state->id;
                    handleTokenPriorities(dfaStates[next], state);
                }
            }
            currentState->addTransition(input, dfaStates[next]);
            possibleInputs.insert(input);
        }
    }
    partitions.emplace_back(normalStates);
    for (const auto &states: tokensPartitions | views::values) {
        partitions.emplace_back(states);
    }
    inputs = vector<char>(possibleInputs.begin(), possibleInputs.end());
    return dfaStartState;
}

void DFA::epsilonClosure(set<State* >& states) {
    std::stack<State*> stack;
    for (State* state : states) {
        stack.push(state);
    }
    while (!stack.empty()) {
        State* state = stack.top();
        stack.pop();

        if (state->transitions.contains(epsilon)) {
            for (vector<State* > nextStates = state->transitions[epsilon]; State* nextState : nextStates) {
                if (!states.contains(nextState)) {
                    states.insert(nextState);
                    stack.push(nextState);
                }
            }
        }
    }
}
void DFA::handleTokenPriorities(State* newState, const State* currentState) {
    if (currentState->isFinal) {
        newState->isFinal = true;
        if (newState->token.empty() || priorities[currentState->token] < priorities[newState->token]) {
            newState->token = currentState->token;
        }
    }
}

State* DFA::minimizeDFA(State *startState) {
    vector<unordered_set<State*>> newPartitions;
    bool changed=true;
    // Keep partitioning until no more changes
    while (changed) {
        changed=false;
        newPartitions.clear();
        for (auto& group : partitions) {
            if (group.size() == 1) {
                newPartitions.push_back(group);
                continue;
            }
            unordered_map<string,unordered_set<State*>> newGroups;
            for (auto& state : group) {
                string stateKey = getStateKey(state, inputs, partitions);
                newGroups[stateKey].insert(state);
            }
            for (const auto &newGroup: newGroups | views::values) {
                newPartitions.push_back(newGroup);
                if (newGroup.size() != group.size()) {
                    changed=true;
                }
            }
        }
        partitions = newPartitions;
    }
    // Reconstruction of the minimized DFA
    unordered_map<State* , State*> newStates;
    vector<State* > minimizedStates;
    for (const auto& partition:partitions) {
        auto* newState = new State(StateIdManager::getInstance().getNextId());
        const auto* representative = *partition.begin();
        newState->transitions = representative->transitions;
        for (const auto state:partition) {
            newState->id += state->id;
            newStates[state] = newState;
            handleTokenPriorities(newState, state);
        }
        minimizedStates.push_back(newState);
    }
    // Modify the transitions to point to the new states
    for (const auto& state: minimizedStates) {
        for (auto& [input, next] : state->transitions) {
            if (next.empty()) {
                continue;
            }
            State* nextState = newStates[*next.begin()];
            state->transitions[input] = {nextState};
        }
    }
    minimizedDFAStartState = newStates[startState];
    return minimizedDFAStartState;

}

string DFA::getStateKey(State *state, const vector<char> &inputs, const vector<unordered_set<State *>> &partitions) {
    string stateKey;
    for (auto input:inputs) {
        if (state->transitions.contains(input)) {
            State* nextState = state->applyTransition(input)[0];
            for (int i = 0; i < partitions.size(); i++) {
                if (partitions[i].contains(nextState)) {
                    stateKey += to_string(i)+",";
                    break;
                }
            }
        }
        else {
            stateKey += "-1,";
        }
    }
    return stateKey;
}

void DFA::printDFA() const {
    cout << "===================================" << endl;
    cout << "              DFA STATES            " << endl;
    cout << "===================================" << endl;
    traverse(dfaStartState);
    cout << "===================================" << endl;
    cout << "         END OF DFA STATES          " << endl;
    cout << "===================================" << endl;
}

void DFA::printMinimizedDFA() const {
    cout << "===================================" << endl;
    cout << "         MINIMIZED DFA STATES       " << endl;
    cout << "===================================" << endl;
    traverse(minimizedDFAStartState);
    cout << "===================================" << endl;
    cout << "    END OF MINIMIZED DFA STATES     " << endl;
    cout << "===================================" << endl;
}
