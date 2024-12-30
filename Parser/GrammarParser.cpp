//
// Created by mohamed_anwar on 12/24/24.
//

#include "GrammarParser.h"
#include "ParserState.h"
#include "LHSState.h"
#include "ParserUtils.h"

GrammarParser::GrammarParser(const string& fileName):
    currentState(new LHSState()),
    grammar(new Grammar()),
    currentNonTerminal(nullptr) {

    inputFilePath.open(fileName);
    if (!inputFilePath.is_open())
        throw ios_base::failure("Failed to open file: " + fileName);
}

void GrammarParser::readNonTerminals(const string& buffer) {
    const int bufferSize = buffer.size();
    string currentLHS = "";

    int index = 1;

    while (index < bufferSize) {

        if (string assignment = buffer.substr(index, 3); assignment == "::=") {
            trim(currentLHS);
            validateNonTerminal(currentLHS);

            grammar->addNonTerminal(new NonTerminal(currentLHS));

            if (grammar->getStartSymbol() == nullptr)
                grammar->setStartSymbol(grammar->getNonTerminals()[currentLHS]);

            while (buffer[index] != '#' and index < bufferSize)
                index++;

            index++;
            currentLHS = "";
            continue;
        }

        currentLHS += buffer[index++];
    }
}

Grammar* GrammarParser::parseGrammar() {
    string buffer = readInputFile();

    trim(buffer);
    readNonTerminals(buffer);

    int index = 1;
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
