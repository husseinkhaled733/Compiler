//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef TERMINAL_H
#define TERMINAL_H


#include "Symbol.h"
#include <bits/stdc++.h>


class Terminal final : public Symbol {
public:
    explicit Terminal(const string& name) : Symbol(name) {}
    bool isTerminal() override { return true; }
};

template <>
struct std::hash<Terminal*> {
    size_t operator()(const Terminal* s) const noexcept {
        return hash<string>{}(s->getName());
    }
};

template <>
struct std::equal_to<Terminal*> {
    bool operator()(const Terminal* lhs, const Terminal* rhs) const {
        return lhs->getName() == rhs->getName();
    }
};

#endif //TERMINAL_H
