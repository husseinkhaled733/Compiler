//
// Created by mohamed_anwar on 12/24/24.
//

#ifndef GRAMMARPARSER_H
#define GRAMMARPARSER_H
#pragma once

#include <bits/stdc++.h>

#include "Grammar.h"

using namespace std;

class ParserState;

class GrammarParser {
    ifstream inputFilePath;
    ParserState* currentState;
    Grammar* grammar;
    NonTerminal* currentNonTerminal;

public:
    explicit GrammarParser(const std::string& fileName);
    ~GrammarParser();

    void readNonTerminals(const string& buffer);
    Grammar* parseGrammar();
    string readInputFile();

    Grammar* getGrammar() const;
    void setState(ParserState* state);
    NonTerminal* getCurrentNonTerminal() const;
    void setCurrentNonTerminal(NonTerminal* nonTerminal);
};


#endif //GRAMMARPARSER_H
