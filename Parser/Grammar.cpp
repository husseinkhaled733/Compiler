//
// Created by mohamed_anwar on 12/22/24.
//

#include "Grammar.h"

const Terminal* Grammar::EPSILON = new Terminal(std::string(1, 0));
const Terminal* Grammar::END = new Terminal(std::string(1, 1));

Grammar::Grammar() {
    startSymbol = nullptr;
}

NonTerminal* Grammar::getStartSymbol() const {
    return startSymbol;
}

std::unordered_map<std::string, NonTerminal*>& Grammar::getNonTerminals() {
    return nonTerminals;
}

std::unordered_map<std::string, Terminal*>& Grammar::getTerminals() {
    return terminals;
}

std::unordered_map<std::string, std::vector<std::vector<Symbol*>>>& Grammar::getProductions() {
    return productions;
}