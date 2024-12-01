//
// Created by Samni on 11/26/2024.
//

#ifndef STATE_H
#define STATE_H
#include<bits/stdc++.h>


class State
{
    public:
        explicit State(int id);
        explicit State(const std::string& token, int id);

        std::string token;
        int id;
        bool isFinal = false;

        std::unordered_map<char, std::vector<State*>> transitions;
        void addTransition(char input, State *state);
        std::vector<State*> applyTransition(char input);
};
#endif //STATE_H
