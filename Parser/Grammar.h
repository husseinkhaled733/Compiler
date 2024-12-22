//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "NonTerminal.h"
#include <bits/stdc++.h>

using namespace std;

class Grammar {
public:
    static const Terminal* EPSILON;
    static const Terminal* END;

private:
    NonTerminal* startSymbol;
    unordered_map<string, NonTerminal*> nonTerminals;
    unordered_map<string, Terminal*> terminals;
    unordered_map<string, vector<vector<Symbol*>>> productions;

public:
    Grammar();

    NonTerminal* getStartSymbol() const;
    std::unordered_map<std::string, NonTerminal*>& getNonTerminals();
    std::unordered_map<std::string, Terminal*>& getTerminals();
    std::unordered_map<std::string, std::vector<std::vector<Symbol*>>>& getProductions();
};


#endif // GRAMMAR_H
