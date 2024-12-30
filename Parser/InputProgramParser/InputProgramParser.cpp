//
// Created by husseinkhaled on 12/22/24.
//

#include "InputProgramParser.h"
#include "../Terminal.h"
#include "../ParsingTable.h"
#include <utility>

using namespace std;

InputProgramParser::InputProgramParser(LexicalAnalyser* lexicalAnalyser, Grammar* grammar, ParsingTable* parsingTable) :
lexicalAnalyser(lexicalAnalyser), grammar(grammar), parsingTable(parsingTable) {
    remainingSymbols.push((Symbol*)Grammar::END);
    remainingSymbols.push(grammar->getStartSymbol());
}

void InputProgramParser::parseInputProgram(const string &outputFilePath) {
    output.open(outputFilePath);
    if (output.fail()) {
        cout << "Error: Unable to open output file." << endl;
        return;
    }
    parse();
    output.close();
}


bool InputProgramParser::handleTerminal(string &currentTokenName, bool &isInputEnd, Symbol *currentSymbol) {
    if (currentSymbol->getName() == currentTokenName) {
        // A match found
        cout << "A match found for token: "<<getName(currentTokenName)<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
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
        cout << "Error: Expected token " << getName(currentSymbol->getName());
        cout << " but found "<<getName(currentTokenName)<<endl;
        cout << "Inserting missing terminal " << currentSymbol->getName() << endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        matchedTokens.emplace_back(currentSymbol);
    }
    return false;
}

void InputProgramParser::handleNonTerminal(string &currentTokenName, bool &isInputEnd, const Symbol *currentSymbol) {
    const string nonTerminalName = currentSymbol->getName();
    bool found = true;
    if (!parsingTable->table[nonTerminalName].contains(currentTokenName)) {
        cout << "Error: Unexpected token " << getName(currentTokenName)<< endl;
        cout<<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
        cout <<"Ignore token "<<getName(currentTokenName)<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        found = false;
        while (lexicalAnalyser->hasNextToken()) {
            currentTokenName=lexicalAnalyser->nextToken().getTokenType();
            if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                found = true;
                break;
            }
            cout << "Error: Unexpected token " << getName(currentTokenName)<< endl;
            cout<<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
            cout<<"Ignore token "<<getName(currentTokenName)<<endl;
            cout<<"--------------------------------------------------------------------------------"<<endl;
        }
        if (!isInputEnd && !found) {
            currentTokenName=Grammar::END->getName();
            isInputEnd=true;
            if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                found = true;
            }
            cout << "Error: Unexpected token " << getName(currentTokenName)<< endl;
            cout <<"Entry not found in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
            cout <<"Ignore token "<<getName(currentTokenName)<<endl;
            cout<<"--------------------------------------------------------------------------------"<<endl;
        }
    }
    if (!found) {
        return;
    }
    const int index = parsingTable->table[nonTerminalName][currentTokenName];
    // sync
    if (index==parsingTable->SYNC) {
        cout << "Error: Unexpected token " << getName(currentTokenName) << endl;
        cout <<"Entry is SYNC in parsing table for non-terminal "<<getName(nonTerminalName)<<" and token "<<getName(currentTokenName)<<endl;
        cout<<"Need to synchronize and get next symbol"<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        return;
    }
    const vector<Symbol* > production = grammar->getProductions()[nonTerminalName][index];
    cout<<"Production: ";
    for (int i = production.size() - 1; i >= 0; i--) {
        cout<<getName(production[i]->getName())<<" ";
        if (production[i]==Grammar::EPSILON) {
            break;
        }
        remainingSymbols.push(production[i]);
    }
    cout<<endl;
}

string InputProgramParser::getName(const string& currentName) {
    if (currentName==Grammar::END->getName()) {
        return "$";
    }
    if (currentName == Grammar::EPSILON->getName()) {
        return "E";
    }
    return currentName;
}

void InputProgramParser::parse() {
    if (!lexicalAnalyser->hasNextToken()) {
        cout << "Error: Empty input." << endl;
        return;
    }
    string currentTokenName=lexicalAnalyser->nextToken().getTokenType();
    bool isInputEnd=false;
    while (!remainingSymbols.empty()) {
        cout<<"--------------------------------------------------------------------------------"<<endl;
        Symbol* currentSymbol = remainingSymbols.top();
        if (!currentSymbol->isTerminal()) {
            printLeftMostDerivation();
        }
        remainingSymbols.pop();
        if (currentSymbol==Grammar::EPSILON) {
            continue;
        }
        cout<<"Current Symbol: "<<getName(currentSymbol->getName())<<endl;
        cout<<"Current token: "<<getName(currentTokenName)<<endl;
        // If the current symbol is a terminal
        if (currentSymbol->isTerminal()) {
            if (handleTerminal(currentTokenName, isInputEnd, currentSymbol)) break;
        }
        else {
            handleNonTerminal(currentTokenName, isInputEnd, currentSymbol);
        }
    }
    if (remainingSymbols.empty() && lexicalAnalyser->hasNextToken()) {
        cout << "Error: Extra tokens in input." << endl;
        return;
    }
    if (!remainingSymbols.empty() && !lexicalAnalyser->hasNextToken()) {
        cout << "Error: Unexpected end of input." << endl;
        return;
    }
    cout << "Parsing completed successfully." << endl;
}

void InputProgramParser::printLeftMostDerivation() {
    vector<Symbol* > leftMostDerivation;
    while (remainingSymbols.top()!=Grammar::END) {
        leftMostDerivation.push_back(remainingSymbols.top());
        remainingSymbols.pop();
    }
    for (const auto symbol:matchedTokens) {
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

