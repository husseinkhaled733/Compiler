//
// Created by mariam on 12/22/2024.
//
#include "Grammar.h"

#include "NonTerminal.h"
#include "ParsingTable.h"

#ifndef COMPILER_PARSINGTABLEGENERATOR_H
#define COMPILER_PARSINGTABLEGENERATOR_H


class ParsingTableGenerator {
private:
    void findFirstUtil();
    void findFirst(NonTerminal* nonTerminal);
    void findFollowUtil();
    void findFollow(NonTerminal* nonTerminal);
    static void addToParsingTable(ParsingTable &parsingTable, const string &nonTerminalString, Symbol *firstSymbol,int index) ;
public:
    Grammar* grammar;
    explicit ParsingTableGenerator(Grammar* grammar) : grammar(grammar) {}
    ParsingTable generateParsingTable();
    void printFirstAndFollow();
};


#endif //COMPILER_PARSINGTABLEGENERATOR_H
