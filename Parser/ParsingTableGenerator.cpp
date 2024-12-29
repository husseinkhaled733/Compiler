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
    for (const auto& nonTerminal : views::values(grammar->getNonTerminals())) {
        if(nonTerminal->getFirstSet().empty()){
            findFirst(nonTerminal);
        }
    }
}
void ParsingTableGenerator::findFirst(NonTerminal* nonTerminal) {
    string nonTerminalString = nonTerminal->getName();
    auto derivations = grammar->getProductions()[nonTerminalString];
    for (int index = 0; derivations.size(); index++)
    {
        auto derivation = derivations[index];
        Symbol* firstSymbol = derivation.front();
        if (firstSymbol->isTerminal()){
            setOccurrenceInDerivations(dynamic_cast<Terminal*>(firstSymbol), index);
            nonTerminal->addToFirstSet(dynamic_cast<Terminal*>(firstSymbol));
        }
        else{
            if(grammar->getNonTerminals()[firstSymbol->getName()]->getFirstSet().empty()) {
                findFirst(dynamic_cast<NonTerminal*>(firstSymbol));
            }
            nonTerminal-> addToFirstSet(dynamic_cast<NonTerminal*>(firstSymbol)->getFirstSet());
        }
    }
}
void ParsingTableGenerator::setOccurrenceInDerivations(Terminal* firstSymbol, int index)
{
    if (firstSymbol->getOccurrenceInDerivations() != -1) {
        cout<<"ERROR";
    } else {
        firstSymbol->setOccurrenceInDerivations(index);
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
        NonTerminal* nonTerminal;    LHS => a a a | b b b
        int derivationIndex;
        int inDerivationIndex;

        NonTerminalOccurrence(NonTerminal* nt, const int derivationIdx, const int inDerivationIdx)
            : nonTerminal(nt), derivationIndex(derivationIdx), inDerivationIndex(inDerivationIdx) {}
    };
 */

void ParsingTableGenerator:: findFollow(NonTerminal* nonTerminal){
    if (!nonTerminal->getFollowSet().empty()) return;
    auto occurrences = nonTerminal->getOccurrencePositions();
    // Non Terminal (LHS) => aaa | ddd | ddd
    for(const auto occurrence : occurrences){
        // in case it is the last
        // in case the next exists
        // F => T X Y
        const auto LHS = occurrence->nonTerminal;

        vector<vector<Symbol*>> derivations = grammar->getProductions()[LHS->getName()];

        auto derivation = derivations[occurrence->derivationIndex];

        if (occurrence->inDerivationIndex == derivation.size() - 1)
        {
            // case last
            if (LHS == derivation[occurrence->inDerivationIndex])
            {

                if (LHS == derivation[occurrence->inDerivationIndex]) continue;
                // get the follow of LHS
                // if it includes epsilon then get its follow
                findFollow(LHS);
                nonTerminal->addToFollowSet(LHS->getFollowSet());
            }
            else
            {
                auto nextDerivative = derivation[occurrence->inDerivationIndex + 1];
                if (nextDerivative->isTerminal())
                {
                    nonTerminal->addToFollowSet(dynamic_cast<Terminal*>(nextDerivative));
                }
                else
                {
                    NonTerminal* nextDerivativeNT = dynamic_cast<NonTerminal*>(nextDerivative);
                    for (auto first: nextDerivativeNT->getFirstSet())
                    {
                        if (first == Grammar::EPSILON)
                        {
                            findFollow(nextDerivativeNT);
                            nonTerminal->addToFollowSet(nextDerivativeNT->getFollowSet());
                        } else
                        {
                            nonTerminal->addToFollowSet(first);
                        }
                    }
                    // if (
                    // nonTerminal->isNullable())
                    // {
                    //     findFollow(LHS);
                    //     nonTerminal->getFollowSet().erase(grammar->EPSILON);
                    //     nonTerminal->addToFollowSet(LHS->getFollowSet());
                    // }
                }
            }
        }
    }

}
void ParsingTableGenerator::findFollowUtil()
{

    for (const auto& nonTerminal : views::values(grammar->getNonTerminals()))
    {
        findFollow(nonTerminal);
    }
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
public:
    const int SYNC = -1;
    unordered_map<string, unordered_map<string, int>> table;
};
 */
ParsingTable ParsingTableGenerator::generateParsingTable() {
     ParsingTable parsingTable;
     for(auto [nonTerminalString , nonTerminalObj]  : grammar->getNonTerminals()){
         for(auto first : nonTerminalObj->getFirstSet()){
             if(first == Grammar::EPSILON){
                 for(auto follow : nonTerminalObj->getFollowSet()){
                     parsingTable.table[nonTerminalString][follow->getName()] = follow->getOccurrenceInDerivations();
                 }
             }
             else{
                 parsingTable.table[nonTerminalString][first ->getName()] = first->getOccurrenceInDerivations();
             }
         }
     }
     return parsingTable ;
}
ParsingTableGenerator::ParsingTableGenerator(Grammar* grammar) {
    grammar = grammar;
}

