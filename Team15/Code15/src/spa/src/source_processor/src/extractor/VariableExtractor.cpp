#include "source_processor/include/extractor/VariableExtractor.h"

set<string> extractVariables(const vector<Line>& program) {
    set<string> variables;
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        string type = line.getType();
        set<string>* v = &variables;
        for(auto token = begin(tokens); token != end(tokens); token++) {
            if(*token == "=" && token != begin(tokens)) {
                v->insert(*(prev(token)));
            } else if (*token == "read" && token != end(tokens)) {
                v->insert(*next(token));
            }
        }
    }
    return variables;
}