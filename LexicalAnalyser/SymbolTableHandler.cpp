//
// Created by mohamed_anwar on 11/27/24.
//

#include "SymbolTableHandler.h"

SymbolTableHandler::SymbolTableHandler() = default;

bool SymbolTableHandler::addSymbol(const std::string& symbol) {
    if (symbolTable.contains(symbol))
        return false;

    symbolTable[symbol] = SymbolTableEntry(SymbolType::None);
    return true;
}

SymbolTableHandler::SymbolTableEntry SymbolTableHandler::getSymbol(const std::string& symbol) {
    return symbolTable[symbol];
}

bool SymbolTableHandler::containsSymbol(const std::string& symbol) const {
    return symbolTable.contains(symbol);
}

void SymbolTableHandler::clear() {
    symbolTable.clear();
}
