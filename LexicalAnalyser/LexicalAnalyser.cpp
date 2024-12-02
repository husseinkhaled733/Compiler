//
// Created by mohamed_anwar on 11/27/24.
//

#include "LexicalAnalyser.h"

#include "InputParser/Constants.h"

LexicalAnalyser::LexicalAnalyser(const SymbolTableHandler& symbolTableHandler, State* startState) {
    minimalDFAStartState = startState;

    this->symbolTableHandler   = symbolTableHandler;
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentLexeme        = Lexeme();
}

Lexeme LexicalAnalyser::nextToken() {

    if (currentLexeme.getTokenType() == DELIMITER) {
        currentLexeme = Lexeme();
        nextToken();
    }

    if (!currentLexeme.getValue().empty()) {
        auto token    = currentLexeme;
        currentLexeme = Lexeme();
        return token;
    }

    std::ifstream file(sourceFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }

    file.seekg(currentIndexInSource);

    std::vector<char> buffer(BUFFER_SIZE);
    std::vector<char> fullBuffer;

    int longestMatchIndex = -1;
    State longestMatchState;

    int errorBackupIndex = 0;
    bool errorOccurred   = false;

    int startBufferIndex = 0;

    while (true) {
        file.read(buffer.data(), BUFFER_SIZE);
        size_t bytesRead = file.gcount();

        if (bytesRead == 0) {
            break;
        }

        buffer.resize(bytesRead);
        fullBuffer.insert(fullBuffer.end(), buffer.begin(), buffer.begin() + static_cast<int>(bytesRead));

        for (int i = startBufferIndex * BUFFER_SIZE; i < fullBuffer.size(); i++) {
            std::vector<State*> nextStates = currentState->applyTransition(fullBuffer[i]);

            if (nextStates.empty()) {

                if (longestMatchIndex == -1) {
                    i             = ++errorBackupIndex;
                    errorOccurred = true;
                } else {
                    auto longestMatchTokenValue =
                        std::string(fullBuffer.begin() + errorBackupIndex, fullBuffer.begin() + longestMatchIndex + 1);

                    currentLexeme = Lexeme(longestMatchState.token, longestMatchTokenValue);
                    currentIndexInSource += longestMatchIndex + 1;
                    currentState = minimalDFAStartState; // reset to start state
                    return currentLexeme;
                }

            } else {

                currentState = nextStates[0];
                if (currentState->isFinal) {

                    // log error on first match if error happened before it
                    if (errorOccurred) {
                        logError(fullBuffer, errorBackupIndex);
                        errorOccurred = false; // reset to log error once
                    }

                    longestMatchIndex = i;
                    longestMatchState = *currentState;
                }
            }
        }

        startBufferIndex++;
    }

    // if we had a match at the end of the file [0000001] 1 was a final state and we reached the end of the file
    // so it won't be considered as a match unless we check after the loop
    if (longestMatchIndex != -1) {
        auto longestMatchTokenValue =
            std::string(fullBuffer.begin() + errorBackupIndex, fullBuffer.begin() + longestMatchIndex + 1);

        currentLexeme = Lexeme(longestMatchState.token, longestMatchTokenValue);
        currentIndexInSource += longestMatchIndex + 1;
        currentState = minimalDFAStartState; // reset to start state
        return currentLexeme;
    }

    // if we reached the end of the file and no match was found then the whole buffer is an error
    if (!fullBuffer.empty()) {
        logError(fullBuffer, static_cast<int>(fullBuffer.size()));
    }
    return Lexeme();
}

bool LexicalAnalyser::hasNextToken() {
    currentLexeme = nextToken();
    return !currentLexeme.getValue().empty();
}

void LexicalAnalyser::tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath) {
    this->sourceFilePath = sourceFilePath;

    std::ofstream outputFile(outputFilePath);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }

    auto printTableHeader = [](std::ostream &output) {
        output << std::setw(20) << std::left << "Token Type"
               << std::setw(20) << std::left << "Value" << std::endl;
        output << std::string(40, '-') << std::endl;
    };

    auto printTableRow = [](std::ostream &output, const std::string &tokenType, const std::string &value) {
        output << std::setw(20) << std::left << tokenType
               << std::setw(20) << std::left << value << std::endl;
    };

    printTableHeader(outputFile);
    while (hasNextToken()) {
        auto currentLexeme = nextToken();
        printTableRow(outputFile, currentLexeme.getTokenType(), currentLexeme.getValue());
        std::regex idPattern("^id\\w*$", std::regex::icase);
        if (std::regex_match(currentLexeme.getTokenType(), idPattern)) {
            symbolTableHandler.addSymbol(currentLexeme.getValue());
        }
    }

    outputFile.close();
}

void LexicalAnalyser::logError(std::vector<char> fullBuffer, const int errorBackupIndex) const {
    const std::string errorSubstring(fullBuffer.begin(), fullBuffer.begin() + errorBackupIndex);

    std::cerr << "Can't recognize token at index " + std::to_string(currentIndexInSource)
              << ", problematic substring: \"" + errorSubstring + "\"" << std::endl;
}

void LexicalAnalyser::reset() {
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentLexeme        = Lexeme();
}
