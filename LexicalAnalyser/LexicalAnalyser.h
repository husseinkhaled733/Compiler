//
// Created by mohamed_anwar on 11/27/24.
//

#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H

#include "Lexeme.h"
#include "State.h"
#include "SymbolTableHandler.h"
#include <bits/stdc++.h>


class LexicalAnalyser {

    SymbolTableHandler symbolTableHandler;

    std::string sourceFilePath;

    State *currentState, *minimalDFAStartState;
    long long currentIndexInSource;
    Lexeme currentLexeme;

    const int BUFFER_SIZE = 1024;

public:

    explicit LexicalAnalyser(const SymbolTableHandler& symbolTableHandler, State* startState);

    Lexeme nextToken();
    bool hasNextToken();
    void tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath);
    void logError(std::vector<char> fullBuffer, int errorBackupIndex) const;
    void reset();

    static State* getExampleDFA(); // will be removed

};



#endif //LEXICALANALYSER_H
