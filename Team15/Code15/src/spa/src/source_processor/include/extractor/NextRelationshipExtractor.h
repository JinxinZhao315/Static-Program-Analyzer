#include "Extractor.h"

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS);
void storeLinesToLink(const Line& prevLine, const pair<int, string>& justExited, const int& prevLineNumber, vector<int>& nodesToJoin);
void linkStoredLines(vector<int>& nodesToJoin, const vector<pair<int, string>>& nestingStack, const unordered_map<int, int>& followsRS,  unordered_map<int, set<int>>& cfg);
