//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef LITERALSTRATEGY_H
#define LITERALSTRATEGY_H

#include "ConversionStrategy.h"

class LiteralStrategy final : public ConversionStrategy {
    void convert(Node* node, State* startState, State* endState) override {
        startState->addTransition(node->value, endState);
    }
};

#endif // LITERALSTRATEGY_H
