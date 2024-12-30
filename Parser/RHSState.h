//
// Created by mohamed_anwar on 12/24/24.
//

#ifndef RHSSTATE_H
#define RHSSTATE_H

#include "ParserState.h"

class RHSState final : public ParserState {

    Terminal* parseTerminal(const GrammarParser& parser, const std::string& buffer, int& index);
    NonTerminal* parseNonTerminal(const GrammarParser& parser, const std::string& buffer, int& index, int inDerivationIndex);

public:
    void parse(GrammarParser& parser, const std::string& buffer, int& index) override;
};



#endif //RHSSTATE_H
