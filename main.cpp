#include "LexicalAnalyser/LexicalAnalyser.h"
#include <iostream>

#include "LexicalAnalyser/Utils.h"
#include "LexicalAnalyser/DFA.h"

int main() {

    // SymbolTableHandler symbolTableHandler;
    // LexicalAnalyser lexicalAnalyser(symbolTableHandler);
    // lexicalAnalyser.tokenizeInputFile(
    //     "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/input.txt",
    //     "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/output.txt"
    // );
    State* A = new State("A");
    State* B = new State("B");
    State* C = new State("C");
    A->transitions['a'].push_back(B);
    A->transitions[epsilon].push_back(C);
    std::set<State*> set1 = {A, B, C};
    std::set<State*> set2 = {C, B, A};
    std::set<State* > set3 = {A};
    if (set1 == set2) {
        std::cout << "The sets are equal!" << std::endl;
    }
    DFA dfa;
    std::set<State* > closure = dfa.epsilonClosure(set3);
    for (State* state : closure) {
        std::cout << state->token << std::endl;
    }
    State* startState = new State("S");
    State* a = new State("A");
    State* g = new State("G");
    State* f = new State("F");
    startState->transitions['1'].push_back(a);
    startState->transitions[epsilon].push_back(f);
    startState->transitions['0'].push_back(g);
    a->transitions['0'].push_back(f);
    a->transitions['1'].push_back(f);
    a->transitions['1'].push_back(a);
    a->transitions[epsilon].push_back(startState);
    State* dfaStartState = dfa.convertNFAtoDFA(startState);

    return 0;
}
