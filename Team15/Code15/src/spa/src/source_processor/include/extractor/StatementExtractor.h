#pragma once

#include "CommonExtractorHeader.h"

class StatementExtractor {
private:
    unordered_map<string, set<int>>  statements;
    set<string> variables;
public:
    StatementExtractor();
    unordered_map<string, set<int>> getStatements();
    set<string> getVariables();
    void extractStatements(Line line);
    void extractVariables(Line line);
};
