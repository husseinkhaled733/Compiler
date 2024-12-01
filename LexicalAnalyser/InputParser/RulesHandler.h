//
// Created by Samni on 11/28/2024.
//

#ifndef RULESHANDLER_H
#define RULESHANDLER_H
#include <string>

#include "RegexTreeBuilder.h"


class RulesHandler {
public:
    virtual ~RulesHandler() = default;
    RulesHandler() = default;
    virtual bool checkRule(const std::string& rule) = 0;
    virtual void handleRule(std::string& rule, RegexTreeBuilder& builder)  = 0;
};




#endif //RULESHANDLER_H
