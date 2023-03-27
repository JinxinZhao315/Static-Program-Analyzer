#include "Extractor.h"
#include "common/include/utils/StringOperations.h"

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS, const unordered_map<int, string>& callLineNumToProcName);
void linkStoredLines(vector<int>& nodesToJoin, const vector<pair<int, string>>& nestingStack, const unordered_map<int, int>& followsRS,  unordered_map<int, set<int>>& cfg);
