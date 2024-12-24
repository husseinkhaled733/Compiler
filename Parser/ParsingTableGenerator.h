//
// Created by mariam on 12/22/2024.
//
#Include 'Grammar.h'
#include "NonTerminal.h"
#ifndef COMPILER_PARSINGTABLEGENERATOR_H
#define COMPILER_PARSINGTABLEGENERATOR_H


class ParsingTableGenerator {
private:
    void findFirst();
    void findFirstUtil(NonTerminal* nonTerminal);
    void findForward();
public:
    Grammar* grammar;

    ParsingTableGenerator(Grammar* grammar);

    ParsingTable* generateParsingTable();
};


#endif //COMPILER_PARSINGTABLEGENERATOR_H
