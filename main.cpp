
#include <bits/stdc++.h>

#include "Parser/Grammar.h"
#include "Parser/GrammarParser.h"
#include "Parser/ParsingTableGenerator.h"
#include "Parser/InputProgramParser/InputProgramParser.h"

#include "Parser/GrammarParser.h"
#include "Parser/InputProgramParser/InputProgramParser.h"
using namespace std;
int main() {
    string grammarPath = "/home/husseinkhaled/Compiler/io/grammar.txt";
    string regexPath ="/home/husseinkhaled/Compiler/io/regex.txt";
    string inputPath ="/home/husseinkhaled/Compiler/io/input.txt";
    string outputParserPath ="/home/husseinkhaled/Compiler/io/outputParser.txt";
    string debugParserPath ="/home/husseinkhaled/Compiler/io/debugParser.txt";

    GrammarParser parser(grammarPath);
    Grammar* grammar = parser.parseGrammar();
    grammar->printGrammar();
    ParsingTableGenerator parsingTableGenerator(grammar);
    ParsingTable parsingTable = parsingTableGenerator.generateParsingTable();
    parsingTableGenerator.printFirstAndFollow();
    parsingTable.printParsingTable(grammar->getProductions());
    LexicalAnalyser lexicalAnalyser(regexPath,inputPath);
    InputProgramParser inputProgramParser(&lexicalAnalyser, grammar, &parsingTable);
    inputProgramParser.parseInputProgram(outputParserPath, debugParserPath);
    return 0;
}
