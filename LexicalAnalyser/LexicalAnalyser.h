//
// Created by mohamed_anwar on 11/27/24.
//

#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H

#include "State.h"
#include "SymbolTableHandler.h"
#include <bits/stdc++.h>


class LexicalAnalyser {

    SymbolTableHandler symbolTableHandler;

    std::string sourceFilePath;
    std::string outputFilePath;

    State currentState;
    long long currentIndexInSource;
    std::string currentToken;

    const int BUFFER_SIZE = 1024;

    State minimalDFAStartState;

public:

    explicit LexicalAnalyser(const SymbolTableHandler& symbolTableHandler);

    std::string nextToken();
    bool hasNextToken();
    void tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath);
    void logError(std::vector<char> fullBuffer, int errorBackupIndex, int i) const;
    void reset();

    static State getExampleDFA(); // will be removed

};



#endif //LEXICALANALYSER_H
