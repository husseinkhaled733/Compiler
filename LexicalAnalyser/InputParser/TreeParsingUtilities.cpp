//
// Created by Samni on 12/1/2024.
//

#include "TreeParsingUtilities.h"

#include "Constants.h"
#include <iostream>
#include <map>
#include <stdexcept>

TreeParsingUtilities::TreeParsingUtilities()
{
    reservedLexicalChars.insert(LexicalRules::REGULAR_DEFINITION);
    reservedLexicalChars.insert(LexicalRules::REGULAR_EXPRESSION);
    reservedLexicalChars.insert(RegexOperations::KLEENE_PLUS);
    reservedLexicalChars.insert(RegexOperations::ENUMERATION);
    reservedLexicalChars.insert(RegexOperations::KLEENE_STAR);
    reservedLexicalChars.insert(RegexOperations::OPEN_PARANTHESIS);
    reservedLexicalChars.insert(RegexOperations::CLOSE_PARANTHESIS);
    reservedLexicalChars.insert(LexicalRules::OPEN_BRACES);
    reservedLexicalChars.insert(LexicalRules::CLOSE_BRACES);
    reservedLexicalChars.insert(LexicalRules::OPEN_BRACkET);
    reservedLexicalChars.insert(LexicalRules::CLOSE_BRACkET);
    reservedLexicalChars.insert(RegexOperations::ALTERNATION);

    reservedLexicalOperator.insert(RegexOperations::KLEENE_PLUS);
    reservedLexicalOperator.insert(RegexOperations::ENUMERATION);
    reservedLexicalOperator.insert(RegexOperations::KLEENE_STAR);
    reservedLexicalOperator.insert(RegexOperations::OPEN_PARANTHESIS);
    reservedLexicalOperator.insert(RegexOperations::CLOSE_PARANTHESIS);
    reservedLexicalOperator.insert(RegexOperations::ALTERNATION);

    operatorsPrecedence[Utilities::charToString(RegexOperations::CLOSE_PARANTHESIS)] = 0;
    operatorsPrecedence[Utilities::charToString(RegexOperations::ENUMERATION)] = 1;
    operatorsPrecedence[Utilities::charToString(RegexOperations::KLEENE_PLUS)] = 2;
    operatorsPrecedence[Utilities::charToString(RegexOperations::KLEENE_STAR)] = 2;
    operatorsPrecedence[Utilities::charToString(RegexOperations::CONCATENATION)] = 3; // concatenation
    operatorsPrecedence[Utilities::charToString(RegexOperations::ALTERNATION)] = 4;
}


std::vector<std::string> TreeParsingUtilities::tokenize(const std::string& RHS, const std::string& rule)
{
    std::vector<std::string> RHSTokens;

    std:: string currToken;
    for (size_t i = 0; i < RHS.length(); ++i) {
        char c = RHS[i];

        if (c == ' ') {
            // Push current token if it's not empty and reset
            if (!currToken.empty()) {
                RHSTokens.push_back(currToken);
                currToken.clear();
            }
        }
        else if (c == '\\') {
            // Handle escape character
            ++i;
            if (i == RHS.length()) {
                throw std::invalid_argument(rule + " rule is invalid (incomplete escape sequence)");
            }

            char nextChar = RHS[i];
            if (nextChar == 'L') {
                if (!currToken.empty()) {
                    RHSTokens.push_back(currToken);
                    currToken.clear();
                }
                RHSTokens.emplace_back(" ");
            }
            else if (reservedLexicalChars.contains(nextChar)) {
                currToken += '\\';
                currToken += nextChar;
            }
            else {
                throw std::invalid_argument(rule + " rule is invalid (invalid escape character)");
            }
        }
        else if (reservedLexicalOperator.contains(c)) {
            // Push current token if it's not empty, then push the operator
            if (!currToken.empty()) {
                RHSTokens.push_back(currToken);
                currToken.clear();
            }
            RHSTokens.emplace_back(1, c);
        }
        else if (reservedLexicalChars.contains(c)){
            throw std::invalid_argument(rule + " rule is invalid (unescaped reserved lexical keyword)");
        }
        else {
            currToken += c;
        }
    }

    if (!currToken.empty()) {
        RHSTokens.push_back(currToken);
    }

    // Adding the concatenation operator in case of:
    // str or unary operator followed by (str or '(' )
    // ')' followed by str
    for (int i = 0; i < RHSTokens.size() - 1; i++) {
        if ((!operatorsPrecedence.contains(RHSTokens[i]) && RHSTokens[i]!="(" || (RHSTokens[i] == "*" || RHSTokens[i] == "+"))
            && (RHSTokens[i + 1] == "(" || !operatorsPrecedence.contains(RHSTokens[i + 1]))
            || RHSTokens[i] == ")" && !operatorsPrecedence.contains(RHSTokens[i + 1])) {

            RHSTokens.insert(RHSTokens.begin() + i + 1,
                Utilities::charToString(RegexOperations::CONCATENATION));
            i++;  // Skip the next element since it's been shifted by the insert
            }
    }
    return RHSTokens;
}

