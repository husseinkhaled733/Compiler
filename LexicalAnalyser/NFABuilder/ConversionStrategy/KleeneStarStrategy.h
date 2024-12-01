//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef KLEENESTARSTRATEGY_H
#define KLEENESTARSTRATEGY_H

#include "../../Utils.h"
#include "ConversionStrategy.h"

class KleeneStarStrategy final : public ConversionStrategy {
public:
    void convert(Node* node, State* startState, State* endState) override {
        State* leftState = new State(StateIdManager::getInstance().getNextId());
        State* rightState = new State(StateIdManager::getInstance().getNextId());

        startState->addTransition(epsilon, leftState);
        startState->addTransition(epsilon, endState);

        rightState->addTransition(epsilon, leftState);
        rightState->addTransition(epsilon, endState);

        convertChild(node, leftState, rightState);
    }
};

#endif //KLEENESTARSTRATEGY_H
