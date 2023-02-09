#include "../../include/extractor/CFGNode.h"

void CFGNode::addIncomingEdge(CFGNode *node) {
    incomingEdges.push_back(node);
}

void CFGNode::addOutgoingEdge(CFGNode *node) {
    outgoingEdges.push_back(node)
}

vector<CFGNode *> &CFGNode::getIncomingEdges() {
    return incomingEdges;
}

vector<CFGNode *> &CFGNode::getOutgoingEdges() {
    return outgoingEdges;
}
