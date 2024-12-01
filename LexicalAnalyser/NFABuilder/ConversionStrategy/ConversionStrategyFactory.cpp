//
// Created by mohamed_anwar on 12/1/24.
//

#include "ConversionStrategyFactory.h"

#include "../../InputParser/Constants.h"
#include "AlternationStrategy.h"
#include "ConcatenationStrategy.h"
#include "EnumerationStrategy.h"
#include "KleenePlusStrategy.h"
#include "KleeneStarStrategy.h"
#include "LiteralStrategy.h"

ConversionStrategyFactory& ConversionStrategyFactory::getInstance() {
        static ConversionStrategyFactory instance;
        return instance;
    }

ConversionStrategyFactory::ConversionStrategyFactory() {
    strategies[RegexOperations::ENUMERATION] = std::make_unique<EnumerationStrategy>();
    strategies[RegexOperations::CONCATENATION] = std::make_unique<ConcatenationStrategy>();
    strategies[RegexOperations::KLEENE_STAR] = std::make_unique<KleeneStarStrategy>();
    strategies[RegexOperations::KLEENE_PLUS] = std::make_unique<KleenePlusStrategy>();
    strategies[RegexOperations::ALTERNATION] = std::make_unique<AlternationStrategy>();
}

ConversionStrategy* ConversionStrategyFactory::getStrategy
    (char operation, bool isLeaf) {

    if (isLeaf) {
        return new LiteralStrategy();
    }

    return strategies.at(operation).get();
}