//
// Created by husseinkhaled on 12/1/24.
//


#include "State.h"
#include "Utils.h"
using namespace std;

void traverse(State* startState) {
    // DFS traversal
    stack<State*> stack;
    unordered_set<State*> visited;
    stack.push(startState);
    visited.insert(startState);

    while (!stack.empty()) {
        State* currentState = stack.top();
        stack.pop();

        // Print the state details
        cout << "State " << currentState->id;
        if (currentState->isFinal) {
            cout << " (Final, Token: " << currentState->token << ")";
        }
        cout << ":\n";

        // Print the transitions
        for (auto& [input, next] : currentState->transitions) {
            if (!next.empty()) {
                for (State* nextState : next) {
                    cout << "  --[" << input << "]--> State " << nextState->id << "\n";
                    if (!visited.contains(nextState)) {
                        stack.push(nextState);
                        visited.insert(nextState);
                    }
                }
            } else {
                cout << "  --[" << input << "]--> None\n";
            }
        }
        cout << "\n"; // Add spacing between states for better readability
    }
}
