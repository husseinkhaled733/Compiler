//
// Created by Samni on 11/28/2024.
//
#pragma once
#include "RulesHandler.h"

class RegularDefinitionHandler final : public RulesHandler
{
public:
    void handleRule(const std::string& rule, RegexTreeBuilder& builder) override
    {

    }
    bool checkRule(const std::string& rule) override
    {
        const size_t pos = rule.find('=');

        // check if = exists and isn't escaped
        return pos != std::string::npos && rule.at(pos - 1) != '\\';
    }
};