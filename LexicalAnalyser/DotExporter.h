//
// Created by mohamed_anwar on 12/1/24.
//

#ifndef DOTEXPORTER_H
#define DOTEXPORTER_H
#include "State.h"
#include "Utils.h"

class DotExporter {
public:
    static void exportToDot(const State* initialState, const std::string& filename) {
        std::ofstream out(filename);
        out << "digraph G {\n";
        out << "    rankdir=LR;\n";
        out << "    layout = \"dot\";\n";

        std::unordered_set<const State*> visited;
        exportStateToDot(initialState, out, visited);

        out << "}\n";
        out.close();
    }

private:
    static void exportStateToDot(const State* state, std::ofstream& out, std::unordered_set<const State*>& visited) {
        if (visited.contains(state)) {
            return;
        }

        visited.insert(state);

        std::string shape = state->isFinal ? "doublecircle" : "circle";

        out << "    \"" << state->id << "\" [label=\"" << state->id << "\" shape=" << shape << "];\n";

        for (const auto& [input, states] : state->transitions) {
            for (const auto& nextState : states) {
                std::string label = (input == epsilon) ? "ε" : std::string(1, input);
                out << "    \"" << state->id << "\" -> \"" << nextState->id << "\" [label=\"" << label << "\"];\n";
                exportStateToDot(nextState, out, visited);
            }
        }
    }
};



#endif //DOTEXPORTER_H
