//
// Created by mohamed_anwar on 12/22/24.
//

#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H

#include "NonTerminal.h"
#include "Terminal.h"
#include <bits/stdc++.h>

using namespace std;

class ParsingTable {
public:
    static const int SYNC = -1;
    unordered_map<string, unordered_map<string, int>> table;
    void printParsingTable(unordered_map<string, vector<vector<Symbol *>>>&productions) const;
};


#endif //PARSINGTABLE_H
