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
    State* state0 = new State();
    state0->token = "0";
    State* state1 = new State();
    state1->token = "1";
    State* state2 = new State();
    state2->token = "2";
    State* state3 = new State();
    state3->token = "3";
    State* state4 = new State();
    state4->token = "4";
    State* state5 = new State();
    state5->token = "5";
    State* state6 = new State();
    state6->token = "6";
    State* state7 = new State();
    state7->token = "7";
    State* state8 = new State();
    state8->token = "8";
    state0->addTransition(epsilon, state1);
    state0->addTransition(epsilon, state7);
    state0->addTransition(epsilon, state3);
    state1->addTransition('a', state2);
    state3->addTransition('a', state4);
    state4->addTransition('b', state5);
    state5->addTransition('b', state6);
    state7->addTransition('a', state7);
    state7->addTransition('b', state8);
    state8->addTransition('b', state8);
    state2->isFinal = true;
    state2->token = "a";
    state6->isFinal = true;
    state6->token= "abb";
    state8->isFinal = true;
    state8->token = "a*b+";
    priorities["a"] = 1;
    priorities["abb"] = 2;
    priorities["a*b+"] = 3;
    DFA dfa;
    State* dfaStartState = dfa.convertNFAtoDFA(state0);
    return 0;
}
