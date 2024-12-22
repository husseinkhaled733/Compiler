//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "NonTerminal.h"
#include <bits/stdc++.h>
using namespace std;

class Grammar {
    static const std::string EPSILON;
    static const std::string END;

    NonTerminal* startSymbol;
    unordered_map<string, NonTerminal*> nonTerminals;
    unordered_map<string, Terminal*> terminals;
    unordered_map<string, vector<vector<Symbol*>>> productions;
};



#endif //GRAMMAR_H
