//
// Created by mohamed_anwar on 12/24/24.
//

#ifndef PARSERSTATE_H
#define PARSERSTATE_H

#include "GrammarParser.h"

class ParserState {
public:
    virtual ~ParserState() = default;
    virtual void parse(GrammarParser& parser, const std::string& buffer, int& index) = 0;
};

#endif //PARSERSTATE_H
