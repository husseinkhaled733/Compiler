//
// Created by Samni on 12/1/2024.
//

#ifndef TREEPARSINGUTILITIES_H
#define TREEPARSINGUTILITIES_H
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Node.h"
#include "Utilities.h"


class TreeParsingUtilities {
public:
    TreeParsingUtilities();

    std::vector<std::string> tokenize(const std::string& RHS, const std::string& rule);

    Node* parseTree(
        std::vector<std::string> tokens,
        std::unordered_map<std::string, Node*>& regularDefinitions,
        std::unordered_map<std::string, Node*>& regularExpressions
    );

    static Node* processOperator(
        std::stack<Node*>& operandsStack,
        std::stack<char>& operatorsStack
    );

    Node* processString(const std::string& s) const;

    void printPostfix(Node* root);

private:
    Utilities utilities;
    std::unordered_set<char> reservedLexicalChars;
    std::unordered_set<char> reservedLexicalOperator;
    std::unordered_map<std::string, int> operatorsPrecedence;
};



#endif //TREEPARSINGUTILITIES_H
