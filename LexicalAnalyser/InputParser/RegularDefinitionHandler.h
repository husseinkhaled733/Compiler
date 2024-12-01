//
// Created by Samni on 11/28/2024.
//
#pragma once
#include <unordered_set>
#include <queue>
#include "RulesHandler.h"
#include "Constants.h"

class RegularDefinitionHandler final
{
public:
    std::unordered_set<char> reservedLexicalChars;
    std::unordered_set<char> reservedLexicalOperator;
    std::unordered_map<std::string, int> operatorsPrecedence;
    void handleRule(const std::string& rule, RegexTreeBuilder& builder)
    {
		// assume I am splitting on the first occurence of :
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
        operatorsPrecedence["."] = 3; // concatenation
        operatorsPrecedence["|"] = 4;

        const std::vector<std::string> tokens = splitByDelimiter(rule, ':', 2);
        std::string LHS = tokens.at(0);
        std::string RHS = tokens.at(1);
        std::vector<std::string> RHSTokens = tokenize(RHS, rule);
        // printTree(parseTree(RHSTokens), 0);
        trim(LHS);
        builder.regexDefinitions[LHS] = parseTree(RHSTokens, builder.regexDefinitions);
        std::cout<<"debugging: "<<LHS<<std::endl;

        // std::cout<<builder.regexDefinitions[LHS]->value;
        // inorderTraversal(builder.regexDefinitions[LHS]);printLevelByLevel(builder.regexDefinitions[LHS]);
        printPostfix(builder.regexDefinitions[LHS]);

    }

    std::vector<std::string> tokenize(const std::string& RHS, const std::string& rule)
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

        std::cout << RHSTokens[0].length() << std::endl;
        // Adding the concatenation operator in case of:
        // str or unary operator followed by (str or '(' )
        // ')' followed by str
        for (int i = 0; i < RHSTokens.size() - 1; i++) {
            if ((!operatorsPrecedence.contains(RHSTokens[i]) && RHSTokens[i]!="(" || (RHSTokens[i] == "*" || RHSTokens[i] == "+"))
                && (RHSTokens[i + 1] == "(" || !operatorsPrecedence.contains(RHSTokens[i + 1]))
                || RHSTokens[i] == ")" && !operatorsPrecedence.contains(RHSTokens[i + 1])) {

                RHSTokens.insert(RHSTokens.begin() + i + 1, ".");
                std::cout << "Inserted \".\" at index " << i << std::endl;
                i++;  // Skip the next element since it's been shifted by the insert
                }
        }

        for (const std::string& token : RHSTokens)
        {
            std::cout << token << std::endl;
        }

