#pragma once

#include <iostream>
#include <vector>
#include "../parser/Line.h"

using namespace std;
using namespace Line;

class CFGNode {
public:
    CFGNode(int id, Line line) {
        this->id = id;
        this->line = line;
    };
    void addIncomingEdge(CFGNode *node);
    void addOutgoingEdge(CFGNode *node);
    vector<CFGNode*>& getIncomingEdges();
    vector<CFGNode*>& getOutgoingEdges();
protected:
    int id;
    Line line;
    int nestingLevel;
private:
    vector<CFGNode*> incomingEdges;
    vector<CFGNode*> outgoingEdges;
};