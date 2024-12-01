//
// Created by Samni on 11/28/2024.
//
#pragma once

#include "RulesHandler.h"
#include "TreeParsingUtilities.h"
#include <regex>

class KeywordsAndPunctuationsHandler final : public RulesHandler
{
    TreeParsingUtilities treeParsingUtilities;
    Utilities utilities;
    public:
        void handleRule(std::string& rule, RegexTreeBuilder& builder) override
        {
            utilities.removeFirstAndLastCharacters(rule);
            for (std::vector<std::string> tokens = utilities.splitBySpaces(rule); auto token : tokens)
            {
                std::string LHS = token;
                utilities.removeOccurrences(LHS, '\\');
                builder.tokens[LHS] = treeParsingUtilities.processString(token);
                builder.tokensPriorities[token] = 0;
            }
        }
        bool checkRule(const std::string& rule) override
        {
            const std::regex punctuationRgx(R"(\[[\s]*([\W]*[\s]*)*\])");
            const std::regex keywordsRgx(R"(\{[\s]*([a-z]*[\s]*)*\})");
            return regex_match(rule, punctuationRgx) || regex_match(rule, keywordsRgx);
        }
};
