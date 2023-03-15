#include "source_processor/include/extractor/CFGGenerator.h"

set<CFGNode*> setOfRoots = {};
unordered_map<int, CFGNode*> nodes;

void printCFG() {
    cout << "printCFG" << endl;
    unordered_set<CFGNode*> visited;
    queue<CFGNode*> q;
    for (CFGNode* root : setOfRoots) {
        cout << "printing root: " << root->getLineNumber() << endl;
        q.push(root);
        while (!q.empty()) {
            CFGNode* curr = q.front();
            q.pop();
            if (visited.count(curr)) {
                continue;
            }
            visited.insert(curr);
            cout << "Line " << curr->getLineNumber() << " successors: ";
            for (CFGNode* next : curr->getNext()) {
                cout << next->getLineNumber() << " ";
                q.push(next);
            }
            cout << endl;
        }
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

void addSuccessor(CFGNode* currNode, CFGNode* prevNode) {
    if (currNode->getLineNumber() != 0 && currNode != prevNode) {
        prevNode->addNext(currNode);
    }
}

void helper(const vector<Line>& program, int start, CFGNode* rootNode, string rootLineType) {
    cout << endl << "Helper function - Starting line: " << start << endl;
    CFGNode* prevNode = rootNode;
    for (int i = start; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        CFGNode* currNode;
        if (lineNumber > 0) {
            currNode = nodes[lineNumber];
        } else {
            currNode = new CFGNode();
        }
        cout << "currNode, lineType: " << lineType << endl;
        if (currNode->hasBeenVisited()) {
            cout << "Visited before: " << lineNumber << endl;
            continue;
        }
        currNode->markVisited();
        if (lineType == "procedure") {
            auto* newRoot = new CFGNode(-1);
            setOfRoots.insert(newRoot);
            helper(program, i + 1, newRoot, "procedure");
        } else if (lineType == "if") {
            addSuccessor(currNode, prevNode);
            helper(program, i + 1, currNode, "if");
        } else if (lineType == "else") {
            addSuccessor(rootNode, prevNode);
        } else if (lineType == "while") {
            addSuccessor(currNode, prevNode);
            helper(program, i + 1, currNode, lineType);
        } else if (lineType == "}") {
            //end of while loop or if-else
            if (rootLineType == "while") { // exiting while loop
                addSuccessor(rootNode, prevNode);  // link last statement to head of while
                if (nodes[lineNumber + 1]) {
                    // link head of while to first statement after loops
                    addSuccessor(nodes[lineNumber + 1], rootNode);
                }
            }
            addSuccessor(prevNode, rootNode);
            return;
        } else {
            addSuccessor(currNode, prevNode);
        }
        addSuccessor(currNode, prevNode);
    }
}


set<CFGNode*> generateCFG(const vector<Line>& program) {
    if (program.size() < 2) {
        return setOfRoots;
    }
    nodes = createNodes(program);
    // Create first node
    cout << "Generate CFG" << endl;
    auto* rootNode = new CFGNode(-1); // create dummy node
    setOfRoots.insert(rootNode);
    helper(program, 1, rootNode, "");
    cout << endl << endl;
    printCFG();
    return setOfRoots;
}
