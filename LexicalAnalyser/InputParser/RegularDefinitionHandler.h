//
// Created by Samni on 11/28/2024.
//
#pragma once
#include <queue>
#include "RulesHandler.h"
#include "TreeParsingUtilities.h"

class RegularDefinitionHandler  : public RulesHandler
{
public:
    TreeParsingUtilities treeParsingUtilities;
    void handleRule(std::string& rule, RegexTreeBuilder& builder) override
    {
        // Split the rule into LHS and RHS
        const std::vector<std::string> tokens = Utilities::splitByDelimiter(rule, ':', 2);
        std::string LHS = tokens.at(0);
        const std::string& RHS = tokens.at(1);

        // Remove leading, trailing spaces and escapes from LHS
        Utilities::trim(LHS);
        Utilities::removeOccurrences(LHS, '\\');

        // Tokenize the RHS expression
        const std::vector<std::string> RHSTokens = treeParsingUtilities.tokenize(RHS, rule);

        // Add the new token and its priority
        builder.tokens[LHS] = treeParsingUtilities.parseTree(RHSTokens, builder.regexExpressions, builder.tokens);
        builder.tokensPriorities[LHS] = builder.priority++;
        // print the postfix for debugging
        // treeParsingUtilities.printPostfix(builder.regexExpressions[LHS]);
    }

    bool checkRule(const std::string& rule) override
    {
        // LHS should contain one word that consists of letters, numbers or underscores, but should start with a letter or underscore
        const std::regex definitionRgx(R"([\s]*[a-zA-z_]+[\w]*[\s]*:[\s|a-zA-z0-9|\-|\+|\*|\(|\)|\||\=|\<|>|\!\.|\/]*)");
        return regex_match(rule, definitionRgx);
    }
};
