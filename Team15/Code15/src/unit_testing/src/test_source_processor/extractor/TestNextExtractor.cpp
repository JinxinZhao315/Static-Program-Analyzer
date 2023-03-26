#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/NextRelationshipExtractor.h"
#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

void printNodes(const unordered_map<int, set<int>>& myMap) {
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": [";
        for (const auto& v : value) {
            std::cout << v << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void compareCFG(const unordered_map<int, set<int>>& result, const unordered_map<int, set<int>>& expected) {
    if (result != expected) {
        cout << "Result: " << endl;
        printNodes(result);
        cout << "Expected: " << endl;
        printNodes(expected);
    }
    REQUIRE(result == expected);
}

TEST_CASE("Empty Program") {
    const vector<Line>& lines = {};
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    unordered_map<int, set<int>> expected = {};
    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("IfElseNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("IfElseWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {5}},
            {4, {5}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
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
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {2}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
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
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 6}},
            {3, {4, 5}},
            {4, {3}},
            {5, {2}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseNestedInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 7}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {2}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}


TEST_CASE("extractNextRelationship_ifElseWhileNestedInEachBranch") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2, 4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseWhileNestedInEachBranch2") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {3, {2}},
            {4, {8}},
            {5, {6}},
            {6, {7, 8}},
            {7, {6}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileWithNestedIfElse") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, "while"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2, 7}},
            {2, {3}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {1}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseEachBranchHasNestedWhileWithNestedIfElse") {
    const vector<Line> &lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}", "else", "{"}, "else"),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(7, {"if", "(", "y", "==", "1", ")", "{"}, "if"),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(9, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

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

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("ifWithNestedIfElseInThenAndNestedWhileInElse") {
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
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {5, {6}},
            {6, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimple") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"y", "=", "0", ";"}, "="),
            Line(2, {"y", "=", "1", ";"}, "="),
            Line(3, {"y", "=", "2", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(4, {"x", "=", "0", ";"}, "="),
            Line(5, {"x", "=", "1", ";"}, "="),
            Line(6, {"x", "=", "2", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "C", "{"}, "procedure"),
            Line(7, {"z", "=", "0", ";"}, "="),
            Line(8, {"z", "=", "1", ";"}, "="),
            Line(9, {"z", "=", "2", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProc") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(3, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(4, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(5, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(6, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "C", "{"}, "procedure"),
            Line(7, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(8, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(9, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2,3}},
            {4, {5,6}},
            {7, {8,9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcLineBeforeAndAfterIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"y", "=", "y", "+", "1", ";"}, "="),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(5, {"y", "=", "y", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(7, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(8, {"x", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(9, {"x", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(10, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "C", "{"}, "procedure"),
            Line(11, {"z", "=", "z", "+", "1", ";"}, "="),
            Line(12, {"if", "(", "z", "==", "1", ")", "then", "{"}, "if"),
            Line(13, {"z", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(14, {"z", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(15, {"z", "=", "z", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {5}},
            {4, {5}},
            {6, {7}},
            {7, {8,9}},
            {8, {10}},
            {9, {10}},
            {11, {12}},
            {12, {13,14}},
            {13, {15}},
            {14, {15}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcMultipleLinesBeforeAfterAndInIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"y", "=", "y", "+", "1", ";"}, "="),
            Line(2, {"y", "=", "y", "+", "2", ";"}, "="),
            Line(3, {"y", "=", "y", "+", "3", ";"}, "="),
            Line(4, {"if", "(", "y", "==", "6", ")", "then", "{"}, "if"),
            Line(5, {"y", "=", "0", ";"}, "="),
            Line(6, {"y", "=", "y", "+", "2", ";"}, "="),
            Line(7, {"y", "=", "y", "+", "3", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(8, {"y", "=", "1", ";"}, "="),
            Line(9, {"y", "=", "y", "+", "2", ";"}, "="),
            Line(10, {"y", "=", "y", "+", "3", ";"}, "="),
            Line({"}"}, "}"),
            Line(11, {"y", "=", "y", "+", "1", ";"}, "="),
            Line(12, {"y", "=", "y", "+", "2", ";"}, "="),
            Line(13, {"y", "=", "y", "+", "3", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(14, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(15, {"x", "=", "x", "+", "2", ";"}, "="),
            Line(16, {"x", "=", "x", "+", "3", ";"}, "="),
            Line(17, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(18, {"x", "=", "0", ";"}, "="),
            Line(19, {"x", "=", "x", "+", "2", ";"}, "="),
            Line(20, {"x", "=", "x", "+", "3", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(21, {"x", "=", "1", ";"}, "="),
            Line(22, {"x", "=", "x", "+", "2", ";"}, "="),
            Line(23, {"x", "=", "x", "+", "3", ";"}, "="),
            Line({"}"}, "}"),
            Line(24, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(25, {"x", "=", "x", "+", "2", ";"}, "="),
            Line(26, {"x", "=", "x", "+", "3", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5,8}},
            {5, {6}},
            {6, {7}},
            {7, {11}},
            {8, {9}},
            {9, {10}},
            {10, {11}},
            {11, {12}},
            {12, {13}},
            {14, {15}},
            {15, {16}},
            {16, {17}},
            {17, {18, 21}},
            {18, {19}},
            {19, {20}},
            {20, {24}},
            {21, {22}},
            {22, {23}},
            {23, {24}},
            {24, {25}},
            {25, {26}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProc") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "C", "{"}, "procedure"),
            Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}},
            {3, {4}},
            {4, {3}},
            {5, {6}},
            {6, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcLinesBeforeAndAfterWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "C", "{"}, "procedure"),
            Line(9, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(11, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(12, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {2}},
            {5, {6}},
            {6, {7,8}},
            {7, {6}},
            {9, {10}},
            {10, {11,12}},
            {11, {10}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcMultipleLinesBeforeAfterAndInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"x", "=", "x", "+", "2", ";"}, "="),
            Line(3, {"x", "=", "x", "+", "3", ";"}, "="),
            Line(4, {"while", "(", "x", "==", "6", ")", "then", "{"}, "while"),
            Line(5, {"x", "=", "x", "+", "4", ";"}, "="),
            Line(6, {"x", "=", "x", "+", "5", ";"}, "="),
            Line(7, {"x", "=", "x", "+", "6", ";"}, "="),
            Line({"}"}, "}"),
            Line(8, {"x", "=", "x", "+", "7", ";"}, "="),
            Line(9, {"x", "=", "x", "+", "8", ";"}, "="),
            Line(10, {"x", "=", "x", "+", "9", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(11, {"y", "=", "y", "+", "1", ";"}, "="),
            Line(12, {"y", "=", "y", "+", "2", ";"}, "="),
            Line(13, {"y", "=", "y", "+", "3", ";"}, "="),
            Line(14, {"while", "(", "y", "==", "6", ")", "then", "{"}, "while"),
            Line(15, {"y", "=", "y", "+", "4", ";"}, "="),
            Line(16, {"y", "=", "y", "+", "5", ";"}, "="),
            Line(17, {"y", "=", "y", "+", "6", ";"}, "="),
            Line({"}"}, "}"),
            Line(18, {"y", "=", "y", "+", "7", ";"}, "="),
            Line(19, {"y", "=", "y", "+", "8", ";"}, "="),
            Line(20, {"y", "=", "y", "+", "9", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5,8}},
            {5, {6}},
            {6, {7}},
            {7, {4}},
            {8, {9}},
            {9, {10}},
            {11, {12}},
            {12, {13}},
            {13, {14}},
            {14, {15,18}},
            {15, {16}},
            {16, {17}},
            {17, {14}},
            {18, {19}},
            {19, {20}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(7, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(8, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {1}},
            {4, {1}},
            {5, {6}},
            {6, {7,8}},
            {7, {5}},
            {8, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhileLineBeforeAfterAndIn") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"y", "=", "0", ";"}, "="),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"y", "=", "0", ";"}, "="),
            Line(4, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(5, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(6, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(7, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line(8, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(9, {"y", "=", "0", ";"}, "="),
            Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(11, {"y", "=", "0", ";"}, "="),
            Line(12, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(13, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(14, {"y", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(15, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line(16, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 8}},
            {3, {4}},
            {4, {5,6}},
            {5, {7}},
            {6, {7}},
            {7, {2}},
            {9, {10}},
            {10, {11, 16}},
            {11, {12}},
            {12, {13, 14}},
            {13, {15}},
            {14, {15}},
            {15, {10}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhileMultipleLinesBeforeAfterAndIn") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"y", "=", "0", ";"}, "="),
            Line(2, {"y", "=", "0", ";"}, "="),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(4, {"y", "=", "0", ";"}, "="),
            Line(5, {"y", "=", "0", ";"}, "="),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(7, {"y", "=", "0", ";"}, "="),
            Line(8, {"y", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(9, {"y", "=", "1", ";"}, "="),
            Line(10, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line(11, {"y", "=", "0", ";"}, "="),
            Line(12, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line(13, {"y", "=", "0", ";"}, "="),
            Line(14, {"y", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(15, {"x", "=", "0", ";"}, "="),
            Line(16, {"x", "=", "0", ";"}, "="),
            Line(17, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(18, {"x", "=", "0", ";"}, "="),
            Line(19, {"x", "=", "0", ";"}, "="),
            Line(20, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(21, {"x", "=", "0", ";"}, "="),
            Line(22, {"x", "=", "0", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(23, {"x", "=", "0", ";"}, "="),
            Line(24, {"x", "=", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(25, {"x", "=", "0", ";"}, "="),
            Line(26, {"x", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
            Line(27, {"x", "=", "0", ";"}, "="),
            Line(28, {"x", "=", "0", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4, 13}},
            {4, {5}},
            {5, {6}},
            {6, {7, 9}},
            {7, {8}},
            {8, {11}},
            {9, {10}},
            {10, {11}},
            {11, {12}},
            {12, {3}},
            {13, {14}},
            {15, {16}},
            {16, {17}},
            {17, {18, 27}},
            {18, {19}},
            {19, {20}},
            {20, {21, 23}},
            {21, {22}},
            {22, {25}},
            {23, {24}},
            {24, {25}},
            {25, {26}},
            {26, {17}},
            {27, {28}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}", "else", "{"}, "else"),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(7, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}", "else", "{"}, "else"),
            Line(9, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(10, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2,4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
            {6, {7,9}},
            {7, {8}},
            {8, {7}},
            {9, {10}},
            {10, {9}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIfLineBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(6, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(8, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(9, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(10, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(11, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(12, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(13, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(14, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(15, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(16, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(17, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(18, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(19, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(20, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(21, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(22, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,7}},
            {3, {4}},
            {4, {5,6}},
            {5, {4}},
            {6, {11}},
            {7, {8}},
            {8, {9,10}},
            {9, {8}},
            {10, {11}},
            {12, {13}},
            {13, {14, 18}},
            {14, {15}},
            {15, {16,17}},
            {16, {15}},
            {17, {22}},
            {18, {19}},
            {19, {20,21}},
            {20, {19}},
            {21, {22}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIfMultipleLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, "procedure"),
            Line(1, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(4, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(5, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(7, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(8, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(9, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(10, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(11, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(12, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(13, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(14, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(15, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(16, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(17, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(18, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(19, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"procedure", "B", "{"}, "procedure"),
            Line(20, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(21, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(22, {"if", "(", "y", "==", "1", ")", "then", "{"}, "if"),
            Line(23, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(24, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(25, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(26, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(27, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(28, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(29, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(30, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(31, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(32, {"while", "(", "x", "==", "1", ")", "then", "{"}, "while"),
            Line(33, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(34, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(35, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(36, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line(37, {"x", "=", "x", "+", "1", ";"}, "="),
            Line(38, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4,11}},
            {4, {5}},
            {5, {6}},
            {6, {7,9}},
            {7, {8}},
            {8, {6}},
            {9, {10}},
            {10, {18}},
            {11, {12}},
            {12, {13}},
            {13, {14, 16}},
            {14, {15}},
            {15, {13}},
            {16, {17}},
            {17, {18}},
            {18, {19}},
            {20, {21}},
            {21, {22}},
            {22, {23, 30}},
            {23, {24}},
            {24, {25}},
            {25, {26, 28}},
            {26, {27}},
            {27, {25}},
            {28, {29}},
            {29, {37}},
            {30, {31}},
            {31, {32}},
            {32, {33, 35}},
            {33, {34}},
            {34, {32}},
            {35, {36}},
            {36, {37}},
            {37, {38}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}
