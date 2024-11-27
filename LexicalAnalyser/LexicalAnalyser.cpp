//
// Created by mohamed_anwar on 11/27/24.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser(const SymbolTableHandler& symbolTableHandler) {
    minimalDFAStartState = getExampleDFA();

    this->symbolTableHandler   = symbolTableHandler;
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentToken         = "";
}

State LexicalAnalyser::getExampleDFA() {
    // Creating states
    State state0137;
    State state247;
    State state8("a*b+");
    State state7;
    State state68("abb");
    State state58("a*b+");

    // Marking final states
    state247.isFinal = true;
    state8.isFinal   = true;
    state58.isFinal  = true;

    // Adding transitions
    // Transitions for state0137
    state0137.addTransition('a', state247);
    state0137.addTransition('b', state8);

    // Transitions for state247
    state247.addTransition('a', state247);
    state247.addTransition('b', state58);

    // Transitions for state8
    state8.addTransition('b', state8);

    // Transitions for state7
    state7.addTransition('a', state247);
    state7.addTransition('b', state68);

    // Transitions for state68
    state68.addTransition('b', state8);

    // Transitions for state58
    state58.addTransition('b', state8);

    // The DFA starts at state0137, so we return it
    return state0137;
}

std::string LexicalAnalyser::nextToken() {

    if (!currentToken.empty()) {
        auto token   = currentToken;
        currentToken = "";
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
    int errorBackupIndex  = 1;
    int startBufferIndex  = 0;

    State longestMatchState;

    while (true) {
        file.read(buffer.data(), BUFFER_SIZE);
        size_t bytesRead = file.gcount();

        if (bytesRead == 0) {
            break;
        }

        buffer.resize(bytesRead);
        fullBuffer.insert(fullBuffer.end(), buffer.begin(), buffer.begin() + static_cast<int>(bytesRead));

        for (int i = startBufferIndex * BUFFER_SIZE; i < fullBuffer.size(); i++) {
            std::vector<State> nextStates = currentState.applyTransition(buffer[i]);

            if (nextStates.empty()) {

                if (longestMatchIndex == -1) {
                    logError(fullBuffer, errorBackupIndex, i);
                    i = errorBackupIndex++;
                } else {
                    currentToken = longestMatchState.token;
                    currentIndexInSource += longestMatchIndex + 1;
                    currentState = getExampleDFA();
                    return currentToken;
                }

            } else {

                currentState = nextStates[0];
                if (currentState.isFinal) {
                    longestMatchIndex = i;
                    errorBackupIndex  = i + 2;
                    longestMatchState = currentState;
                }
            }
        }

        startBufferIndex++;
    }

    return "";
}

bool LexicalAnalyser::hasNextToken() {
    currentToken = nextToken();
    return !currentToken.empty();
}

void LexicalAnalyser::tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath) {
    this->sourceFilePath = sourceFilePath;
    this->outputFilePath = outputFilePath;

    std::ofstream outputFile(outputFilePath);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }

    while (hasNextToken()) {
        auto currentToken = nextToken();
        outputFile << currentToken << std::endl;
    }

    outputFile.close();
}

void LexicalAnalyser::logError(std::vector<char> fullBuffer,const int errorBackupIndex,const int i) const {
    const std::string errorSubstring(fullBuffer.begin() + errorBackupIndex - 1, fullBuffer.begin() + i);
    std::cerr << "Can't recognize token at index " + std::to_string(currentIndexInSource + i)
                     + ", problematic substring: \"" + errorSubstring + "\""
              << std::endl;
}

void LexicalAnalyser::reset() {
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentToken         = "";
}
