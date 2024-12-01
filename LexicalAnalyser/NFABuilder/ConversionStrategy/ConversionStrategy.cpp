//
// Created by mohamed_anwar on 12/1/24.
//

#include "ConversionStrategy.h"

#include "ConversionStrategyFactory.h"

void ConversionStrategy::convertChildren(Node* node,
                                         State* leftStartState, State* leftEndState,
                                         State* rightStartState, State* rightEndState) {
    ConversionStrategyFactory& factory = ConversionStrategyFactory::getInstance();

    ConversionStrategy* leftStrategy = factory.getStrategy(node->left->value, node->left->isLeaf());
    leftStrategy->convert(node->left, leftStartState, leftEndState);

    ConversionStrategy* rightStrategy = factory.getStrategy(node->right->value, node->right->isLeaf());
    rightStrategy->convert(node->right, rightStartState, rightEndState);
}

void ConversionStrategy::convertChild(Node* node, State* startState, State* endState) {
    ConversionStrategyFactory& factory = ConversionStrategyFactory::getInstance();

    ConversionStrategy* strategy = factory.getStrategy(node->left->value, node->left->isLeaf());
    strategy->convert(node->left, startState, endState);
}