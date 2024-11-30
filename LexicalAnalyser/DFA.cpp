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
    cout<<"start set : ";
    for (State* state : startSet) {
        cout << state->token << " ";
    }
    cout << endl;
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
        if (currentState->isFinal) {
            finalStates.insert(currentState);
            cout << "Final State: " << currentState->token << endl;
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
            possibleInputs.insert(input);
            cout<<"input :"<<input<<" goes to : ";
            for (State* state : nextSet) {
                cout << state->token << " ";
            }
            cout << endl;
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

State* DFA::minimizeDFA(State *startState) {
    const vector<char> inputs(possibleInputs.begin(), possibleInputs.end());
    vector<unordered_set<State*>> partitions = {finalStates, normalStates};
    vector<unordered_set<State*>> newPartitions;
    int i=0;
    bool changed=true;
    while (changed) {
        cout<<"iteration no. "<<i++<<endl;
        changed=false;
        newPartitions.clear();
        for (auto& group : partitions) {
            cout << "Group: ";
            for (auto state:group) {
                cout << state->token << " ";
            }
            cout << endl;
            if (group.size() == 1) {
                newPartitions.push_back(group);
                continue;
            }
            unordered_map<string,unordered_set<State*>> newGroups;
            for (auto& state : group) {
                cout << "State: " << state->token << endl;
                string stateKey = getStateKey(state, inputs, partitions);
                newGroups[stateKey].insert(state);
                cout << "State Key: " << stateKey << endl;
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
    for (const auto& partition:partitions) {
        cout << "Partition: ";
        for (const auto state:partition) {
            cout << state->token << " ";
        }
        cout << endl;
    }
    return nullptr;
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
