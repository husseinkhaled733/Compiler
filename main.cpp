#include "LexicalAnalyser/DFA/DFA.h"
#include "LexicalAnalyser/InputParser/RegexTreeBuilder.h"
#include "LexicalAnalyser/LexicalAnalyser.h"
#include "LexicalAnalyser/NFABuilder/NFABuilder.h"
#include "LexicalAnalyser/DotExporter.h"
#include "LexicalAnalyser/Utils.h"
#include <iostream>

int main() {
    RegexTreeBuilder regexTreeBuilder("/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io"
                                      "/regex.txt");
    cout << endl;

    priorities = regexTreeBuilder.tokensPriorities;

    NFABuilder nfaBuilder(regexTreeBuilder.tokens);
    State* nfa = nfaBuilder.buildNFA();

    // DotExporter::exportToDot(nfa, "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
    // "nfa.dot");
    // traverse(nfa);

    DFA dfa;
    State* startState = dfa.convertNFAtoDFA(nfa);
    State* minimizedDFA = dfa.minimizeDFA(startState);
    dfa.printMinimizedDFA();

    // DotExporter::exportToDot(minimizedDFA, "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
    // "dfa.dot");

    SymbolTableHandler symbol_table_handler;
    LexicalAnalyser lexical_analyser(symbol_table_handler, minimizedDFA);

    lexical_analyser.tokenizeInputFile("/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
                                       "input.txt","/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/"
                                       "Compiler/io/output.txt");

    return 0;
}
