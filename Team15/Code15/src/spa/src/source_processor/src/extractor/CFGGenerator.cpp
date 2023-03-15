#include "source_processor/include/extractor/CFGGenerator.h"

set<CFGNode*> setOfRoots = {};
unordered_map<int, CFGNode*> nodes;

void printCFG() {
    cout << endl << "printCFG" << endl;
    unordered_set<CFGNode*> visited;
    queue<CFGNode*> q;
    for (CFGNode* root : setOfRoots) {
        cout << "root: " << root->getLineNumber() << endl;
        q.push(root);
        while (!q.empty()) {
            CFGNode* curr = q.front();
            q.pop();
            if (visited.count(curr)) {
                continue;
            }
            visited.insert(curr);
            cout << curr->getLineNumber() << " : [";
            for (CFGNode* next : curr->getNext()) {
                cout << next->getLineNumber() << ", ";
                q.push(next);
            }
            cout << "]" << endl;
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

void helper(const vector<Line>& program, int start, CFGNode* rootNode, const string& rootLineType) {
    cout << endl << "Helper function - Starting line: " << start << endl;
    CFGNode* prevNode = rootNode;
    int endOfThen = 0;
    for (int i = start; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        CFGNode* currNode;
        if (lineNumber > 0) {
            currNode = nodes[lineNumber];
        } else {
            currNode = new CFGNode(); // temporary dummy node
        }
        cout << "currNode, lineType: " << lineType << ", lineNumber: " << lineNumber << endl;
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
            prevNode->addNext(currNode);
            helper(program, i + 1, currNode, "if");
        } else if (lineType == "else") {
            endOfThen = prevNode->getLineNumber(); //store previous line to link to join
            rootNode->addNext(prevNode);
        } else if (lineType == "while") {
            if (currNode->getLineNumber() != 0) prevNode->addNext(currNode);
            helper(program, i + 1, currNode, lineType);
        } else if (lineType == "}") {
            CFGNode* nextNode = nodes[prevNode->getLineNumber() + 1];
            if (rootLineType == "while") { // exiting while loop
                if (rootNode != prevNode) prevNode->addNext(rootNode);  // link last statement to head of while
                if (nextNode) { // if there is a statement after the while loop
                    // link head of while to first statement after loop
                    if (rootNode != nextNode) rootNode->addNext(nextNode);
                }
            } else if (rootLineType == "if" && nextNode) {
                // join end of "then" block and "else" block to the node outside "if-else" block
                nodes[endOfThen]->addNext(nextNode);
                prevNode->addNext(nextNode);
            }
//            rootNode->addNext(prevNode);
            return;
        } else {
            printCFG();
            if (currNode->getLineNumber() != 0 && currNode != prevNode) prevNode->addNext(currNode);
        }
        if (currNode->getLineNumber() != 0) {
            prevNode = currNode;
        }
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
