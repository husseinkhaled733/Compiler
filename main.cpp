#include "LexicalAnalyser/DFA/DFABuilder.h"
#include "LexicalAnalyser/InputParser/RegexTreeBuilder.h"
#include "LexicalAnalyser/LexicalAnalyser.h"
#include "LexicalAnalyser/NFABuilder/NFABuilder.h"
#include "LexicalAnalyser/DotExporter.h"
#include "LexicalAnalyser/Utils.h"
#include <iostream>

#include "Parser/Grammar.h"
#include "Parser/ParsingTable.h"
#include "Parser/InputProgramParser/InputProgramParser.h"

int main() {
    // RegexTreeBuilder regexTreeBuilder("/home/husseinkhaled/Compiler/io"
    //                                   "/regex.txt");
    // cout << endl;
    //
    // priorities = regexTreeBuilder.tokensPriorities;
    //
    // NFABuilder nfaBuilder(regexTreeBuilder.tokens);
    // State* nfa = nfaBuilder.buildNFA();
    //
    // // DotExporter::exportToDot(nfa, "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
    // // "nfa.dot");
    // // traverse(nfa);
    //
    // DFABuilder dfa;
    // State* startState = dfa.convertNFAtoDFA(nfa);
    // State* minimizedDFA = dfa.minimizeDFA(startState);
    // dfa.printMinimizedDFA();
    // // dfa.printDFA();
    //
    // // DotExporter::exportToDot(minimizedDFA, "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
    // // "dfa.dot");
    //
    // SymbolTableHandler symbol_table_handler;
    // LexicalAnalyser lexical_analyser(symbol_table_handler, minimizedDFA);
    //
    // lexical_analyser.tokenizeInputFile("/home/husseinkhaled/Compiler/io/"
    //                                    "input.txt","/home/husseinkhaled/"
    //                                    "Compiler/io/output.txt");

    // LexicalAnalyser lexical_analyser;
    // while (lexical_analyser.hasNextToken()) {
    //     Lexeme l = lexical_analyser.nextToken();
    //     cout<<l.getTokenType()<<" "<<l.getValue()<<endl;
    // }
    // NonTerminal* S = new NonTerminal("S");
    // NonTerminal* A = new NonTerminal("A");
    // Terminal* a = new Terminal("a");
    // Terminal* e = new Terminal("e");
    // Terminal* d = new Terminal("d");
    // Terminal* c = new Terminal("c");
    // Terminal* b = new Terminal("b");
    // Grammar* grammar = new Grammar();
    // grammar->startSymbol = S;
    // unordered_map<string, vector<vector<Symbol*>>> productions;
    // vector<vector<Symbol*>> S_productions;
    // vector<Symbol*> S1={A,b,S};
    // S_productions.push_back(S1);
    // vector<Symbol*> S2={e};
    // S_productions.push_back(S2);
    // vector<Symbol*> S3;
    // S3.emplace_back((Symbol*) Grammar::EPSILON);
    // S_productions.push_back(S3);
    // productions["S"]=S_productions;
    // vector<vector<Symbol*>> A_productions;
    // vector<Symbol*> A1={a};
    // A_productions.push_back(A1);
    // vector<Symbol*> A2={c, A, d};
    // A_productions.push_back(A2);
    // productions["A"]=A_productions;
    // grammar->productions=productions;
    // ParsingTable* parsingTable = new ParsingTable();
    // parsingTable->table["S"]["a"]=0;
    // parsingTable->table["S"]["c"]=0;
    // parsingTable->table["S"]["e"]=1;
    // parsingTable->table["S"][Grammar::END->getName()]=2;
    // parsingTable->table["A"]["a"]=0;
    // parsingTable->table["A"]["c"]=1;
    // parsingTable->table["A"]["b"]=parsingTable->SYNC;
    // parsingTable->table["A"]["d"]=parsingTable->SYNC;
    // InputProgramParser inputProgramParser(&lexical_analyser, grammar, parsingTable);
    // inputProgramParser.parseInputProgram("/home/husseinkhaled/Compiler/io/parserOutput.txt");



    return 0;
}
