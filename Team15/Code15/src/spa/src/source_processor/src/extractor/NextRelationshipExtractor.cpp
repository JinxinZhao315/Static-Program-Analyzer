#include "source_processor/include/extractor/NextRelationshipExtractor.h"
#include "source_processor/include/extractor/CFGNode.h"

bool noNextNode(const CFGNode& node) {
    return node.next.empty();
}

unordered_map<int, set<int>> extractNextRSForProcedure(const CFGNode& rootNode,
    unordered_map<int, set<int>> currentProcNextRS) {
        if(!noNextNode(rootNode)) {
            for(const CFGNode& next : rootNode.next) {
                int rootLine = rootNode.lineNumber;
                int nextLine = next.lineNumber;
                currentProcNextRS[rootLine].insert(nextLine);
                extractNextRSForProcedure(next, currentProcNextRS);
            }
        }
        return currentProcNextRS;
}

unordered_map<int, set<int>> extractNextRS(const vector<CFGNode>& rootNodes) {
    unordered_map<int, set<int>> nextRS;
    unordered_map<int, set<int>> currentProcNextRS;
    for(const CFGNode& rootNode : rootNodes) {
        currentProcNextRS = extractNextRSForProcedure(rootNode, currentProcNextRS);
        nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
        currentProcNextRS.clear();
    }
    return nextRS;
}
