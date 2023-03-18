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

string ProcedureExtractor::findProcedure(vector<string> tokens) {
    for(auto token : tokens) {
        if(find(procedures.begin(), procedures.end(), token) != procedures.end()) {
            return token;
        }
    }
    return "";
}

bool isEmptyProcedure(string procedure) {
    return procedure == "";
}

void ProcedureExtractor::extractCallLineNumToProcName(const vector<Line> &program) {
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        string type = line.getType();
        int lineNumber = line.getLineNumber();
        string procedure = findProcedure(tokens);
        if(!isEmptyProcedure(procedure) && type == "call") {
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
