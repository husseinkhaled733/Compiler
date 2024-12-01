//
// Created by Samni on 11/28/2024.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <vector>


class Utilities {
    public:
        Utilities() = default;

        static void trim(std::string& s);

        static void removeFirstAndLastCharacters(std::string& s);

        static void removeOccurrences(std::string& s, char c);

        std::string getStringWithoutOccureneces(std::string& s, char c);

        static std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter);

        static std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter, int max);

        static std::vector<std::string> splitBySpaces(const std::string& s);

};



#endif //UTILITIES_H
