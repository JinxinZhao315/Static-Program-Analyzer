#pragma once

#include <utility>

#include "CommonExtractorHeader.h"

class CFGNode {
public:
    int lineNumber;
    std::set<CFGNode*> next;
    bool isVisited = false;
    explicit CFGNode() : lineNumber(0), next() {}

    explicit CFGNode(int lineNumber) : lineNumber(lineNumber), next() {}

    [[nodiscard]] int getLineNumber() const { return lineNumber; }

    [[nodiscard]] const set<CFGNode*>& getNext() const { return next; }

    void addNext(CFGNode* successor) {
        if (successor->lineNumber != 0 && this->lineNumber != 0 && successor != this) {
            next.insert(successor);
        }
    }
    void markVisited() {
        isVisited = true;
    }

    bool hasBeenVisited() const {
        return isVisited;
    }
};
