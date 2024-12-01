//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef KLEENEPLUSSTRATEGY_H
#define KLEENEPLUSSTRATEGY_H

#include "ConversionStrategy.h"

class KleenePlusStrategy final : public ConversionStrategy {
public:
    void convert(Node* node, State* startState, State* endState) override {
        State* leftState = new State(StateIdManager::getInstance().getNextId());
        State* middleState = new State(StateIdManager::getInstance().getNextId());
        State* rightState = new State(StateIdManager::getInstance().getNextId());

        leftState->addTransition(epsilon, middleState);
        leftState->addTransition(epsilon, endState);

        rightState->addTransition(epsilon, middleState);
        rightState->addTransition(epsilon, endState);

        convertChild(node, middleState, rightState);
        convertChild(node, startState, leftState);
    }
};

#endif //KLEENEPLUSSTRATEGY_H
