//
// Created by mohamed_anwar on 12/25/24.
//

#include "RHSState.h"
#include "LHSState.h"

Terminal* RHSState::parseTerminal(const GrammarParser& parser, const string& buffer, int& index) {
    string terminalName;
    index++;
    while (buffer[index] != '\'' and index < buffer.size()) {
        // escape
        if (buffer[index] == '\\' and buffer[index + 1] == '\'') {
            terminalName += '\'';
            index += 2;
            continue;
        }
        terminalName += buffer[index++];
    }

    if (index == buffer.size() or terminalName.empty())
        throw std::invalid_argument("Terminal is not complete: " + terminalName);

    index++;

    const auto terminal = new Terminal(terminalName);
    parser.getGrammar()->addTerminal(terminal);
    return terminal;
}

NonTerminal* RHSState::parseNonTerminal(const GrammarParser& parser, const string& buffer, int& index) {
    NonTerminal* currentNonTerminal = parser.getCurrentNonTerminal();
    const int currentDerivationIndex = parser.getGrammar()
        ->getProductions()[currentNonTerminal->getName()].size();
    const int currentInDerivationIndex = index;

    string nonTerminalName = "";
    const auto nonTerminals
        = parser.getGrammar()->getNonTerminals();
    const set endChars = {'|', '#', '\''};

    while (!nonTerminals.contains(nonTerminalName) and index < buffer.size()) {
        if (endChars.contains(buffer[index]))
            throw invalid_argument("Non-terminal not found: " + nonTerminalName);
        nonTerminalName += buffer[index++];
    }

    if (index == buffer.size())
        throw invalid_argument("Non-terminal not found: " + nonTerminalName);

    const auto nonTerminal = new NonTerminal(nonTerminalName);
    parser.getGrammar()->addNonTerminal(nonTerminal);
    currentNonTerminal->addOccurrence(nonTerminal, currentDerivationIndex, currentInDerivationIndex);
    return nonTerminal;
}

void RHSState::parse(GrammarParser& parser, const string& buffer, int& index) {
    const int bufferSize = buffer.size();

    NonTerminal* currentNonTerminal = parser.getCurrentNonTerminal();
    vector<Symbol*> production;

    while (index < bufferSize) {
        // end of definition
        if (buffer[index] == '#') {
            parser.setState(new LHSState());
            parser.setCurrentNonTerminal(nullptr);
            parser.getGrammar()->addProduction(currentNonTerminal, production);
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
            const auto terminal = parseTerminal(parser, buffer, index);
            if (terminal->getName() == "\\L")
                currentNonTerminal->setNullable(true);
            production.push_back(terminal);
            continue;
        }

        // end of production
        if (buffer[index] == '|') {
            parser.getGrammar()->addProduction(currentNonTerminal, production);
            production.clear();
            index++;
            continue;
        }

        // non-terminal
        const auto nonTerminal = parseNonTerminal(parser, buffer, index);
        production.push_back(nonTerminal);

        index++;
    }

    if (!production.empty())
        parser.getGrammar()->addProduction(currentNonTerminal, production);
}
