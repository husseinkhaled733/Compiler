//
// Created by mohamed_anwar on 11/27/24.
//

#include "Lexeme.h"

#include <utility>

Lexeme::Lexeme() = default;
Lexeme::Lexeme(std::string tokenType, std::string value)
        : tokenType(std::move(tokenType)), value(std::move(value)) {}

std::string Lexeme::getTokenType() const {
    return tokenType;
}
std::string Lexeme::getValue() const {
    return value;
}