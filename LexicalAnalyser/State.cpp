//
// Created by Samni on 11/26/2024.
//

#include "State.h"
#include <utility>

State::State() = default;
State::State(const std::string& token)
{
    this->token = token;
    this->isFinal = true;
}
State State::applyTransition(const char input)
{
    return this->transitions[input];
}
void State::addTransition(const char input, State state)
{
    this->transitions[input] = std::move(state);
}

