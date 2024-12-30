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
public:
    explicit InputProgramParser(LexicalAnalyser* lexicalAnalyser, Grammar* grammar, ParsingTable* parsingTable);
    stack<Symbol*> remainingSymbols;
    LexicalAnalyser* lexicalAnalyser;
    Grammar* grammar;
    ParsingTable* parsingTable;
    Lexeme currentLexeme;
    ofstream output;
    void parse();
    void printLeftMostDerivation();
    void parseInputProgram(const string &outputFilePath);
    void handleTerminal(Symbol* currentSymbol, string& currentTokenName, bool& isInputEnd);
    void handleNonTerminal(Symbol* currentSymbol, string& currentTokenName, bool& isInputEnd);
    void logDebug(const string& message);
    void handleCurrentSymbol(Symbol* currentSymbol, string& currentTokenName, bool& isInputEnd);
};

#endif //INPUTPROGRAMPARSER_H
