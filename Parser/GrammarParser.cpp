//
// Created by mohamed_anwar on 12/24/24.
//

#include "GrammarParser.h"
#include "ParserState.h"
#include "LHSState.h"

GrammarParser::GrammarParser(const std::string& fileName):
    currentState(new LHSState()),
    grammar(new Grammar()),
    currentNonTerminal(nullptr) {

    inputFilePath.open(fileName);
    if (!inputFilePath.is_open())
        throw std::ios_base::failure("Failed to open file: " + fileName);
}

int getStartIndex(const string& buffer) {
    int startIndex = 0;
    while (buffer[startIndex] != '#')
        startIndex++;
    return startIndex + 1;
}

bool isWordCharacter(const char c) {
    return isalnum(static_cast<unsigned char>(c)) || c == '_';
}

void GrammarParser::readNonTerminals(const string& buffer) {
    const int bufferSize = buffer.size();
    string currentLHS = "";
    int index = getStartIndex(buffer);

    while (index < bufferSize) {
        if (Grammar::IGNORED_CHARS.contains(buffer[index])) {
            index++;
            continue;
        }

        if (!isWordCharacter(buffer[index]))
            throw invalid_argument("Invalid character in LHS: " +
                string(1, buffer[index]));

        if (string assignment = buffer.substr(index, 3); assignment == "::=") {
            grammar->addNonTerminal(new NonTerminal(currentLHS));
            while (buffer[index] != '#') index++;
            index++;
            currentLHS = "";
            continue;
        }

        currentLHS += buffer[index];
        index++;
    }
}

Grammar* GrammarParser::parseGrammar() {
    const string buffer = readInputFile();
    readNonTerminals(buffer);

    int index = getStartIndex(buffer);
    while (index < buffer.size())
        currentState->parse(*this, buffer, index);

    return grammar;
}

string GrammarParser::readInputFile() {
    vector<string> lines;

    string line;
    while (getline(inputFilePath, line)) lines.push_back(line);

    string buffer = "";
    ranges::for_each(lines, [&](const string& _line) {
        for (const char c : _line) buffer.push_back(c);
    });

    return buffer;
}

Grammar* GrammarParser::getGrammar() const {
    return grammar;
}

void GrammarParser::setState(ParserState* state) {
    delete currentState;
    currentState = state;
}

NonTerminal* GrammarParser::getCurrentNonTerminal() const {
    return currentNonTerminal;
}

void GrammarParser::setCurrentNonTerminal(NonTerminal* nonTerminal) {
    currentNonTerminal = nonTerminal;
}

GrammarParser::~GrammarParser() {
    delete currentState;
    delete grammar;
    inputFilePath.close();
}
