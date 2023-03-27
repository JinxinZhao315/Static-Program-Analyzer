#include "Extractor.h"
#include "common/include/utils/StringOperations.h"

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS, const unordered_map<int, string>& callLineNumToProcName);
