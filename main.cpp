#include "LexicalAnalyser/LexicalAnalyser.h"
#include <iostream>

int main() {

    SymbolTableHandler symbolTableHandler;
    LexicalAnalyser lexicalAnalyser(symbolTableHandler);
    lexicalAnalyser.tokenizeInputFile(
        "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/input.txt",
        "/media/mohamed_anwar/HDD/CSED/9th Semester/Compilers/Project/Compiler/io/output.txt"
    );

    return 0;
}
