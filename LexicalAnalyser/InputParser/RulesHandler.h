//
// Created by Samni on 11/28/2024.
//

#ifndef RULESHANDLER_H
#define RULESHANDLER_H
#include <string>

#include "RegexTreeBuilder.h"


class RulesHandler {
public:
    RulesHandler() = default;
    virtual ~RulesHandler();
    void handleRequest(const std::string& rule, RegexTreeBuilder& builder);;
    virtual bool checkRule(const std::string& rule);
    virtual void handleRule(const std::string& rule, RegexTreeBuilder& builder);

    void setNext(RulesHandler* nextHandler) {
        next = nextHandler;
    }

protected:
    RulesHandler* next = nullptr;
};



#endif //RULESHANDLER_H
