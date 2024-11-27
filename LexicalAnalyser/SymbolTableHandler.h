//
// Created by mohamed_anwar on 11/27/24.
//

#ifndef SYMBOLTABLEHANDLER_H
#define SYMBOLTABLEHANDLER_H

#include <bits/stdc++.h>


class SymbolTableHandler {

    enum class SymbolType { Integer, Float, Boolean };

    class SymbolTableEntry {
        SymbolType type;

    public:
        explicit SymbolTableEntry(const SymbolType type) : type(type) {}
        [[nodiscard]] SymbolType getType() const {
            return type;
        }
        [[nodiscard]] std::string toString() const {
            switch (type) {
            case SymbolType::Integer:
                return "int";
            case SymbolType::Float:
                return "float";
            case SymbolType::Boolean:
                return "boolean";
            default:
                return "NA";
            }
        }
    };

    std::unordered_map<std::string, SymbolTableEntry> symbolTable;

public:
    SymbolTableHandler();

    bool addSymbol(const std::string& symbol, SymbolType type);
    SymbolTableEntry getSymbol(const std::string& symbol);
    bool containsSymbol(const std::string& symbol) const;
    void clear();
};


#endif // SYMBOLTABLEHANDLER_H
