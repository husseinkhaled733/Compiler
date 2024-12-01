//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef ALTERNATIONSTRATEGY_H
#define ALTERNATIONSTRATEGY_H

#include "../../StateIdManager.h"
#include "../../Utils.h"
#include "ConversionStrategy.h"

class AlternationStrategy final : public ConversionStrategy {
public:
    void convert(Node* node, State* startState, State* endState) override {
        State* upperLeftState = new State(StateIdManager::getInstance().getNextId());
        State* upperRightState = new State(StateIdManager::getInstance().getNextId());

        State* lowerLeftState = new State(StateIdManager::getInstance().getNextId());
        State* lowerRightState = new State(StateIdManager::getInstance().getNextId());

        startState->addTransition(epsilon, upperLeftState);
        startState->addTransition(epsilon, lowerLeftState);

        upperRightState->addTransition(epsilon, endState);
        lowerRightState->addTransition(epsilon, endState);

        convertChildren(node, upperLeftState, upperRightState, lowerLeftState, lowerRightState);
    }
};

#endif //ALTERNATIONSTRATEGY_H
