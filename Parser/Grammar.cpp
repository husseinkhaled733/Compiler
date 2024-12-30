//
// Created by mohamed_anwar on 12/22/24.
//

#include "Grammar.h"

Terminal* Grammar::EPSILON = new Terminal(std::string(1, 0));
Terminal* Grammar::END = new Terminal(std::string(1, 1));
const std::set<std::string> Grammar::RESERVED_SYMBOLS = {
    "::=",
    "|",
    "\\L",
    "'",
    "\\",
    "#"
};

const std::set<char> Grammar::IGNORED_CHARS = {
    ' ',
    '\t',
    '\n',
    '\r'
};

Grammar::Grammar() {
    startSymbol = nullptr;
}

NonTerminal* Grammar::getStartSymbol() const {
    return startSymbol;
}

unordered_map<string, NonTerminal*>& Grammar::getNonTerminals() {
    return nonTerminals;
}

unordered_map<string, vector<vector<Symbol*>>>& Grammar::getProductions() {
    return productions;
}

void Grammar::addNonTerminal(NonTerminal* nonTerminal) {
    nonTerminals[nonTerminal->getName()] = nonTerminal;
}

void Grammar::setStartSymbol(NonTerminal* startSymbol) {
    this->startSymbol = startSymbol;
}

void Grammar::addProduction(NonTerminal* nonTerminal, vector<Symbol*> production) {
    productions[nonTerminal->getName()].push_back(production);
}

void Grammar::printGrammar() const {
    cout << "===================================" << endl;
    cout << "              GRAMMAR               " << endl;
    cout << "===================================" << endl;
    cout << "Start Symbol: " << startSymbol->getName() << endl;
    cout << "===================================" << endl;
    cout << "Non Terminals: " << endl;

    for (const auto& [name, nonTerminal] : nonTerminals) {
        cout << "Name: " << name << endl;
        cout << "Has Epsilon Transition: " << (nonTerminal->isNullable() ? "Yes" : "No") << endl;

        cout << "First Set: { ";
        for (const auto& terminal : nonTerminal->getFirstSet()) {
            cout << terminal->getName() << " ";
        }
        cout << "}" << endl;

        cout << "Follow Set: { ";
        for (const auto& terminal : nonTerminal->getFollowSet()) {
            cout << terminal->getName() << " ";
        }
        cout << "}" << endl;

        cout << "Occurrence Positions: [" << endl;
        for (const auto& occurrence : nonTerminal->getOccurrencePositions()) {
            cout << "  {NonTerminal: " << occurrence->nonTerminal->getName()
                 << ", Derivation Index: " << occurrence->derivationIndex
                 << ", In-Derivation Index: " << occurrence->inDerivationIndex << "}," << endl;
        }
        cout << "]" << endl;

        cout << "-----------------------------------" << endl;
    }

    cout << endl;
    cout << "===================================" << endl;
    cout << "Productions: " << endl;

    for (const auto& [name, productions] : productions) {
        cout << name << " -> ";
        for (size_t i = 0; i < productions.size(); ++i) {
            const auto& production = productions[i];
            for (const auto& symbol : production) {
                const auto symbolName = symbol->isTerminal() ? "'" + symbol->getName() + "'" : symbol->getName();
                cout << symbolName << " ";
            }
            if (i < productions.size() - 1)
                cout << "| ";
        }
        cout << endl;
    }

    cout << "===================================" << endl;
    cout << "           END OF GRAMMAR           " << endl;
    cout << "===================================" << endl;
}