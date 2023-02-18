#include "source_processor/include/extractor/ProcedureExtractor.h"

string findProcedureName(vector<string> tokens) {
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "procedure") {
            return *(next(token));
        }
    }
    return "";
}

void ProcedureExtractor::extractProcedures(Line line) {
    vector<string> tokens = line.getTokens();
    string procedureName = findProcedureName(tokens);
    set<string>* p = &this->procedures;
    p->insert(procedureName);
}