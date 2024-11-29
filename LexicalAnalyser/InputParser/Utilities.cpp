//
// Created by Samni on 11/28/2024.
//

#include "Utilities.h"

// Removes leading and trailing whitespace
// (tabs, newlines, carriage returns, form feeds, and vertical tabs)
void Utilities::strip(std::string& s)
{
    s.erase(s.find_last_not_of("\t\n\r\f\v")+1);
    s.erase(0, s.find_first_not_of("\t\n\r\f\v"));
}
