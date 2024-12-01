//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef NFABUILDER_H
#define NFABUILDER_H

#include "../../LexicalAnalyser/State.h"
#include "../InputParser/Node.h"
#include "ConversionStrategy/ConversionStrategyFactory.h"
#include <bits/stdc++.h>

class NFABuilder {
    std::unordered_map<std::string, Node*> tokens;
    State* buildTokenNFA(std::string token, Node* root);
public:
    explicit NFABuilder(const std::unordered_map<std::string, Node*>& tokens);
    State* buildNFA();
};


#endif // NFABUILDER_H
