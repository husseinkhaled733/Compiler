//
// Created by Samni on 12/1/2024.
//

#include "TreeParsingUtilities.h"

#include <iostream>
#include <map>
#include <stdexcept>

TreeParsingUtilities::TreeParsingUtilities()
{
    reservedLexicalChars.insert('=');
    reservedLexicalChars.insert(':');
    reservedLexicalChars.insert('+');
    reservedLexicalChars.insert('-');
    reservedLexicalChars.insert('*');
    reservedLexicalChars.insert('(');
    reservedLexicalChars.insert(')');
    reservedLexicalChars.insert('{');
    reservedLexicalChars.insert('}');
    reservedLexicalChars.insert('|');

    reservedLexicalOperator.insert('+');
    reservedLexicalOperator.insert('-');
    reservedLexicalOperator.insert('*');
    reservedLexicalOperator.insert('(');
    reservedLexicalOperator.insert(')');
    reservedLexicalOperator.insert('|');

    operatorsPrecedence[")"] = 0;
    operatorsPrecedence["-"] = 1;
    operatorsPrecedence["+"] = 2;
    operatorsPrecedence["*"] = 2;
    operatorsPrecedence["@"] = 3; // concatenation
    operatorsPrecedence["|"] = 4;
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

            RHSTokens.insert(RHSTokens.begin() + i + 1, "@");
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
            Node* root = processString(token);
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

    if (currentNode->value!='+' && currentNode->value!='*')
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

Node* TreeParsingUtilities::processString(const std::string& s) const
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
            const auto operatorNode = new Node('@');
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

