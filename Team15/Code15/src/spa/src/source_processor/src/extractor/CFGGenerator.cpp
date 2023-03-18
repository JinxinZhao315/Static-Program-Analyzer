#include "source_processor/include/extractor/CFGGenerator.h"

set<CFGNode*> setOfRoots = {};
unordered_map<int, CFGNode*> nodes;
unordered_set<int> processedLines = {};


void printNodes() {

    for (auto& entry : nodes) {
        CFGNode* node = entry.second;
        if (entry.first < 1 || entry.second == NULL) {
            continue;
        }
        set<CFGNode*> nextNodes = node->getNext();
        cout << entry.first << " : [";
        for (auto& nextNode : nextNodes) {
            cout << nextNode->getLineNumber() << ", ";
        }
        cout << " ]" << endl;
    }

}

unordered_map<int, CFGNode*> createNodes(const vector<Line>& program) {
    for (Line line : program) {
        int lineNumber = line.getLineNumber();
        if (lineNumber > 0) {
            nodes[lineNumber] = new CFGNode(lineNumber);
        }
    }
    return nodes;
}

set<CFGNode*> generateCFG(const vector<Line>& program) {
    if (program.size() < 2) {
        return setOfRoots;
    }

    nodes = createNodes(program);
    auto* rootNode = new CFGNode(-1); // create dummy node
    setOfRoots.insert(rootNode);

    struct StackEntry {
        CFGNode* node;
        string lineType;
        int endOfThen;
    };

    stack<StackEntry> stack;
    stack.push({rootNode, "", 0});

    CFGNode* prevNode = rootNode;

    for (int i = 1; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        CFGNode* currNode;

        if (lineNumber > 0) {
            currNode = nodes[lineNumber];
        } else {
            currNode = new CFGNode(); // temporary dummy node
        }

        if (processedLines.count(i) != 0) {
            continue;
        }

        processedLines.insert(i);
        CFGNode* nextNode = nodes[prevNode->getLineNumber() + 1];

        StackEntry& entry = stack.top();

        if (lineType == "procedure") {
            auto* newRoot = new CFGNode(-1);
            setOfRoots.insert(newRoot);
            stack.push({newRoot, "procedure", 0});
            prevNode = nullptr;
        } else if (lineType == "if" || lineType == "while") {
            prevNode->addNext(currNode);
            stack.push({currNode, lineType, 0});
            prevNode = nullptr;
        } else if (lineType == "else") {
            entry.endOfThen = prevNode->getLineNumber();
            if (nextNode) prevNode->addNext(nextNode);
            prevNode = nullptr;
        } else if (lineType == "}") {
            if (entry.lineType == "while") {
                prevNode->addNext(entry.node);
                if (nextNode) {
                    entry.node->addNext(nextNode);
                }
            } else if (entry.lineType == "if" && nextNode) {
                nodes[entry.endOfThen]->addNext(nextNode);
                prevNode->addNext(nextNode);
            }
            stack.pop();
            prevNode = nullptr;
        } else {
            if (prevNode) {
                prevNode->addNext(currNode);
            }
        }

        if (currNode->getLineNumber() != 0) {
            prevNode = currNode;
        }
    }

    printNodes();
    return setOfRoots;
}
