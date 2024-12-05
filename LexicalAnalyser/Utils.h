//
// Created by Samni on 11/26/2024.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <unordered_map>
#include "State.h"

inline std::unordered_map<std::string, int> priorities;
inline char epsilon = 0;
void traverse(State* startState);

#endif //UTILS_H
