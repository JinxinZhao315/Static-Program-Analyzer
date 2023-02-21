#include "source_processor/include/extractor/ConstantExtractor.h"

bool tokenIsNumeric(const string& token) {
    try {
        stoi(token);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

set<string> extractConstants(const vector<Line>& program) {
    set<string> constants;
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        set<string> *c = &constants;
        for (auto token = begin(tokens); token != end(tokens); token++) {
            if (tokenIsNumeric(*token)) {
                c->insert(*token);
            }
        }
    }
    return constants;
}
