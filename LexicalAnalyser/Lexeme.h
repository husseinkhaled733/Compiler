//
// Created by mohamed_anwar on 11/27/24.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <bits/stdc++.h>

class Lexeme {
private:
    std::string tokenType;
    std::string value;

public:
    Lexeme();
    explicit Lexeme(std::string tokenType, std::string value);

    [[nodiscard]] std::string getTokenType() const;
    [[nodiscard]] std::string getValue() const;
};


#endif //TOKEN_H
