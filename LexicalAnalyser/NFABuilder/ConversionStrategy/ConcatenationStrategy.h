//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef CONCATENATIONSTRATEGY_H
#define CONCATENATIONSTRATEGY_H

#include "ConversionStrategy.h"


class ConcatenationStrategy final : public ConversionStrategy {
public:
    void convert(Node* node, State* startState, State* endState) override {
        State* middleState = new State(StateIdManager::getInstance().getNextId());
        convertChildren(node, startState, middleState, middleState, endState);
    }
};

#endif //CONCATENATIONSTRATEGY_H
