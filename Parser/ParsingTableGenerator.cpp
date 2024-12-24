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

void ParsingTableGenerator::findFirst() {
    for (auto nonTerminal : productions.keys()){
        if(grammar.nonTerminals[nonTerminal].getFirstSet().empty()){
            findFirstUtil(nonTerminal);
        }
    }
}
void ParsingTableGenerator::findFirstUtil(NonTerminal* nonTerminal) {
    string nonTerminalString = nonTerminal->getName();
    for (auto production : productions[nonTerminalString]){
        if (production[0].isTerminal()){
            grammar.nonTerminals[nonTerminalString].addToFirstSet(production[0]);
        }
        else{
            if(grammar.nonTerminals[production[0]].getFirstSet().empty()) {
                findFirstUtil(production[0]);
            }
            const auto& subFirstSet = production[0]->getFirstSet();
            nonTerminal->getFirstSet().insert(subFirstSet.begin(), subFirstSet.end());
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

void ParsingTableGenerator::findForwardUtil() {
    for (auto nonTerminal : productions){
        vector<NonTerminalOccurrence*> occurrences = grammar.nonTerminals[nonTerminal].getOccurrencePositions();
        for(const NonTerminalOccurrence& occurrence : occurrences){

        }
    }
}
void ParsingTableGenerator::findForward() {
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
    for(auto nonTerminal : grammar.nonTerminals){
        NonTerminal nonTerminalObj = grammar.nonTerminals[nonTerminal];
        for(const Terminal& first : nonTerminalObj.getFirstSet()){
            if(first.isNullable()){
                for(const Terminal& follow : nonTerminalObj.getFollowSet()){
                    parsingTable.table[no]
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