        return RHSTokens;
    }

    Node* parseTree(std::vector<std::string> tokens, std::unordered_map<std::string, Node*>& regularDefinitions, std::unordered_map<std::string, Node*>& regularExpressions)
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
                if (regularDefinitions[token]!=nullptr)
                {
                    operandsStack.push(regularDefinitions[token]); continue;
                }
                if (regularExpressions[token]!=nullptr)
                {
                    operandsStack.push(regularExpressions[token]); continue;
                }
                Node* root = nullptr;
                for (int j = 0; j<token.length(); ++j)
                {
                    const char c = token.at(j);
                    // handle escapes
                    if (c=='\\' && j+1 < token.length() && reservedLexicalChars.contains(token.at(j+1))) continue;
                    if (!root)
                    {
                        root = new Node(c);
                    }
                    else
                    {
                        const auto operatorNode = new Node('.');
                        operatorNode->left = root;
                        operatorNode->right = new Node(c);
                        root = operatorNode;
                    }
                }
                operandsStack.push(root);
            }
            else if (operatorsPrecedence[token] > 0)
            {
                while (!operatorsStack.empty() && operatorsStack.top()!='('
                    && operatorsPrecedence[std::string(1,operatorsStack.top())] < operatorsPrecedence[token])
                {
                    currentNode = new Node(operatorsStack.top());
                    operatorsStack.pop();

                    Node* rightNode = nullptr;

                    if (currentNode->value!='+' && currentNode->value!='*')
                    {
                        rightNode = operandsStack.top();
                        operandsStack.pop();
                    }
                    auto leftNode = operandsStack.top();
                    operandsStack.pop();

                    currentNode->left = leftNode;
                    currentNode->right = rightNode;

                    operandsStack.push(currentNode);
                }
                operatorsStack.push(token.at(0));
            }
            else if (token == ")")
            {
                while (!operatorsStack.empty() && operatorsStack.top()!='(')
                {
                    currentNode = new Node(operatorsStack.top());
                    operatorsStack.pop();
                    auto rightNode = operandsStack.top();
                    operandsStack.pop();
                    auto leftNode = operandsStack.top();
                    operandsStack.pop();
                    currentNode->right = rightNode;
                    currentNode->left = leftNode;
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

            currentNode = new Node(operatorsStack.top());
            operatorsStack.pop();

            Node* rightNode = nullptr;
            if (currentNode->value!='*' && currentNode->value!='+')
            {
                rightNode = operandsStack.top();
                operandsStack.pop();
            }

            Node* leftNode = operandsStack.top();
            operandsStack.pop();

            currentNode->right = rightNode;
            currentNode->left = leftNode;
            operandsStack.push(currentNode);
        }
        return operandsStack.top();
    }



    void printLevelByLevel(Node* root) {
        if (root == nullptr) {
            return;
        }

        // Use a queue for BFS
        std::queue<Node*> q;
        q.push(root);

        int level = 0; // Track the current level

        while (!q.empty()) {
            int levelSize = q.size();  // Number of nodes at the current level
            std::cout << "Level " << level << ": ";

            // Print all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();
                std::cout << current->value << " ";  // Print the current node value

                // Add children to the queue
                if (current->left != nullptr) {
                    q.push(current->left);
                }
                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }
            std::cout << std::endl;  // Print a newline after each level
            level++; // Increment level
        }
    }

    void trim(std::string& s)
    {
        const std::string& blanks = " \t\n\r";
        s.erase(s.find_last_not_of(blanks)+1);
        s.erase(0, s.find_first_not_of(blanks));
    }

    // Post-order traversal to print the postfix expression
    void printPostfix(Node* root) {
        if (root == nullptr) {
            return;
        }

        // Traverse the left subtree
        printPostfix(root->left);

        // Traverse the right subtree
        printPostfix(root->right);

        // Visit the root node (print it)
        std::cout << root->value << " ";
    }

