//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef SYMBOL_H
#define SYMBOL_H

#include <bits/stdc++.h>

#include <utility>
using namespace std;


class Symbol {
    string name;
public:
    explicit Symbol(string name) : name(move(name)) {}

    virtual bool isTerminal() = 0;
    virtual ~Symbol() = default;

    [[nodiscard]] const string& getName() const {
        return name;
    }
};

#endif //SYMBOL_H
