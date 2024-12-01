//
// Created by husseinkhaled on 12/1/24.
//


#include "State.h"
#include "Utils.h"
using namespace std;

void traverse(State* startState) {
    // DFS traversal
    stack<State* > stack;
    unordered_set<State*> visited;
    stack.push(startState);
    visited.insert(startState);
    while (!stack.empty()) {
        State* currentState = stack.top();
        stack.pop();
        cout << "State: " << currentState->id << endl;
        if (currentState->isFinal) {
            cout<<"Final State with token: " << currentState->token << endl;
        }
        for (auto& [input, next] : currentState->transitions) {
            cout << "Input: " << input;
            if (next.empty()) {
                cout << " Next: " << "None" << endl;
                continue;
            }
            cout << " Next: " << next[0]->id << endl;
            for (State* nextState : next) {
                if (visited.contains(nextState)) {
                    continue;
                }
                stack.push(nextState);
                visited.insert(nextState);
            }
        }
    }
}
