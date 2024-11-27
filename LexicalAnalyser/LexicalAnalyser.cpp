//
// Created by mohamed_anwar on 11/27/24.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser(const SymbolTableHandler& symbolTableHandler) {
    minimalDFAStartState = getExampleDFA();

    this->symbolTableHandler   = symbolTableHandler;
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentLexeme        = Lexeme();
}

State* LexicalAnalyser::getExampleDFA() {
    // Creating heap-allocated states
    State* state0137 = new State();
    State* state247  = new State("a");
    State* state8    = new State("a*b+");
    State* state7    = new State();
    State* state68   = new State("abb");
    State* state58   = new State("a*b+");

    // Marking final states
    state247->isFinal = true;
    state8->isFinal   = true;
    state58->isFinal  = true;
    state68->isFinal  = true;

    // Adding transitions for state0137
    state0137->addTransition('a', state247);
    state0137->addTransition('b', state8);

    // Adding transitions for state247
    state247->addTransition('a', state7);
    state247->addTransition('b', state58);

    // Adding transitions for state8
    state8->addTransition('b', state8);

    // Adding transitions for state7
    state7->addTransition('a', state7);
    state7->addTransition('b', state8);

    // Adding transitions for state68
    state68->addTransition('b', state8);

    // Adding transitions for state58
    state58->addTransition('b', state68);

    // The DFA starts at state0137, so we return it
    return state0137;
}

Lexeme LexicalAnalyser::nextToken() {

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
            std::vector<State*> nextStates = currentState->applyTransition(fullBuffer[i]);

            if (nextStates.empty()) {

                if (longestMatchIndex == -1) {
                    logError(fullBuffer, errorBackupIndex, i);
                    i = errorBackupIndex++;
                } else {
                    auto longestMatchTokenValue =
                        std::string(fullBuffer.begin(), fullBuffer.begin() + longestMatchIndex + 1);

                    currentLexeme = Lexeme(longestMatchState.token, longestMatchTokenValue);
                    currentIndexInSource += longestMatchIndex + 1;
                    currentState = minimalDFAStartState;
                    return currentLexeme;
                }

            } else {

                currentState = nextStates[0];
                if (currentState->isFinal) {
                    longestMatchIndex = i;
                    errorBackupIndex  = i + 2;
                    longestMatchState = *currentState;
                }
            }
        }

        startBufferIndex++;
    }

    if (longestMatchIndex != -1) {
        auto longestMatchTokenValue =
                        std::string(fullBuffer.begin(), fullBuffer.begin() + longestMatchIndex + 1);
        currentLexeme = Lexeme(longestMatchState.token, longestMatchTokenValue);
        currentIndexInSource += longestMatchIndex + 1;
        currentState = minimalDFAStartState;
        return currentLexeme;
    }

    logError(fullBuffer, errorBackupIndex - 1, fullBuffer.size());

    return Lexeme();
}

bool LexicalAnalyser::hasNextToken() {
    currentLexeme = nextToken();
    return !currentLexeme.getValue().empty();
}

void LexicalAnalyser::tokenizeInputFile(const std::string& sourceFilePath, const std::string& outputFilePath) {
    this->sourceFilePath = sourceFilePath;
    this->outputFilePath = outputFilePath;

    std::ofstream outputFile(outputFilePath);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }

    while (hasNextToken()) {
        auto currentLexeme = nextToken();
        outputFile << currentLexeme.getTokenType() << std::endl;

        std::regex idPattern("^id\\w*$", std::regex::icase);
        if (std::regex_match(currentLexeme.getTokenType(), idPattern)) {
            symbolTableHandler.addSymbol(currentLexeme.getValue());
        }
    }

    outputFile.close();
}

void LexicalAnalyser::logError(std::vector<char> fullBuffer, const int errorBackupIndex, const int i) const {
    const std::string errorSubstring(fullBuffer.begin() + errorBackupIndex - 1, fullBuffer.begin() + i);
    std::cerr << "Can't recognize token at index " + std::to_string(currentIndexInSource + i)
                     + ", problematic substring: \"" + errorSubstring + "\""
              << std::endl;
}

void LexicalAnalyser::reset() {
    this->currentState         = minimalDFAStartState;
    this->currentIndexInSource = 0;
    this->currentLexeme        = Lexeme();
}