//     Node* parseTree(std::vector<std::string> tokens)
// {
//     std::stack<Node*> operandsStack;
//     std::stack<char> operatorsStack;
//
//     // Ensure operatorsPrecedence is defined outside this function
//     for (const auto & token : tokens)
//     {
//         if (token == "(")
//         {
//             operatorsStack.push('(');
//         }
//         else if (token == ")")
//         {
//             // Process operators until matching '(' is found
//             while (!operatorsStack.empty() && operatorsStack.top() != '(')
//             {
//                 Node* currentNode = new Node(operatorsStack.top());
//                 operatorsStack.pop();
//
//                 // Build the subtree with right and left nodes
//                 Node* rightNode = operandsStack.top();
//                 operandsStack.pop();
//                 Node* leftNode = operandsStack.top();
//                 operandsStack.pop();
//
//                 currentNode->right = rightNode;
//                 currentNode->left = leftNode;
//                 operandsStack.push(currentNode);
//             }
//
//             // Check for unmatched '('
//             if (operatorsStack.empty() || operatorsStack.top() != '(')
//             {
//                 throw std::invalid_argument("Unmatched closing parenthesis.");
//             }
//             operatorsStack.pop(); // Remove the matching '('
//         }
//         else if (!operatorsPrecedence.contains(token)) // Operand
//         {
//             Node* root = nullptr;
//             for (const char c : token)
//             {
//                 if (!root)
//                 {
//                     root = new Node(c);
//                 }
//                 else
//                 {
//                     Node* operatorNode = new Node('.');
//                     operatorNode->left = root;
//                     operatorNode->right = new Node(c);
//                     root = operatorNode;
//                 }
//             }
//             operandsStack.push(root);
//         }
//         else if (operatorsPrecedence[token] > 0) // Operator
//         {
//             while (!operatorsStack.empty() && operatorsStack.top() != '(' &&
//                    operatorsPrecedence[std::string(1, operatorsStack.top())] >= operatorsPrecedence[token])
//             {
//                 Node* currentNode = new Node(operatorsStack.top());
//                 operatorsStack.pop();
//
//                 Node* rightNode = operandsStack.top();
//                 operandsStack.pop();
//                 Node* leftNode = operandsStack.top();
//                 operandsStack.pop();
//
//                 currentNode->right = rightNode;
//                 currentNode->left = leftNode;
//                 operandsStack.push(currentNode);
//             }
//             operatorsStack.push(token.at(0));
//         }
//         else
//         {
//             throw std::invalid_argument("Invalid token: " + token);
//         }
//         std::cout << "operators stack: ";
//         {
//             std::stack<char> temp = operatorsStack; // Copy the stack
//             while (!temp.empty()) {
//                 std::cout << temp.top() << " "; // Access the top element
//                 temp.pop();                    // Remove the top element
//             }
//         }
//         std::cout << std::endl;
//
//         std::cout << "operands stack: ";
//         {
//             std::stack<Node*> temp = operandsStack; // Copy the stack
//             while (!temp.empty()) {
//                 std::cout << temp.top()->value << " "; // Access the top element's value
//                 temp.pop();                           // Remove the top element
//             }
//         }
//         std::cout << std::endl;
//     }
//
//     // Process remaining operators
//     // while (!operatorsStack.empty())
//     // {
//     //     if (operatorsStack.top() == '(')
//     //     {
//     //         throw std::invalid_argument("Unmatched opening parenthesis.");
//     //     }
//     //
//     //     Node* currentNode = new Node(operatorsStack.top());
//     //     operatorsStack.pop();
//     //
//     //     Node* rightNode = operandsStack.top();
//     //     operandsStack.pop();
//     //     Node* leftNode = operandsStack.top();
//     //     operandsStack.pop();
//     //
//     //     currentNode->right = rightNode;
//     //     currentNode->left = leftNode;
//     //     operandsStack.push(currentNode);
//     // }
//
//     // Final check: the operandsStack should have exactly one node (the root)
//         std::cout<<operandsStack.size()<<std::endl;
//     // if (operandsStack.size() != 1)
//     // {
//     //     throw std::runtime_error("Invalid expression.");
//     // }
//
//     return operandsStack.top();
// }
    void printTree(Node* root, int level = 0) {
        if (root == nullptr) return;

        // Print the current node's value, with indentation based on its level in the tree
        std::string indent(level * 4, ' ');  // 4 spaces per level for better visibility
        std::cout << indent << root->value << std::endl;

        // Recur for left and right subtrees, with an increased indentation
        if (root->left || root->right) {
            std::cout << indent << "Left -> ";
            printTree(root->left, level + 1);  // Print left subtree
            std::cout << indent << "Right -> ";
            printTree(root->right, level + 1); // Print right subtree
        }
    }

    void inorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        // Traverse the left subtree
        inorderTraversal(root->left);

        // Visit the root node
        std::cout << root->value;

        // Traverse the right subtree
        inorderTraversal(root->right);
    }





    bool checkRule(const std::string& rule)
    {
        const size_t pos = rule.find('=');

        // check if = exists and isn't escaped
        return pos != std::string::npos && rule.at(pos - 1) != '\\';
    }

    static std::vector<std::string> splitByDelimiter(const std::string& s, char delimiter, int max) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = s.find(delimiter);

        while (end != std::string::npos && tokens.size() < max) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
            end = s.find(delimiter, start);
        }
        tokens.push_back(s.substr(start));

        return tokens;
    }

};