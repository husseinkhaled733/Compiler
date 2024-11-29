//
// Created by Samni on 11/28/2024.
//

#include <fstream>
#include <iostream>

#include "KeywordsAndPunctuationsHandler.h"
#include "RegularDefinitionHandler.h"
#include "RegularExpressionHandler.h"
#include "RegexTreeBuilder.h"
#include "RulesHandler.h"

RegexTreeBuilder::RegexTreeBuilder(const std::string& filePath)
{

    std::ifstream file(filePath);
    if (!file.is_open()){
        throw std::ios_base::failure("File not found: " + filePath);
    }

    RegularDefinitionHandler regularDefinitionHandler;
    RegularExpressionHandler regularExpressionHandler;
    KeywordsAndPunctuationsHandler keywordsAndPunctuationsHandler;

    keywordsAndPunctuationsHandler.setNext(&regularDefinitionHandler);
    regularDefinitionHandler.setNext(&regularExpressionHandler);

    std::string rule;
    while(std::getline(file, rule))
    {
        Utilities::strip(rule);
        keywordsAndPunctuationsHandler.handleRequest(rule, *this);
    }
}

std::unordered_map<std::string, int> RegexTreeBuilder::getTokenPriorities()
{
    return this->tokensPriorities;
}

std::set<std::string> RegexTreeBuilder::getKeywords()
{
    return this->keywords;
}

std::unordered_map<std::string, Node*> RegexTreeBuilder::getTokens()
{
    return this->tokens;
}

