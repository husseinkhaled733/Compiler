//
// Created by Samni on 11/28/2024.
//

#include "RulesHandler.h"

#include <stdexcept>

void RulesHandler::handleRequest(const std::string& rule, RegexTreeBuilder& builder)
{
    if (checkRule(rule)) handleRule(rule, builder);
    else if (next!=nullptr) next-> handleRequest(rule, builder);
    else throw std::invalid_argument(rule + " rule is invalid");
}
