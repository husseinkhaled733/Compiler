cmake_minimum_required(VERSION 3.30)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler
        main.cpp
        LexicalAnalyser/LexicalAnalyser.cpp
        LexicalAnalyser/LexicalAnalyser.h
        LexicalAnalyser/SymbolTableHandler.cpp
        LexicalAnalyser/SymbolTableHandler.h
        LexicalAnalyser/Lexeme.cpp
        LexicalAnalyser/Lexeme.h
        LexicalAnalyser/State.cpp
        LexicalAnalyser/State.h
        LexicalAnalyser/DFA/DFA.h
        LexicalAnalyser/DFA/DFA.cpp
        LexicalAnalyser/InputParser/TreeParsingUtilities.cpp
        LexicalAnalyser/InputParser/TreeParsingUtilities.h
        LexicalAnalyser/InputParser/Utilities.cpp
        LexicalAnalyser/InputParser/Node.cpp
        LexicalAnalyser/InputParser/RulesHandler.h
        LexicalAnalyser/InputParser/RegexTreeBuilder.cpp
        LexicalAnalyser/InputParser/Constants.h
        LexicalAnalyser/Utils.cpp
)
