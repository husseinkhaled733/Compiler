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
    static Terminal* EPSILON;
    static Terminal* END;
    static const set<string> RESERVED_SYMBOLS;
    static const set<char> IGNORED_CHARS;

private:
    NonTerminal* startSymbol;
    unordered_map<string, NonTerminal*> nonTerminals;
    unordered_map<string, vector<vector<Symbol*>>> productions;

public:
    Grammar();

    NonTerminal* getStartSymbol() const;
    unordered_map<string, NonTerminal*>& getNonTerminals();
    unordered_map<string, Terminal*>& getTerminals();
    unordered_map<string, vector<vector<Symbol*>>>& getProductions();

    void addNonTerminal(NonTerminal* nonTerminal);
    void setStartSymbol(NonTerminal* startSymbol);
    void addProduction(NonTerminal* nonTerminal, vector<Symbol*> production);

    void printGrammar() const;
};


#endif // GRAMMAR_H
