//
// Created by mariam on 12/22/2024.
//

#include "ParsingTableGenerator.h"
#include "ParsingTable.h"
#include "Grammar.h"


void ParsingTableGenerator::findFirstUtil() {
    for (const auto& nonTerminal : views::values(grammar->getNonTerminals())) {
            findFirst(nonTerminal);
    }
}
void ParsingTableGenerator::findFirst(NonTerminal* nonTerminal) {
    if(!nonTerminal->getFirstSet().empty()) return;

    const auto& derivations = grammar->getProductions()[nonTerminal->getName()];

    for (const auto& derivation : derivations) {
        Symbol* firstSymbol = derivation.front();

        if (firstSymbol->isTerminal()){
            nonTerminal->addToFirstSet(dynamic_cast<Terminal*>(firstSymbol));
        }
        else{
            auto* nonTerminalSymbol = dynamic_cast<NonTerminal*>(firstSymbol);
            findFirst(nonTerminalSymbol);
            nonTerminal-> addToFirstSet(nonTerminalSymbol->getFirstSet());
        }
    }
}

void ParsingTableGenerator::findFollowUtil()  {
    for (const auto &nonTerminal: views::values(grammar->getNonTerminals())) {
        findFollow(nonTerminal);
    }
}

void ParsingTableGenerator:: findFollow(NonTerminal* nonTerminal){
    if (!nonTerminal->getFollowSet().empty()) return;
    if(nonTerminal == grammar->getStartSymbol()){
        auto* endTerminal =new Terminal(Grammar::END->getName());
        grammar->getStartSymbol()->addToFollowSet(endTerminal);
    }
    auto occurrences = nonTerminal->getOccurrencePositions();
    for(const auto occurrence : occurrences){
        const auto LHS = occurrence->nonTerminal;
        auto derivation = grammar->getProductions()[LHS->getName()][occurrence->derivationIndex];
        //case last
        if (occurrence->inDerivationIndex == derivation.size() - 1) {
            if (LHS == derivation[occurrence->inDerivationIndex]) continue;
            findFollow(LHS);
            nonTerminal->addToFollowSet(LHS->getFollowSet());
        }
        else{
            auto nextDerivative = derivation[occurrence->inDerivationIndex + 1];
            if (nextDerivative->isTerminal())
            {
                nonTerminal->addToFollowSet(dynamic_cast<Terminal*>(nextDerivative));
            }
            else
            {
                auto* nextDerivativeNT = dynamic_cast<NonTerminal*>(nextDerivative);
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

            }
        }
    }
}

void ParsingTableGenerator::addToParsingTable(ParsingTable& parsingTable, const string& nonTerminalString, Symbol* firstSymbol, int index) {
    // Check if the terminal is already in the table for the non-terminal
    if (parsingTable.table[nonTerminalString].find(firstSymbol->getName()) != parsingTable.table[nonTerminalString].end()) {
        throw std::runtime_error("Error: language is not LL(1) - conflict detected for "
                                 + nonTerminalString + " and " + firstSymbol->getName());
    }
    // If no conflict, add the rule to the parsing table
    parsingTable.table[nonTerminalString][firstSymbol->getName()] = index;
}

ParsingTable ParsingTableGenerator::generateParsingTable() {
    findFirstUtil();
    findFollowUtil();
    ParsingTable parsingTable;
     for(auto& [nonTerminalString , nonTerminalObj]  : grammar->getNonTerminals()){
         auto derivations = grammar->getProductions()[nonTerminalString];
         for (int index = 0; index < derivations.size(); index++){
             auto derivation = derivations[index];
             Symbol* firstSymbol = derivation.front();
             if (firstSymbol->isTerminal()){
                 if(firstSymbol == Grammar::EPSILON){
                     for (auto follow : nonTerminalObj->getFollowSet()) {
                         addToParsingTable(parsingTable, nonTerminalString, follow, index);
                     }
                 }
                 else {
                     addToParsingTable(parsingTable, nonTerminalString, firstSymbol, index);
                 }
             }
             else{
                 auto firstNonTerminal = dynamic_cast<NonTerminal*>(firstSymbol)->getFirstSet();
                 for(auto first : firstNonTerminal){
                     if(first == Grammar::EPSILON){
                         auto* firstNonTerminalObj = dynamic_cast<NonTerminal*>(firstSymbol);
                         if (firstNonTerminalObj) {
                             for (auto follow : firstNonTerminalObj->getFollowSet()) {
                                 addToParsingTable(parsingTable, nonTerminalString, follow, index);
                             }
                         }
                     }
                     else{
                         addToParsingTable(parsingTable, nonTerminalString, first, index);

                     }
                 }
             }
         }
         if(!nonTerminalObj->isNullable()){
             for(const auto follow:nonTerminalObj->getFollowSet()){
                 addToParsingTable(parsingTable,nonTerminalString,follow,ParsingTable::SYNC);
             }
         }
     }
     return parsingTable ;
}


void ParsingTableGenerator::printFirstAndFollow() {
    cout << "First and Follow Sets for Non-Terminals:" << endl;
    for (const auto& [nonTerminalString, nonTerminalObj] : grammar->getNonTerminals()) {
        // Print the First set
        cout << "Non-Terminal: " << nonTerminalString << endl;

        cout << "  First: { ";
        for (const auto terminal : nonTerminalObj->getFirstSet()) {
            if (terminal == Grammar::EPSILON)
                cout << "epsilon ";
            else cout << terminal->getName() << ", ";
        }
        cout << "}" << endl;
        // Print the Follow set
        cout << "  Follow: { ";
        for (const auto terminal : nonTerminalObj->getFollowSet()) {
            cout << terminal->getName() << ", ";
        }
        cout << "}" << endl;

        cout << endl;
    }
}