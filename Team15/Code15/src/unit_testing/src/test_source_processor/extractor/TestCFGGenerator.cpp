#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/CFGGenerator.h"

void compareCFG(set<CFGNode*> cfg1, set<CFGNode*> cfg2) {
    cout << "compareCFG" << endl;
    // Compare the sizes of the sets
//    if (cfg1.size() != cfg2.size()) {
//        FAIL("Sets have different sizes");
//        return;
//    }
    // Traverse each root node in the set and compare their successors
    for (auto it1 = cfg1.begin(), it2 = cfg2.begin(); it1 != cfg1.end() && it2 != cfg2.end(); it1++, it2++) {
        cout << "test 1";
        CFGNode* node1 = *it1;
        CFGNode* node2 = *it2;
        while (node1 != nullptr && node2 != nullptr) {
            cout << "test";
            REQUIRE(node1->getLineNumber() == node2->getLineNumber());
            REQUIRE(node1->getNext() == node2->getNext());
            node1 = *(node1->getNext().begin());
            node2 = *(node2->getNext().begin());
        }
    }
}


TEST_CASE("Empty Program") {
    const vector<Line>& lines = {};
    const set<CFGNode*> expected = {};
    auto result = generateCFG(lines);
    REQUIRE(expected == result);
}

TEST_CASE("No nesting") {
    const set<CFGNode *> expected = {};
    auto result = generateCFG(mainProgram);
    compareCFG(expected, result);
}

TEST_CASE("whileLoop") {
    const set<CFGNode*> expected = {};
    auto result = generateCFG(whileLoopInProcedure);
//    compareCFG(expected, result);
}


TEST_CASE("whileLoopWithLineBeforeAfter") {
    const set<CFGNode*> expected = {};
    auto result = generateCFG(whileLoopInProcedureWithLinesBeforeAfter);
//    compareCFG(expected, result);
}

TEST_CASE("ifElseInProcedure") {
    const set<CFGNode*> expected = {};
    auto result = generateCFG(ifElseInProcedure);
//    compareCFG(expected, result);
}