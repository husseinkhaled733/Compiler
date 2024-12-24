//
// Created by mohamed_anwar on 12/22/24.
//

#include "Grammar.h"

const Terminal* Grammar::EPSILON = new Terminal(std::string(1, 0));
const Terminal* Grammar::END = new Terminal(std::string(1, 1));
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

unordered_map<string, Terminal*>& Grammar::getTerminals() {
    return terminals;
}

unordered_map<string, vector<vector<Symbol*>>>& Grammar::getProductions() {
    return productions;
}

void Grammar::addTerminal(Terminal* terminal) {
    terminals[terminal->getName()] = terminal;
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
    cout << "Non Terminals: " << endl;
    for (const auto& [name, nonTerminal] : nonTerminals) {
        cout << name << " ";
    }
    cout << endl;
    cout << "Terminals: " << endl;
    for (const auto& [name, terminal] : terminals) {
        cout << name << " ";
    }
    cout << endl;
    cout << "Productions: " << endl;
    for (const auto& [name, productions] : productions) {
        cout << name << " -> ";
        for (const auto& production : productions) {
            for (const auto& symbol : production) {
                cout << symbol->getName() << " ";
            }
            cout << "| ";
        }
        cout << endl;
    }
    cout << "===================================" << endl;
    cout << "           END OF GRAMMAR           " << endl;
    cout << "===================================" << endl;
}