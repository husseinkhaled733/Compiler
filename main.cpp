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
    // state0->token = "0";
    State* state1 = new State();
    // state1->token = "1";
    State* state2 = new State();
    // state2->token = "2";
    State* state3 = new State();
    // state3->token = "3";
    State* state4 = new State();
    // state4->token = "4";
    State* state5 = new State();
    // state5->token = "5";
    State* state6 = new State();
    // state6->token = "6";
    State* state7 = new State();
    // state7->token = "7";
    State* state8 = new State();
    // state8->token = "8";
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
    // cout << "DFA: " << endl;
    // for (auto& state: dfa.normalStates) {
    //     cout << "State: " << state->token << endl;
    //     for (auto& [input, next] : state->transitions) {
    //         cout << "Input: " << input << " Next: " << next[0]->token << endl;
    //     }
    // }
    // for (auto& state: dfa.finalStates) {
    //     cout << "Final State: " << state->token << endl;
    //     for (auto& [input, next] : state->transitions) {
    //         cout << "Input: " << input << " Next: " << next[0]->token << endl;
    //     }
    // }
    State* minimized=dfa.minimizeDFA(dfaStartState);
    // cout << "Minimized DFA: " << endl;
    // cout << "State: " << minimized->token << endl;
    // for (auto& [input, next] : minimized->transitions) {
    //     cout << "Input: " << input << " Next: " << next[0]->token << endl;
    // }
    // cout << "DFA: " << endl;
    // for (auto& state: dfa.normalStates) {
    //     cout << "State: " << state->token << endl;
    //     for (auto& [input, next] : state->transitions) {
    //         cout << "Input: " << input << " Next: " << next[0]->token << endl;
    //     }
    // }
    // for (auto& state: dfa.finalStates) {
    //     cout << "Final State: " << state->token << endl;
    //     for (auto& [input, next] : state->transitions) {
    //         cout << "Input: " << input << " Next: " << next[0]->token << endl;
    //     }
    // }
    // unordered_set<State *> s1;
    // unordered_set<State *> s2;
    // s1.insert(state0);
    // s1.insert(state1);
    // s1.insert(state2);
    // s2.insert(state2);
    // s2.insert(state1);
    // s2.insert(state0);
    // if (s1==s2) {
    //     cout << "Equal" << endl;
    // }
    // else {
    //     cout << "Not Equal" << endl;
    // }
    //
    // State* A= new State();
    // A->token="A";
    // State* B= new State();
    // B->token="B";
    // State* C= new State();
    // C->token="C";
    // State* D= new State();
    // D->token="D";
    // State* E= new State();
    // E->token="E";
    // A->addTransition('0', B);
    // A->addTransition('1', C);
    // B->addTransition('1', D);
    // B->addTransition('0',B);
    // C->addTransition('0', B);
    // C->addTransition('1', C);
    // D->addTransition('1', E);
    // D->addTransition('0', B);
    // E->addTransition('0', B);
    // E->addTransition('1', C);
    // E->isFinal = true;
    // DFA dfa2;
    // dfa2.possibleInputs.insert('0');
    // dfa2.possibleInputs.insert('1');
    // dfa2.finalStates.insert(E);
    // dfa2.normalStates.insert(A);
    // dfa2.normalStates.insert(B);
    // dfa2.normalStates.insert(C);
    // dfa2.normalStates.insert(D);
    // dfa2.minimizeDFA(A);
    dfa.printDFA();
    dfa.printMinimizedDFA();
    return 0;
}
