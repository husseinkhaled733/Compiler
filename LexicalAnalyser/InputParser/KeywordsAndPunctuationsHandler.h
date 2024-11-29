//
// Created by Samni on 11/28/2024.
//
#pragma once

#include "RulesHandler.h"

class KeywordsAndPunctuationsHandler final : public RulesHandler
{
    public:
        void handleRule(const std::string& rule, RegexTreeBuilder& builder) override
        {

        }
        bool checkRule(const std::string& rule) override
        {
            return (rule.front() == '{' && rule.back() == '}') ||
                (rule.front() == '[' && rule.back() == ']');
        }
};
