//
// Created by mohamed_anwar on 12/25/24.
//

#include "LHSState.h"

#include "ParserUtils.h"
#include "RHSState.h"

void LHSState::parse(GrammarParser& parser, const std::string& buffer, int& index) {
    const int bufferSize = buffer.size();
    std::string currentLHS = "";

    while (index < bufferSize) {

        if (std::string assignment = buffer.substr(index, 3); assignment == "::=") {
            trim(currentLHS);
            validateNonTerminal(currentLHS);

            parser.setCurrentNonTerminal(parser.getGrammar()->getNonTerminals()[currentLHS]);
            parser.setState(new RHSState());
            index += 3;
            return;
        }

        currentLHS += buffer[index++];
    }
}
