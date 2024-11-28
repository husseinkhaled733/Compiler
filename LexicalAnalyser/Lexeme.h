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
    explicit Lexeme(const std::string& tokenType, const std::string& value);

    std::string getTokenType() const;
    std::string getValue() const;
};


#endif //TOKEN_H
