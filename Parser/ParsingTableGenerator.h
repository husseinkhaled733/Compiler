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
public:
    Grammar* grammar;

    ParsingTableGenerator(Grammar* grammar);

    ParsingTable generateParsingTable();
};


#endif //COMPILER_PARSINGTABLEGENERATOR_H
