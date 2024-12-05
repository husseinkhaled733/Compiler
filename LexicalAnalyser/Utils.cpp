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

    std::unordered_map<char, std::string> escapeMap = {
        {'\n', "\\n"},
        {'\t', "\\t"},
        {'\r', "\\r"},
        {'\\', "\\\\"},
        {'\"', "\\\""},
        {'\'', "\\\'"}
    };

    while (!stack.empty()) {
        State* currentState = stack.top();
        stack.pop();

        // Print the state details
        cout << "State " << currentState->id.substr(0, 6);
        if (currentState->isFinal) {
            cout << " (Final, Token: " << currentState->token << ")";
        }
        cout << ":\n";

        // Print the transitions
        for (auto& [input, next] : currentState->transitions) {
            if (!next.empty()) {
                for (State* nextState : next) {
                    cout << "  --[" << (escapeMap.contains(input) ? escapeMap[input] : std::string(1, input)) << "]--> State " << nextState->id.substr(0, 6) << "\n";
                    if (!visited.contains(nextState)) {
                        stack.push(nextState);
                        visited.insert(nextState);
                    }
                }
            } else {
                cout << "  --[" << (escapeMap.contains(input) ? escapeMap[input] : std::string(1, input)) << "]--> None\n";
            }
        }
        cout << "\n"; // Add spacing between states for better readability
    }
    cout<<"Number of states: "<<visited.size()<<endl;
}
