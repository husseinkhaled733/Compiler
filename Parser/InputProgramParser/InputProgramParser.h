//
// Created by husseinkhaled on 12/22/24.
//

#ifndef INPUTPROGRAMPARSER_H
#define INPUTPROGRAMPARSER_H

#include "../Symbol.h"
#include "../../LexicalAnalyser/LexicalAnalyser.h"
#include "../Grammar.h"
#include "../ParsingTable.h"
using namespace std;

class InputProgramParser {
private:
    stack<Symbol*> remainingSymbols;
    LexicalAnalyser* lexicalAnalyser;
    Grammar* grammar;
    ParsingTable* parsingTable;
    Lexeme currentLexeme;
    ofstream output;
    vector<Symbol* > matchedTokens;
    bool handleTerminal(string &currentTokenName, bool &isInputEnd, Symbol *currentSymbol);
    void handleNonTerminal(string &currentTokenName, bool &isInputEnd, const Symbol *currentSymbol);
    void printLeftMostDerivation();
public:
    explicit InputProgramParser(LexicalAnalyser* lexicalAnalyser, Grammar* grammar, ParsingTable* parsingTable);
    void parse();
    void parseInputProgram(const string &outputFilePath);
    static string getName(const string &currentName);

};

#endif //INPUTPROGRAMPARSER_H
