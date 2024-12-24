//
// Created by mohamed_anwar on 12/25/24.
//

#include "LHSState.h"
#include "RHSState.h"

void LHSState::parse(GrammarParser& parser, const std::string& buffer, int& index) {
    const int bufferSize = buffer.size();
    std::string currentLHS = "";

    while (index < bufferSize) {
        if (Grammar::IGNORED_CHARS.contains(buffer[index])) {
            index++;
            continue;
        }

        // Check for "::=" assignment operator
        if (std::string assignment = buffer.substr(index, 3); assignment == "::=") {
            parser.setCurrentNonTerminal(parser.getGrammar()->getNonTerminals()[currentLHS]);
            parser.setState(new RHSState());
            index += 3;
            return;
        }

        currentLHS += buffer[index];
        index++;
    }
}
