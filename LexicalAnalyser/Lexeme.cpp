//
// Created by mohamed_anwar on 11/27/24.
//

#include "Lexeme.h"

Lexeme::Lexeme() = default;
Lexeme::Lexeme(const std::string& tokenType, const std::string& value)
        : tokenType(tokenType), value(value) {}

std::string Lexeme::getTokenType() const {
    return tokenType;
}
std::string Lexeme::getValue() const {
    return value;
}