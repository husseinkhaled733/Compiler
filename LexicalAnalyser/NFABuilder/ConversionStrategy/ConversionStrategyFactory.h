//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef CONVERSIONSTRATEGYFACTORY_H
#define CONVERSIONSTRATEGYFACTORY_H

#include "ConversionStrategy.h"
#include <bits/stdc++.h>

class ConversionStrategyFactory {

    std::unordered_map<char, std::unique_ptr<ConversionStrategy>> strategies;

    ConversionStrategyFactory();

public:
    static ConversionStrategyFactory& getInstance();
    ConversionStrategy* getStrategy(char operation, bool isLeaf);

    ConversionStrategyFactory(const ConversionStrategyFactory&) = delete;
    ConversionStrategyFactory& operator=(const ConversionStrategyFactory&) = delete;
};



#endif //CONVERSIONSTRATEGYFACTORY_H
