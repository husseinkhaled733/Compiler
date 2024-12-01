//
// Created by Samni on 11/28/2024.
//

#ifndef REGEXTREEBUILDER_H
#define REGEXTREEBUILDER_H
#include <random>
#include <set>
#include <string>
#include <unordered_map>

#include "Node.h"
#include "TreeParsingUtilities.h"
#include "Utilities.h"

class RegexTreeBuilder {
    public:
        RegexTreeBuilder() = default;
        explicit RegexTreeBuilder(const std::string& filePath);
        std::unordered_map<std::string, int> operationsPriorities;
        std::unordered_map<std::string, int> tokensPriorities;
        std::unordered_map<std::string, Node*> regexExpressions;
        std::unordered_map<std::string, Node*> tokens;
        std::set<std::string> keywords;
        TreeParsingUtilities treeParsingUtilities;
        Utilities utilities;
        int priority = 1;

};



#endif //REGEXTREEBUILDER_H
