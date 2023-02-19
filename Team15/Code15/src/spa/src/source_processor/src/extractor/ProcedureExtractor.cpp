#include "source_processor/include/extractor/ProcedureExtractor.h"

string findProcedureName(vector<string> tokens) {
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "procedure") {
            return *(next(token));
        }
    }
    return "";
}

bool isProcedure(Line line) {
    return line.getType() == "procedure";
}

set<string> extractProcedures(const vector<Line>& program) {
    set<string> procedures;
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        set<string> *p = &procedures;
        if(isProcedure(line)) {
            string procedureName = findProcedureName(tokens);
            p->insert(procedureName);
        }
    }
    return procedures;
};
