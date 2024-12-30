//
// Created by mohamed_anwar on 11/27/24.
//

#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H

#include "DFA/DFABuilder.h"
#include "InputParser/RegexTreeBuilder.h"
#include "Lexeme.h"
#include "NFABuilder/NFABuilder.h"
#include "State.h"
#include "SymbolTableHandler.h"
#include <bits/stdc++.h>


class LexicalAnalyser {

    RegexTreeBuilder regexTreeBuilder;
    NFABuilder nfaBuilder;
    DFABuilder dfaBuilder;

    SymbolTableHandler symbolTableHandler;

    std::string sourceFilePath;

    State *currentState, *minimalDFAStartState;
    long long currentIndexInSource;
    Lexeme currentLexeme;

    const int BUFFER_SIZE = 1024;

public:

    explicit LexicalAnalyser(const std::string& rulesFilePath, const std::string& sourceFilePath);

    Lexeme nextToken();
    bool hasNextToken();
    void tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath);
    void logError(std::vector<char> fullBuffer, int errorBackupIndex) const;
    void reset();
};



#endif //LEXICALANALYSER_H
