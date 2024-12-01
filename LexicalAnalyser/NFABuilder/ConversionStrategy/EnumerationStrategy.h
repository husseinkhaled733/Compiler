//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef ENUMERATIONSTRATEGY_H
#define ENUMERATIONSTRATEGY_H
#include "../../StateIdManager.h"
#include "ConversionStrategy.h"


class EnumerationStrategy final : public ConversionStrategy {
public:
    void convert(Node* node, State* startState, State* endState) override {
        // the - operator assumes that the left and right children are leaf nodes
        if (!node->left->isLeaf() || !node->right->isLeaf()) {
            throw std::invalid_argument("Enumeration strategy expects leaf nodes");
        }

        Node* left  = node->left;
        Node* right = node->right;

        State* currentState = startState;
        for (int enumeration = left->value; enumeration < right->value; ++enumeration) {
            State* nextState = new State(StateIdManager::getInstance().getNextId());
            currentState->addTransition(enumeration, nextState);
            currentState = nextState;
        }

        currentState->addTransition(right->value, endState);
    }
};


#endif // ENUMERATIONSTRATEGY_H
