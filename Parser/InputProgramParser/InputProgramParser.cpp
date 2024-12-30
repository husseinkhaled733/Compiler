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


void InputProgramParser::parse() {
    if (!lexicalAnalyser->hasNextToken()) {
        cout << "Error: Empty input." << endl;
        return;
    }
    currentLexeme = lexicalAnalyser->nextToken();
    string currentTokenName=currentLexeme.getTokenType();
    bool isInputEnd=false;
    while (!remainingSymbols.empty()) {
        printLeftMostDerivation();
        Symbol* currentSymbol = remainingSymbols.top();
        remainingSymbols.pop();
        if (currentSymbol==Grammar::EPSILON) {
            continue;
        }
        cout<<"Current Symbol: ";
        if (currentSymbol==Grammar::END) {
            cout<<"$"<<endl;
        }
        else {
            cout<<currentSymbol->getName()<<endl;
        }
        cout<<"Current token: ";
        if (currentTokenName==Grammar::END->getName()) {
            cout<<"$"<<endl;
        }
        else {
            cout<<currentTokenName<<endl;
        }
        // If the current symbol is a terminal
        if (currentSymbol->isTerminal()) {
            if (currentSymbol->getName() == currentTokenName) {
                cout << "Matched terminal: " << currentSymbol->getName() << endl;
                if (!lexicalAnalyser->hasNextToken()) {
                    if (!isInputEnd) {
                        currentTokenName=Grammar::END->getName();
                        isInputEnd=true;
                    }
                    else {
                        break;
                    }
                }
                else {
                    currentLexeme = lexicalAnalyser->nextToken();
                    currentTokenName=currentLexeme.getTokenType();
                }
            } else {
                cout << "Error: Expected terminal " << currentSymbol->getName() << " but found " << currentTokenName << endl;
                cout << "Inserting missing terminal " << currentSymbol->getName() << endl;
            }
        }
        else {
            string nonTerminalName = currentSymbol->getName();
            bool found = true;
            if (!parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                cout << "Error: Unexpected token " << currentTokenName << endl;
                found = false;
                while (lexicalAnalyser->hasNextToken()) {
                    currentLexeme = lexicalAnalyser->nextToken();
                    currentTokenName=currentLexeme.getTokenType();
                    if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                        found = true;
                        break;
                    }
                    cout << "Error: Unexpected token " << currentTokenName << endl;
                }
                if (!isInputEnd && !found) {
                    currentTokenName=Grammar::END->getName();
                    isInputEnd=true;
                    if (parsingTable->table[nonTerminalName].contains(currentTokenName)) {
                        found = true;
                    }
                    cout << "Error: Unexpected token " << currentTokenName << endl;
                }
            }
            if (!found) {
                continue;
            }
            const int index = parsingTable->table[nonTerminalName][currentTokenName];
            cout<<index<<endl;
            // sync
            if (index==parsingTable->SYNC) {
                cout << "Error: Unexpected token " << currentLexeme.getTokenType() << endl;
                continue;
            }
            cout<<nonTerminalName<<" "<<index<<endl;
            cout<<currentTokenName<<endl;
            cout<<grammar->getProductions()[nonTerminalName].size()<<endl;
            vector<Symbol* > production = grammar->getProductions()[nonTerminalName][index];
            cout<<"Production: ";
            for (int i = production.size() - 1; i >= 0; i--) {
                cout<<production[i]->getName()<<" ";
                if (production[i]==Grammar::EPSILON) {
                    break;
                }
                remainingSymbols.push(production[i]);
            }
            cout<<endl;
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
    if (leftMostDerivation.empty()) {
        return;
    }
    for (const auto symbol:leftMostDerivation) {
        output<<symbol->getName()<<" ";
    }
    output<<endl;
    for (int i = leftMostDerivation.size() - 1; i >= 0; i--) {
        remainingSymbols.push(leftMostDerivation[i]);
    }
}

