//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "Symbol.h"
#include "Terminal.h"
#include <bits/stdc++.h>

using namespace std;

class NonTerminal final : public Symbol {
public:
    class NonTerminalOccurrence {
    public:
        NonTerminal* nonTerminal;
        int derivationIndex;
        int inDerivationIndex;

        NonTerminalOccurrence(NonTerminal* nt, const int derivationIdx, const int inDerivationIdx)
            : nonTerminal(nt), derivationIndex(derivationIdx), inDerivationIndex(inDerivationIdx) {}
    };

private:
    unordered_set<Terminal*> firstSet;
    unordered_set<Terminal*> followSet;
    vector<NonTerminalOccurrence*> occurrencePositions;
    bool nullable;

public:
    explicit NonTerminal(const string& name) : Symbol(name), nullable(false) {}

    bool isTerminal() override {
        return false;
    }

    void addToFirstSet(Terminal* terminal) {
        firstSet.insert(terminal);
    }

    void addToFollowSet(Terminal* terminal) {
        followSet.insert(terminal);
    }

    void addOccurrence(NonTerminal* nonTerminal, int derivationIndex, int inDerivationIndex) {
        occurrencePositions.push_back(
            new NonTerminalOccurrence(nonTerminal, derivationIndex, inDerivationIndex)
        );
    }

    unordered_set<Terminal*>& getFirstSet() {
        return firstSet;
    }

    unordered_set<Terminal*>& getFollowSet() {
        return followSet;
    }

    vector<NonTerminalOccurrence*>& getOccurrencePositions() {
        return occurrencePositions;
    }

    bool isNullable() const {
        return nullable;
    }

    void setNullable(const bool value) {
        nullable = value;
    }

    ~NonTerminal() override {
        for (const auto occ : occurrencePositions) {
            delete occ;
        }
    }
};

template <>
struct std::hash<NonTerminal*> {
    size_t operator()(const NonTerminal* s) const noexcept {
        return hash<string>{}(s->getName());
    }
};

template <>
struct std::equal_to<NonTerminal*> {
    bool operator()(const NonTerminal* lhs, const NonTerminal* rhs) const {
        return lhs->getName() == rhs->getName();
    }
};

#endif // NONTERMINAL_H
