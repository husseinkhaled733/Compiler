//
// Created by Samni on 11/29/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace RegexOperations {
    constexpr char ENUMERATION = '-';
    constexpr char CONCATENATION = '@';
    constexpr char KLEENE_STAR = '*';
    constexpr char KLEENE_PLUS = '+';
    constexpr char ALTERNATION = '|';
    constexpr char CLOSE_PARANTHESIS = ')';
    constexpr char OPEN_PARANTHESIS = '(';
}

namespace LexicalRules {
    constexpr char REGULAR_DEFINITION = '=';
    constexpr char REGULAR_EXPRESSION = ':';
    constexpr char OPEN_BRACES = '{';
    constexpr char CLOSE_BRACES = '}';
    constexpr char OPEN_BRACkET = '[';
    constexpr char CLOSE_BRACkET = ']';
}

const std::string DELIMITER = "delimiter";


#endif //CONSTANTS_H
