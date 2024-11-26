//
// Created by Samni on 11/26/2024.
//

#ifndef STATE_H
#define STATE_H
#include<bits/stdc++.h>


class State
{
    public:
        State();
        explicit State(const std::string& token);

        std::string token;
        bool isFinal = false;
        std::unordered_map<char, State> transitions;
        void addTransition(char input, State state);
        State applyTransition(char input);
};
#endif //STATE_H
