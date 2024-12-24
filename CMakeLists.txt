cmake_minimum_required(VERSION 3.30)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp
        LexicalAnalyser/InputParser/Node.cpp
        LexicalAnalyser/InputParser/RegexTreeBuilder.cpp
        LexicalAnalyser/InputParser/Utilities.cpp
        LexicalAnalyser/NFABuilder/ConversionStrategy/ConversionStrategy.cpp
        LexicalAnalyser/NFABuilder/ConversionStrategy/ConversionStrategyFactory.cpp
        LexicalAnalyser/NFABuilder/NFABuilder.cpp
        LexicalAnalyser/State.cpp
        LexicalAnalyser/StateIdManager.cpp
        LexicalAnalyser/InputParser/Constants.h
        LexicalAnalyser/InputParser/KeywordsAndPunctuationsHandler.h
        LexicalAnalyser/InputParser/Node.h
        LexicalAnalyser/InputParser/RegexTreeBuilder.h
        LexicalAnalyser/InputParser/RegularDefinitionHandler.h
        LexicalAnalyser/InputParser/RegularExpressionHandler.h
        LexicalAnalyser/InputParser/RulesHandler.h
        LexicalAnalyser/InputParser/Utilities.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/AlternationStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/ConcatenationStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/ConversionStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/ConversionStrategyFactory.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/EnumerationStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/KleenePlusStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/KleeneStarStrategy.h
        LexicalAnalyser/NFABuilder/ConversionStrategy/LiteralStrategy.h
        LexicalAnalyser/NFABuilder/NFABuilder.h
        LexicalAnalyser/State.h
        LexicalAnalyser/StateIdManager.h
        LexicalAnalyser/Utils.h
        LexicalAnalyser/Utils.cpp
        LexicalAnalyser/DFA/DFA.h
        LexicalAnalyser/DFA/DFA.cpp
        LexicalAnalyser/Lexeme.cpp
        LexicalAnalyser/Lexeme.h
        LexicalAnalyser/LexicalAnalyser.cpp
        LexicalAnalyser/LexicalAnalyser.h
        LexicalAnalyser/SymbolTableHandler.cpp
        LexicalAnalyser/SymbolTableHandler.h
        LexicalAnalyser/InputParser/TreeParsingUtilities.cpp
        LexicalAnalyser/InputParser/TreeParsingUtilities.h
        LexicalAnalyser/DotExporter.h
        Parser/ParsingTableGenerator.cpp
        Parser/ParsingTableGenerator.h
)
