//
// Created by mohamed_anwar on 12/24/24.
//

#ifndef LHSSTATE_H
#define LHSSTATE_H

#include "ParserState.h"

class LHSState final : public ParserState {
public:
    void parse(GrammarParser& parser, const std::string& buffer, int& index) override;
};

#endif //LHSSTATE_H
