//
// Created by mohamed_anwar on 12/25/24.
//

#include "RHSState.h"
#include "LHSState.h"
#include "ParserUtils.h"

Terminal* RHSState::parseTerminal(const GrammarParser& parser, const string& buffer, int& index) {
    string terminalName;
    index++;

    const set endChars = {'|', '#', '\''};
    while (buffer[index] != '\'' and index < buffer.size()) {
        // escape
        if (buffer[index] == '\\') {
            if (index + 1 == buffer.size())
                throw std::invalid_argument("Terminal is not complete: " + terminalName);

            if (endChars.contains(buffer[index + 1])) {
                terminalName += buffer[index + 1];
                index += 2;
                continue;
            }
        }

        if (endChars.contains(buffer[index]) and buffer[index] != '\'')
            throw std::invalid_argument("Terminal is not complete: " + terminalName);

        terminalName += buffer[index++];
    }

    if (index == buffer.size() or terminalName.empty()) {
        const string logMessage = "Terminal is not complete: " + terminalName
            + ", In Non-terminal: " + parser.getCurrentNonTerminal()->getName()
            + ", At index: " + to_string(index);

        throw std::invalid_argument(logMessage);
    }

    index++;
    return new Terminal(terminalName);
}

NonTerminal::NonTerminalOccurrence* createNonTerminalOccurrence(
    const GrammarParser& parser, const string& buffer,
    const int& index, const int inDerivationIndex) {
    NonTerminal* currentNonTerminal = parser.getCurrentNonTerminal();
    const int currentDerivationIndex = parser.getGrammar()
                                             ->getProductions()[currentNonTerminal->getName()].size();
    const int currentInDerivationIndex = inDerivationIndex;
    return new NonTerminal::NonTerminalOccurrence(
        currentNonTerminal, currentDerivationIndex, currentInDerivationIndex
    );
}

NonTerminal* RHSState::parseNonTerminal(const GrammarParser& parser,
                                        const string& buffer,
                                        int& index,
                                        const int inDerivationIndex) {
    const auto occurrence = createNonTerminalOccurrence(parser, buffer, index, inDerivationIndex);

    const auto nonTerminals
        = parser.getGrammar()->getNonTerminals();
    const set endChars = {'|', '#', '\''};

    string currentNonTerminalName = "";
    string longestNonTerminalName = "";
    int currentLongestNonTerminalEndIndex = index;

    while (index < buffer.size() and !endChars.contains(buffer[index])) {
        currentNonTerminalName += buffer[index++];
        if (nonTerminals.contains(currentNonTerminalName)) {
            longestNonTerminalName = currentNonTerminalName;
            currentLongestNonTerminalEndIndex = index;
        }
    }

    if (!nonTerminals.contains(longestNonTerminalName)) {
        const int firstWhiteSpaceIndex = currentNonTerminalName.find_first_of(" \t\n\r", 0);
        throw invalid_argument("Non-terminal not found: " +
            currentNonTerminalName.substr(0, firstWhiteSpaceIndex));
    }

    index = currentLongestNonTerminalEndIndex;
    nonTerminals.at(longestNonTerminalName)->addOccurrence(occurrence);
    return nonTerminals.at(longestNonTerminalName);
}

void validateEpsilonProduction(NonTerminal* currentNonTerminal, const GrammarParser& parser) {
    if (currentNonTerminal == nullptr)
        return;

    const auto& productions = parser.getGrammar()->getProductions()
        [currentNonTerminal->getName()];

    for (const auto& production : productions) {
        if (production.size() == 1) {
            if (Symbol* symbol = production[0];
                dynamic_cast<Terminal*>(symbol) && symbol == Grammar::EPSILON) {
                currentNonTerminal->setNullable(true);
                break;
            }
        }
    }
}


void RHSState::parse(GrammarParser& parser, const string& buffer, int& index) {
    const int bufferSize = buffer.size();

    NonTerminal* currentNonTerminal = parser.getCurrentNonTerminal();
    vector<Symbol*> production;

    while (index < bufferSize) {
        char c = buffer[index];

        // end of definition
        if (buffer[index] == '#') {
            parser.setState(new LHSState());
            parser.setCurrentNonTerminal(nullptr);
            parser.getGrammar()->addProduction(currentNonTerminal, production);
            validateEpsilonProduction(currentNonTerminal, parser);
            index++;
            return;
        }

        // ignoring
        if (Grammar::IGNORED_CHARS.contains(buffer[index])) {
            index++;
            continue;
        }

        // terminal
        if (buffer[index] == '\'') {
            auto terminal = parseTerminal(parser, buffer, index);
            if (terminal->getName() == "\\L")
                terminal = Grammar::EPSILON;
            production.push_back(terminal);
            continue;
        }

        // end of production
        if (buffer[index] == '|') {
            if (production.empty())
                throw invalid_argument("Empty production in Non-terminal: " + currentNonTerminal->getName()
                    + ", At index: " + to_string(index));

            parser.getGrammar()->addProduction(currentNonTerminal, production);
            production.clear();
            index++;
            continue;
        }

        // non-terminal
        const auto nonTerminal = parseNonTerminal(parser, buffer, index, production.size());
        production.push_back(nonTerminal);
    }

    if (!production.empty())
        parser.getGrammar()->addProduction(currentNonTerminal, production);

    validateEpsilonProduction(currentNonTerminal, parser);
}
