#pragma once

#include "CommonExtractorHeader.h"

struct CFGNode {
    int lineNumber;
    set<CFGNode> next;

    CFGNode(int lineNumber) : lineNumber(lineNumber) {}
};
