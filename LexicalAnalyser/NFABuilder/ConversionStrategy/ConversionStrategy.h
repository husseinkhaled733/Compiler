//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef CONVERSIONSTRATEGY_H
#define CONVERSIONSTRATEGY_H

#include "../../InputParser/Node.h"
#include "../../State.h"


class ConversionStrategy {
protected:
    void convertChildren(Node* node,
                         State* leftStartState, State* leftEndState,
                         State* rightStartState, State* rightEndState);

    void convertChild(Node* node, State* startState, State* endState);
public:
    virtual ~ConversionStrategy()                                              = default;
    virtual void convert(Node* node, State* startState, State* endState) = 0;
};


#endif // CONVERSIONSTRATEGY_H
