//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef STATEIDMANAGER_H
#define STATEIDMANAGER_H


#pragma once

class StateIdManager {
private:
    int currentId;
    StateIdManager();

public:
    StateIdManager(const StateIdManager&) = delete;
    StateIdManager& operator=(const StateIdManager&) = delete;

    static StateIdManager& getInstance();
    int getNextId();
    void reset();
};



#endif //STATEIDMANAGER_H
