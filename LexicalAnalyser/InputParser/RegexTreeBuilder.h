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
#include "Utilities.h"

class RegexTreeBuilder {
    public:
        explicit RegexTreeBuilder(const std::string& filePath);
        std::unordered_map<std::string, int> getTokenPriorities();
        std::unordered_map<std::string, Node*> getTokens();
        std::set<std::string> getKeywords();

    private:
        std::unordered_map<std::string, int> operationsPriorities;
        std::unordered_map<std::string, int> tokensPriorities;
        std::unordered_map<std::string, Node*> definitions;
        std::unordered_map<std::string, Node*> tokens;
        std::set<std::string> keywords;
        Utilities utilities;

};



#endif //REGEXTREEBUILDER_H
