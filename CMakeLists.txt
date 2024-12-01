cmake_minimum_required(VERSION 3.30)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp
        LexicalAnalyser/InputParser/TreeParsingUtilities.cpp
        LexicalAnalyser/InputParser/TreeParsingUtilities.h
        LexicalAnalyser/InputParser/Utilities.cpp
        LexicalAnalyser/InputParser/Node.cpp
        LexicalAnalyser/InputParser/RulesHandler.h
        LexicalAnalyser/InputParser/RegexTreeBuilder.cpp
        LexicalAnalyser/InputParser/Constants.h
        )
