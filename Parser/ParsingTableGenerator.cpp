//
// Created by mariam on 12/22/2024.
//

#include "ParsingTableGenerator.h"
#include "ParsingTable.h"
#include "Grammar.h"

/* grammar have
 *  unordered_map<string, NonTerminal*> nonTerminals;
    unordered_map<string, vector<vector<Symbol*>>> productions;
 */

void ParsingTableGenerator::findFirstUtil() {
    for (const auto& nonTerminal : views::values(grammar->nonTerminals)){
        if(nonTerminal->getFirstSet().empty()){
            findFirst(nonTerminal);
        }
    }
}
void ParsingTableGenerator::findFirst(NonTerminal* nonTerminal) {
    string nonTerminalString = nonTerminal->getName();
    for (auto production : grammar->productions[nonTerminalString]){
        Symbol* firstSymbol = production.front();
        if (firstSymbol->isTerminal()){
            grammar->nonTerminals[nonTerminalString]->addToFirstSet(dynamic_cast<Terminal*>(firstSymbol));
        }
        else{
            if(grammar->nonTerminals[firstSymbol->getName()]->getFirstSet().empty()) {
                findFirst(dynamic_cast<NonTerminal*>(firstSymbol));
            }
            nonTerminal-> addToFirstSet(dynamic_cast<NonTerminal*>(firstSymbol)->getFirstSet());
        }
    }
}
// iterate over key of the production for each non-terminal  do
// iterate for each entry on the right hand side
// for first symbol in the entry
// if it's terminal -> you found the first (update FIRST map)
// else -> check the first
// if the current symbol is calculated -> we found the FIRST
// else  -> call FIRST(current non-terminal)
/*
 * class NonTerminalOccurrence {
    public:
        NonTerminal* nonTerminal;
        int derivationIndex;
        int inDerivationIndex;

        NonTerminalOccurrence(NonTerminal* nt, const int derivationIdx, const int inDerivationIdx)
            : nonTerminal(nt), derivationIndex(derivationIdx), inDerivationIndex(inDerivationIdx) {}
    };
 */

void ParsingTableGenerator:: findFollow(NonTerminal* nonTerminal){
    for (const auto& nonTerminal : views::values(grammar->nonTerminals))
    {
        auto occurrences = nonTerminal->getOccurrencePositions();
        for(const auto occurrence : occurrences){
            grammar->productions[occurrence->nonTerminal]

        }
    }

}
void ParsingTableGenerator::findFollowUtil()
{
    // iterate over key of the production for each non-terminal do
        // iterate over occurrences of this non-terminal
            // for each occurrence
                // if it's not the last symbol -> put the forward of current as first of next
                // else ->
                    // if the forward of its non-terminal calculated -> put the forward of the current  as forward of
                    // else calculate the forward
}
/*
  class ParsingTable {
    const int SYNC = -1;
    unordered_map<NonTerminal*, unordered_map<Terminal*, int>> table;
};
 */
ParsingTable ParsingTableGenerator::generateParsingTable() {
    ParsingTable parsingTable;
    for(auto [nonTerminalString , nonTerminalObj]  : grammar->nonTerminals){
        for(const Terminal& first : nonTerminalObj->getFirstSet()){
            if(first.getName() == grammar->EPSILON){
                for(const Terminal& follow : nonTerminalObj->getFollowSet()){
                    parsingTable.table[nonTerminalString][follow.getName()] = ;
                }

            }
            else{
                
            }
        }
    }
    return parsingTable;
}

ParsingTableGenerator::ParsingTableGenerator(Grammar* grammar) {

}

