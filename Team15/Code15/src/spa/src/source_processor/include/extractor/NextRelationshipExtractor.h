#pragma once

#include "CommonExtractorHeader.h"
#include "CFGNode.h"

unordered_map<int, set<int>> extractNextRS(const vector<CFGNode*>& rootNodes);
