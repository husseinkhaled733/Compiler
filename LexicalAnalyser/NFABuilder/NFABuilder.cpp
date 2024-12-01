//
// Created by mohamed_anwar on 12/1/24.
//

#include "NFABuilder.h"

#include "../StateIdManager.h"
#include "../Utils.h"

NFABuilder::NFABuilder(const std::unordered_map<std::string, Node*>& tokens) : tokens(tokens) {}

State* NFABuilder::buildNFA() {
    State* combinedNFA = new State(StateIdManager::getInstance().getNextId());
    for (const auto& [token , regexTreeRoot] : this->tokens) {
        State* tokenNFA = buildTokenNFA(token, regexTreeRoot);
        combinedNFA->addTransition(epsilon, tokenNFA);
    }
    return combinedNFA;
}

State* NFABuilder::buildTokenNFA(std::string token, Node* root) {
    if (!root) {
        throw std::invalid_argument("Node is null");
    }

    State* startState = new State(StateIdManager::getInstance().getNextId());
    State* endState   = new State(token, StateIdManager::getInstance().getNextId());
    endState->isFinal = true;

    ConversionStrategyFactory::getInstance()
        .getStrategy(root->value, root->isLeaf())
        ->convert(root, startState, endState);

    return startState;
}
