//
// Created by Samni on 11/28/2024.
//
#pragma once

#include "RulesHandler.h"
#include "TreeParsingUtilities.h"
#include <regex>

#include "Constants.h"

class KeywordsAndPunctuationsHandler final : public RulesHandler
{
    TreeParsingUtilities treeParsingUtilities;
    Utilities utilities;
    public:
        void handleRule(std::string& rule, RegexTreeBuilder& builder) override
        {
            utilities.removeFirstAndLastCharacters(rule);
            const std::regex regex(R"(\\(?!\\))");
            rule = std::regex_replace(rule, regex, "");
            for (std::vector<std::string> tokens = utilities.splitBySpaces(rule); auto token : tokens)
            {
                builder.tokens[token] = treeParsingUtilities.processString(token, RegexOperations::CONCATENATION);
                builder.tokensPriorities[token] = 0;
            }
        }
        bool checkRule(const std::string& rule) override
        {
            // special characters escaped or any other character
            const std::regex punctuationRgx(R"(\[[\s]*(\\[\(\)\{\}:=]|[^\\(\)\{\}:=\w]|[\s])*\])");
            // keywords should be formed of letters or underscores
            const std::regex keywordsRgx(R"(\{[a-zA-Z_\s]*\})");
            return regex_match(rule, punctuationRgx) || regex_match(rule, keywordsRgx);
        }
};
