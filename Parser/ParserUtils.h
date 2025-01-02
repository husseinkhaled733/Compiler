//
// Created by mohamed_anwar on 12/30/24.
//

#ifndef PARSERUTILS_H
#define PARSERUTILS_H

#include <bits/stdc++.h>

using namespace std;

inline void ltrim(string& s) {
    s.erase(s.begin(), ranges::find_if(s, [](const unsigned char ch) {
        return !isspace(ch);
    }));
}

inline void rtrim(string& s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

inline void trim(string& str) {
    ltrim(str);
    rtrim(str);
}

inline bool isWordCharacter(const char c) {
    return isalnum(static_cast<unsigned char>(c)) || c == '_';
}

inline void validateNonTerminal(const string& nonTerminalName) {
    if (nonTerminalName.empty())
        throw invalid_argument("Non-terminal is empty");

    for (const char c : nonTerminalName) {
        if (!isWordCharacter(c)) {
            const string logMessage = "Invalid character in NonTerminal: "
                + string(1, c) + ", In Non-terminal: " + nonTerminalName;
            throw invalid_argument(logMessage);
        }
    }
}

#endif //PARSERUTILS_H
