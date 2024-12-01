//
// Created by Samni on 11/28/2024.
//

#include "Utilities.h"
#include <iostream>
#include <regex>
#include <fstream>

// Removes leading and trailing whitespace
// (tabs, newlines, carriage returns, form feeds, and vertical tabs)



std::vector<std::string> Utilities::splitByDelimiter(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start));

    return tokens;
}

 std::vector<std::string> Utilities::splitByDelimiter(const std::string& s, char delimiter, int max) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos && tokens.size() < max) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start));

    return tokens;
}

void Utilities::trim(std::string& s) {
	const std::string& blanks = " \t\n\r";
    s.erase(s.find_last_not_of(blanks)+1);
    s.erase(0, s.find_first_not_of(blanks));
}

std::string Utilities::charToString(const char c) {
    return std::string(1, c);
}

void Utilities::removeFirstAndLastCharacters(std::string& s) {
    if (s.length() > 1) {
        s.erase(s.length() - 1);
        s.erase(0, 1);
    } else {
        s.clear();
    }
}
void Utilities::removeOccurrences(std::string& s, char charToRemove) {
    std::erase(s, charToRemove);
}
std::string getStringWithoutOccureneces(std::string& s, char charToRemove)
{
    std::string result = s;
    std::erase(s, charToRemove);
    return result;
}
std::vector<std::string> Utilities::splitBySpaces(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream stream(s);
    std::string token;

    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}
