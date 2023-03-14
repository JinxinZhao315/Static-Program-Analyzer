#include "source_processor/include/extractor/NextRelationshipExtractor.h"

bool noNextNode(const CFGNode& node) {
    return node.next.empty();
}

bool checkPair(int rootLine, int nextLine, unordered_map<int, set<int>> currentProcNextRS) {
    if(currentProcNextRS.count(rootLine) == 0) {
        return true;
    } else {
        set<int> rootSet = currentProcNextRS.at(rootLine);
        return rootSet.find(nextLine) == rootSet.end();
    }
}

unordered_map<int, set<int>> extractNextRSForProcedure(CFGNode* rootNode,
    unordered_map<int, set<int>> currentProcNextRS) {
        if(!noNextNode(*rootNode)) {
            for(CFGNode* next : rootNode->next) {
                int rootLine = rootNode->lineNumber;
                int nextLine = next->lineNumber;
                if(!checkPair(rootLine, nextLine, currentProcNextRS)) {
                    // cycle detected
                    continue;
                }
                currentProcNextRS[rootLine].insert(nextLine);
                unordered_map<int, set<int>> temp = (extractNextRSForProcedure(next, currentProcNextRS));
                currentProcNextRS.insert(temp.begin(), temp.end());
            }
        }
        return currentProcNextRS;
}

unordered_map<int, set<int>> extractNextRS(const vector<CFGNode*>& rootNodes) {
    unordered_map<int, set<int>> nextRS;
    unordered_map<int, set<int>> currentProcNextRS;
    for(CFGNode* rootNode : rootNodes) {
        currentProcNextRS = extractNextRSForProcedure(rootNode, currentProcNextRS);
        nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
        currentProcNextRS.clear();
    }
    return nextRS;
}
