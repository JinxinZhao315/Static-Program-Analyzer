#pragma once

#include <utility>

#include "CommonExtractorHeader.h"

class CFGNode {
public:
    int lineNumber;
    set<CFGNode*> next;

    CFGNode(int lineNumber) : lineNumber(lineNumber) {}

    // mainly for testing purposes
    void addNext(CFGNode* node) {
        next.insert(node);
    }
};
