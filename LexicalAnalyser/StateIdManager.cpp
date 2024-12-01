//
// Created by mohamed_anwar on 12/1/24.
//

#include "StateIdManager.h"

StateIdManager::StateIdManager() : currentId(0) {}

StateIdManager& StateIdManager::getInstance() {
    static StateIdManager instance;
    return instance;
}

std::string StateIdManager::getNextId() {
    return std::to_string(currentId++);
}

void StateIdManager::reset() {
    currentId = 0;
}
