

#include "Parser/Grammar.h"
#include "Parser/GrammarParser.h"
#include "Parser/ParsingTableGenerator.h"
#include "Parser/InputProgramParser/InputProgramParser.h"

int main() {
    string grammarPath = "C:/Users/mariam/Compiler/io/grammar.txt";
    string regexPath ="C:/Users/mariam/Compiler/io/regex.txt";
    string inputPath ="C:/Users/mariam/Compiler/io/input.txt";
    string outputParserPath ="C:/Users/mariam/Compiler/io/outputParser.txt";

    GrammarParser parser(grammarPath);
    Grammar* grammar = parser.parseGrammar();
    grammar->printGrammar();
    ParsingTableGenerator parsingTableGenerator(grammar);
    ParsingTable parsingTable = parsingTableGenerator.generateParsingTable();
    parsingTableGenerator.printFirstAndFollow();
    parsingTable.printParsingTable(grammar->getProductions());
    LexicalAnalyser lexicalAnalyser(regexPath,inputPath);
    InputProgramParser inputProgramParser(&lexicalAnalyser, grammar, &parsingTable);
    inputProgramParser.parseInputProgram(outputParserPath);

    return 0;
}
