// ParsingTable.h

#include <bits/stdc++.h>
#include "ParsingTable.h"
#include "Grammar.h"
using namespace std;


void ParsingTable :: printParsingTable(unordered_map<string, vector<vector<Symbol*>>>& productions) const {
    cout<<"========================="<<endl;
    cout << "     Parsing Table:" << endl;
    cout<<"========================="<<endl;

    for (const auto& row : table) {
        const string& nonTerminal = row.first;

        // Check if non-terminal exists in productions
        if (productions.find(nonTerminal) == productions.end()) {
            cerr << "Error: Non-terminal '" << nonTerminal << "' not found in productions." << endl;
            continue;
        }

        for (const auto& entry : row.second) {
            const string& terminal = entry.first;
            int ruleIndex = entry.second;

            // Handle special cases for SYNC or epsilon
            if (ruleIndex == SYNC) {
                cout << nonTerminal << " -> " << terminal << " : sync" << endl;
                continue;
            }
            // Check if ruleIndex is within bounds
            if (ruleIndex < 0 || ruleIndex >= productions[nonTerminal].size()) {
                cerr << "Error: Invalid rule index " << ruleIndex
                     << " for non-terminal '" << nonTerminal << "'." << endl;
                continue;
            }
            string derivation = "";

            // Build the derivation string
            for (auto symbol : productions[nonTerminal][ruleIndex]) {
                if (!symbol) {
                    cerr << "Error: Null symbol in production for non-terminal '"
                         << nonTerminal << "'." << endl;
                    continue;
                }
                // Handle epsilon "/0"
                if (symbol == Grammar::EPSILON) {
                    derivation += "epsilon ";
                } else {
                    derivation += symbol->getName() + " ";
                }
            }
            // Print the entry
            cout << nonTerminal << " -> " << terminal << " : " << derivation << endl;
        }
    }
}



