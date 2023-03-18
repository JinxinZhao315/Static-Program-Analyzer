#include "source_processor/include/extractor/CFGNode.h"
#include "unordered_set"
#include "queue"

void printNodes(const map<int, set<int>> &myMap);
unordered_map<int, set<int>> generateCFG(const vector<Line>& program);