Node* TreeParsingUtilities::parseTree(std::vector<std::string> tokens, std::unordered_map<std::string, Node*>& regularDefinitions, std::unordered_map<std::string, Node*>& regularExpressions)
{
    std::stack<Node*> operandsStack;
    std::stack<char> operatorsStack;
    Node* currentNode;

    for (auto & token : tokens)
    {
        if (token == "(")
        {
            operatorsStack.push(token.at(0));
        }
        else if (!operatorsPrecedence.contains(token))
        {
            if (regularDefinitions.contains(token) && regularDefinitions[token]!=nullptr)
            {
                operandsStack.push(regularDefinitions[token]); continue;
            }

            if (regularExpressions.contains(token) && regularExpressions[token]!=nullptr)
            {
                operandsStack.push(regularExpressions[token]); continue;
            }
            Node* root = processString(token, RegexOperations::CONCATENATION);
            operandsStack.push(root);
        }
        else if (operatorsPrecedence[token] > 0)
        {
            while (!operatorsStack.empty() && operatorsStack.top()!='('
                && operatorsPrecedence[std::string(1,operatorsStack.top())] < operatorsPrecedence[token])
            {
                currentNode = processOperator(operandsStack, operatorsStack);
                operandsStack.push(currentNode);
            }
            operatorsStack.push(token.at(0));
        }
        else if (token == ")")
        {
            while (!operatorsStack.empty() && operatorsStack.top()!='(')
            {
                currentNode =  processOperator(operandsStack, operatorsStack);
                operandsStack.push(currentNode);

            }
            if (operatorsStack.empty()) throw std::invalid_argument("unmatched closed paranthesis");
            operatorsStack.pop();
        }
    }
    // Process remaining operators
    while (!operatorsStack.empty())
    {
        if (operatorsStack.top() == '(')
        {
            throw std::invalid_argument("Unmatched opening parenthesis.");
        }

        currentNode =  processOperator(operandsStack, operatorsStack);
        operandsStack.push(currentNode);
    }
    return operandsStack.top();
}

Node* TreeParsingUtilities::processOperator(std::stack<Node*>& operandsStack, std::stack<char>& operatorsStack)
{
    const auto currentNode = new Node(operatorsStack.top());
    operatorsStack.pop();

    Node* rightNode = nullptr;

    if (currentNode->value!=RegexOperations::KLEENE_PLUS && currentNode->value!=RegexOperations::KLEENE_STAR)
    {
        rightNode = operandsStack.top();
        operandsStack.pop();
    }
    const auto leftNode = operandsStack.top();
    operandsStack.pop();

    currentNode->left = leftNode;
    currentNode->right = rightNode;

    return currentNode;
}

Node* TreeParsingUtilities::processString(const std::string& s, char op) const
{
    Node* root = nullptr;
    for (int j = 0; j<s.length(); j++)
    {
        const char c = s.at(j);
        // handle escapes
        if (c=='\\' && j+1 < s.length() && reservedLexicalChars.contains(s.at(j+1))) continue;
        if (!root)
        {
            root = new Node(c);
        }
        else
        {
            const auto operatorNode = new Node(op);
            operatorNode->left = root;
            operatorNode->right = new Node(c);
            root = operatorNode;
        }
    }
    return root;
}

// Post-order traversal to print the postfix expression
void TreeParsingUtilities::printPostfix(Node* root) {
    if (root == nullptr) {
        return;
    }

    printPostfix(root->left);
    printPostfix(root->right);

    std::cout << root->value << " ";
}

