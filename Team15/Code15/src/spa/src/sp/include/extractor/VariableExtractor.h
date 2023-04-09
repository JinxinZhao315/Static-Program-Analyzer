#pragma once
#include "sp/include/extractor/CommonExtractorHeader.h"
#include "common/include/models/Keywords.h"

class VariableExtractor {
private:
    Keywords* keywords;
    set<string> variables;
    unordered_map<int, string> readLineNumToVarName;
    unordered_map<int, string> printLineNumToVarName;
public:
    VariableExtractor();
    bool findVariable(string token);
    void extractVariables(const vector<Line>& program);
    set<string> getVariables();
    void extractReadAndPrintLineNumToVarName(const vector<Line>& program);
    unordered_map<int, string> getReadLineNumToVarName();
    unordered_map<int, string> getPrintLineNumToVarName();
    bool isVariable(const string& token, const string& previous);
};
