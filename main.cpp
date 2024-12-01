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
    NFABuilder nfaBuilder(regexTreeBuilder.tokens);
    State* nfa = nfaBuilder.buildNFA();

    DotExporter::exportToDot(nfa, "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/"
                                  "nfa.dot");
    // traverse(nfa);

    return 0;
}
