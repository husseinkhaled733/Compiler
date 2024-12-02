//
// Created by Samni on 11/28/2024.
//
#pragma once
#include "RulesHandler.h"
#include "TreeParsingUtilities.h"
#include <regex>

class RegularExpressionHandler : public RulesHandler
{
public:
    TreeParsingUtilities treeParsingUtilities;
    Utilities utilities;
    void handleRule(std::string& rule, RegexTreeBuilder& builder) override
    {
        // Split the rule into LHS and RHS
        const std::vector<std::string> tokens = utilities.splitByDelimiter(rule, '=', 2);
        std::string LHS = tokens.at(0);
        const std::string& RHS = tokens.at(1);

        // Remove leading, trailing spaces and escapes from LHS
        utilities.trim(LHS);
        utilities.removeOccurrences(LHS, '\\');

        // Tokenize the RHS expression
        const std::vector<std::string> RHSTokens = treeParsingUtilities.tokenize(RHS, rule);

        // Store the tree of the new definition
        builder.regexExpressions[LHS] = treeParsingUtilities.parseTree(RHSTokens, builder.regexExpressions, builder.tokens);

        // print the postfix for debugging
        // treeParsingUtilities.printPostfix(builder.regexExpressions[LHS]);
    }
    bool checkRule(const std::string& rule) override
    {
        const std::regex expressionRgx(R"([\s]*[a-zA-z0-9]*[\s]*=[\s|a-zA-z0-9|\-|\+|\*|\(|\)|\||\=|\<|>|\!\.|\/]*)");
        return regex_match(rule, expressionRgx);
    }
};
