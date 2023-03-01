#pragma once

#include "CommonExtractorHeader.h"

struct ModifiesUsesCallsRS {
    unordered_map<int, set<string>> modifiesRS;
    unordered_map<string, set<string>> procedureModifiesRS;
    unordered_map<int, set<string>> usesRS;
    unordered_map<string, set<string>> procedureUsesRS;
    unordered_map<string, set<string>> callsRS;
    unordered_map<string, set<string>> callsStarRS;
};

ModifiesUsesCallsRS extractModifiesUsesAndCallRS(const vector<Line>& program, const set<string>& variables);
