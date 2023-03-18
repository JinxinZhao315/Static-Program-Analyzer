#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/CFGGenerator.h"

void compareCFG(set<CFGNode*> cfg1, set<CFGNode*> cfg2) {
//    cout << "compareCFG" << endl;
    // Compare the sizes of the sets
    if (cfg1.size() != cfg2.size()) {
        FAIL("Sets have different sizes");
        return;
    }
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
    generateCFG(lines);
//    REQUIRE(expected == result);
}

TEST_CASE("No nesting") {
    const set<CFGNode *> expected = {};
    generateCFG(mainProgram);
//    compareCFG(expected, result);
}

TEST_CASE("whileLoop") {
    const set<CFGNode*> expected = {};
    generateCFG(whileLoopInProcedure);
//    compareCFG(expected, result);
}


TEST_CASE("whileLoopWithLineBeforeAfter") {
    const set<CFGNode*> expected = {};
    generateCFG(whileLoopInProcedureWithLinesBeforeAfter);
//    compareCFG(expected, result);
}

TEST_CASE("ifElseInProcedure") {
    const set<CFGNode*> expected = {};
    generateCFG(ifElseInProcedure);
//    compareCFG(expected, result);
}

TEST_CASE("ifWithNestedIfAndElseInThenAndNestedWhileInElse") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}", "else", "{"}, "else"),
            Line(5, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    map<int, set<int>> result = generateCFG(lines);
//    REQUIRE_THAT(result, Equals(expected)); //TODO: write expected
//    compareCFG(expected, result);
}
