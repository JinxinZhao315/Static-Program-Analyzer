#pragma once
#include "sp/include/extractor/CommonExtractorHeader.h"
#include "common/include/utils/StringOperations.h"

class ProcedureExtractor {
public:
    void extractProcedures(const vector<Line>& program);
    void extractCallLineNumToProcName(const vector<Line>& program);
    set<string> getProcedures();
    unordered_map<int, string> getCallLineNumToProcName();
private:
    set<string> procedures;
    unordered_map<int, string> callLineNumToProcName;
};
