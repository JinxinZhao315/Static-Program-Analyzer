#include "source_processor/include/extractor/CFGNode.h"
#include "unordered_set"
#include "queue"

unordered_map<int, CFGNode*> createNodes(const std::vector<Line>& program);
set<CFGNode*> generateCFG(const vector<Line>& program);