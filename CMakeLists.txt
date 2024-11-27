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
)