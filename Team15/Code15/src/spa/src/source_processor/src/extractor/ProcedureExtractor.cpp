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

void ProcedureExtractor::extractProcedures(const vector<Line>& program) {
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        set<string> *p = &procedures;
        if(isProcedure(line)) {
            string procedureName = findProcedureName(tokens);
            p->insert(procedureName);
        }
    }
};

bool isEmptyProcedure(const string& procedure) {
    return procedure.empty();
}

void ProcedureExtractor::extractCallLineNumToProcName(const vector<Line> &program) {
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        string type = line.getType();
        int lineNumber = line.getLineNumber();
        if(type == "call") {
            string procedure = getProcedureNameFromCallStatement(tokens);
            callLineNumToProcName[lineNumber] = procedure;
        }
    }
}

set<string> ProcedureExtractor::getProcedures() {
    return procedures;
}

unordered_map<int, string> ProcedureExtractor::getCallLineNumToProcName() {
    return callLineNumToProcName;
}
