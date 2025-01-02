//
// Created by husseinkhaled on 12/22/24.
//

#include "InputProgramParser.h"
#include "../Terminal.h"
#include "../ParsingTable.h"

using namespace std;

InputProgramParser::InputProgramParser(LexicalAnalyser* lexicalAnalyser, Grammar* grammar, ParsingTable* parsingTable) :
lexicalAnalyser(lexicalAnalyser), grammar(grammar), parsingTable(parsingTable) {
    remainingSymbols.push((Symbol*)Grammar::END);
    remainingSymbols.push(grammar->getStartSymbol());
}

void InputProgramParser::parseInputProgram(const string &outputFilePath, const string &debugFilePath) {
    output.open(outputFilePath);
    if (output.fail()) {
        cout << "Error: Unable to open output file." << endl;
        return;
    }
    debug.open(debugFilePath);
    if (debug.fail()) {
        cout << "Error: Unable to open debug file." << endl;
        return;
    }
    parse();
    output.close();
    debug.close();
}


bool InputProgramParser::handleTerminal(string &currentTokenName, bool &isInputEnd, Symbol *currentSymbol) {
    if (currentSymbol->getName() == currentTokenName) {
        // A match found
        debug << "Action: A match found for token: "<<getName(currentTokenName)<<endl;
        matchedTokens.emplace_back(currentSymbol);
        if (!lexicalAnalyser->hasNextToken()) {
            if (!isInputEnd) {
                // put $ manually in the input
                currentTokenName=Grammar::END->getName();
                isInputEnd=true;
            }
            // End of the input
            else {
                return true;
            }
        }
        else {
            currentTokenName=lexicalAnalyser->nextToken().getTokenType();
        }
    } else {
        debug << "Error: Expected token " << getName(currentSymbol->getName());
        debug << " but found "<<getName(currentTokenName)<<endl;
        debug << "Action: Inserting missing terminal " << currentSymbol->getName() << endl;
        matchedTokens.emplace_back(currentSymbol);
    }
    return false;
}

void InputProgramParser::handleNonTerminal(string &currentTokenName, bool &isInputEnd, const Symbol *currentSymbol) {
    const string& nonTerminalName = currentSymbol->getName();
    bool found = true;
    if (!parsingTable->table[nonTerminalName].contains(currentTokenName)) {
        debug << "Error: Unexpected token " << getName(currentTokenName)<< endl;
        debug<<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
        debug <<"Action: Ignore token "<<getName(currentTokenName)<<endl;
        debug<<"--------------------------------------------------------------------------------"<<endl;
        found = false;
        while (lexicalAnalyser->hasNextToken()) {
            currentTokenName=lexicalAnalyser->nextToken().getTokenType();
            debug<<"Current input token: "<<getName(currentTokenName)<<endl;
            if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                found = true;
                break;
            }
            debug << "Error: Unexpected token " << getName(currentTokenName)<< endl;
            debug<<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
            debug <<"Action: Ignore token "<<getName(currentTokenName)<<endl;
            debug<<"--------------------------------------------------------------------------------"<<endl;

        }
        if (!isInputEnd && !found) {
            currentTokenName=Grammar::END->getName();
            isInputEnd=true;
            debug<<"Current input token: "<<getName(currentTokenName)<<endl;
            if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                found = true;
            }
            debug << "Error: Unexpected token " << getName(currentTokenName)<< endl;
            debug <<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
            debug <<"Action: Ignore token "<<getName(currentTokenName)<<endl;
            debug<<"--------------------------------------------------------------------------------"<<endl;
        }
    }
    if (!found) {
        return;
    }
    const int index = parsingTable->table[nonTerminalName][currentTokenName];
    // sync
    if (index==ParsingTable::SYNC) {
        debug << "Error: Unexpected token " << getName(currentTokenName) << endl;
        debug <<"Entry is SYNC in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
        debug<<"Action: Need to synchronize and get next symbol"<<endl;
        return;
    }
    const vector<Symbol* > production = grammar->getProductions()[nonTerminalName][index];
    debug<<"Action: "<<getName(nonTerminalName)<<" -> ";
    for (int i = production.size() - 1; i >= 0; i--) {
        debug<<getName(production[i]->getName())<<" ";
        if (production[i]==Grammar::EPSILON) {
            break;
        }
        remainingSymbols.push(production[i]);
    }
    debug<<endl;
}

string InputProgramParser::getName(const string& currentName) {
    if (currentName==Grammar::END->getName()) {
        return "$";
    }
    if (currentName == Grammar::EPSILON->getName()) {
        return "Epsilon";
    }
    return currentName;
}

void InputProgramParser::parse() {
    if (!lexicalAnalyser->hasNextToken()) {
        debug << "Error: Empty input." << endl;
        return;
    }
    string currentTokenName=lexicalAnalyser->nextToken().getTokenType();
    bool isInputEnd=false;
    while (!remainingSymbols.empty()) {
        debug<<"--------------------------------------------------------------------------------"<<endl;
        printCurrentStack();
        Symbol* currentSymbol = remainingSymbols.top();
        if (!currentSymbol->isTerminal()) {
            printLeftMostDerivation();
        }
        remainingSymbols.pop();
        if (currentSymbol==Grammar::EPSILON) {
            continue;
        }
        debug<<"Current Top of the stack: "<<getName(currentSymbol->getName())<<endl;
        debug<<"Current input token: "<<getName(currentTokenName)<<endl;
        // If the current symbol is a terminal
        if (currentSymbol->isTerminal()) {
            if (handleTerminal(currentTokenName, isInputEnd, currentSymbol)) break;
        }
        else {
            handleNonTerminal(currentTokenName, isInputEnd, currentSymbol);
        }
    }
    if (remainingSymbols.empty() && lexicalAnalyser->hasNextToken()) {
        debug << "Error: Extra tokens in input." << endl;
        return;
    }
    if (!remainingSymbols.empty() && !lexicalAnalyser->hasNextToken()) {
        debug << "Error: Unexpected end of input." << endl;
        return;
    }
    printLeftMostDerivation();
    debug << "Parsing completed successfully." << endl;
}

void InputProgramParser::printLeftMostDerivation() {
    vector<Symbol* > leftMostDerivation;
    while (!remainingSymbols.empty() && remainingSymbols.top()!=Grammar::END) {
        leftMostDerivation.push_back(remainingSymbols.top());
        remainingSymbols.pop();
    }
    for (const auto symbol:matchedTokens) {
        if (symbol==Grammar::END) {
            continue;
        }
        output<<symbol->getName()<<" ";
    }
    for (const auto symbol:leftMostDerivation) {
        output<<symbol->getName()<<" ";
    }
    output<<endl;
    for (int i = leftMostDerivation.size() - 1; i >= 0; i--) {
        remainingSymbols.push(leftMostDerivation[i]);
    }
}

void InputProgramParser::printCurrentStack() {
    debug << "Current stack: ";
    stack<Symbol*> temp;
    while (!remainingSymbols.empty()) {
        temp.push(remainingSymbols.top());
        remainingSymbols.pop();
    }
    while (!temp.empty()) {
        debug << getName(temp.top()->getName()) << " ";
        remainingSymbols.push(temp.top());
        temp.pop();
    }
    debug << endl;
}

