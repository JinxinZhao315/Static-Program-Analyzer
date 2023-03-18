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
    map<int, set<int>> result = generateCFG(lines);
    REQUIRE(result, Equals(expected));
}

TEST_CASE("No nesting") {
    const set<CFGNode *> expected = {};
    map<int, set<int>> result = generateCFG(mainProgram);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("whileLoop") {
    const set<CFGNode*> expected = {};
    map<int, set<int>> result = generateCFG(whileLoopInProcedure);
    REQUIRE_THAT(result, Equals(expected));
}


TEST_CASE("whileLoopWithLineBeforeAfter") {
    const set<CFGNode*> expected = {};
    map<int, set<int>> result = generateCFG(whileLoopInProcedureWithLinesBeforeAfter);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("ifElseInProcedure") {
    const set<CFGNode*> expected = {};
    map<int, set<int>> result = generateCFG(ifElseInProcedure);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("ifNoElseNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("ifNoElseWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("ifAndElseNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
            {2, {3}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("ifAndElseWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {5}},
            {4, {5}},
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_whileNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_whileWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {2, 4}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_whileNestedInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(3, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 6}},
            {3, {4, 5}},
            {4, {3, 5}},
            {5, {2, 6}},
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_ifWithElseNestedInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 7}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {2, 7}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}


TEST_CASE("extractNextRelationship_ifWithElseWhileNestedInEachBranch") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_whileWithNestedIfWithElse") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 7}},
            {2, {3}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {1, 7}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}

TEST_CASE("extractNextRelationship_ifWithElseEachBranchHasNestedWhileWithNestedIfWithElse") {
    const vector<Line> &lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(7, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(9, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 6}},
            {2, {3}},
            {3, {4, 5}},
            {4, {2}},
            {5, {2}},
            {6, {7}},
            {7, {8, 9}},
            {8, {6}},
            {9, {6}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
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

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {5, {6}},
            {6, {5}}
    };

    map<int, set<int>> result = generateCFG(lines);
    REQUIRE_THAT(result, Equals(expected));
}
