//
// Created by Samni on 11/28/2024.
//

#include <fstream>
#include <iostream>

#include "KeywordsAndPunctuationsHandler.h"
#include "RegularDefinitionHandler.h"
#include "RegularExpressionHandler.h"
#include "RegexTreeBuilder.h"

RegexTreeBuilder::RegexTreeBuilder(const std::string& filePath)
{

    std::ifstream file(filePath);
    if (!file.is_open()){
        throw std::ios_base::failure("File not found: " + filePath);
    }

    RegularDefinitionHandler regularDefinitionHandler;
    RegularExpressionHandler regularExpressionHandler;
    KeywordsAndPunctuationsHandler keywordsAndPunctuationsHandler;
    std::string rule;
    while(std::getline(file, rule))
    {
        utilities.trim(rule);

        if (regularDefinitionHandler.checkRule(rule))
        {
            regularDefinitionHandler.handleRule(rule, *this);
        }
        else if (regularExpressionHandler.checkRule(rule))
        {
            regularExpressionHandler.handleRule(rule, *this);
        }
        else if (keywordsAndPunctuationsHandler.checkRule(rule))
        {
            keywordsAndPunctuationsHandler.handleRule(rule, *this);
        }
        else
          throw std::invalid_argument(rule + " rule is invalid");
    }
    // Add delimiter token
    const auto delimiterRoot = new Node(RegexOperations::KLEENE_STAR);
    delimiterRoot->left = treeParsingUtilities.processString(" \t\n\r", RegexOperations::ALTERNATION);
    tokens[DELIMITER] = delimiterRoot;
}
