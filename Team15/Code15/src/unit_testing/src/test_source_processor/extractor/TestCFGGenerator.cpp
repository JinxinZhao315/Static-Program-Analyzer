#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/CFGGenerator.h"

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
    unordered_map<int, set<int>> expected = {};
    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("ifAndElseNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, "procedure"),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, "if"),
            Line(2, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}", "else", "{"}, "else"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("ifAndElseWithLinesBeforeAndAfter") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {5}},
            {4, {5}},
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {2}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 6}},
            {3, {4, 5}},
            {4, {3}},
            {5, {2}},
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifWithElseNestedInWhile") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 7}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {2}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}


TEST_CASE("extractNextRelationship_ifWithElseWhileNestedInEachBranch") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2, 4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifWithElseWhileNestedInEachBranch2") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {3, {2}},
            {4, {8}},
            {5, {6}},
            {6, {7, 8}},
            {7, {6}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileWithNestedIfWithElse") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2, 7}},
            {2, {3}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {1}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifWithElseEachBranchHasNestedWhileWithNestedIfWithElse") {
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

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
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

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfAndElseInEachProc") {
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

    unordered_map<int, set<int>> expected = {
            {1, {2,3}},
            {4, {5,6}},
            {7, {8,9}},
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfAndElseInEachProcLineBeforeAndAfterIf") {
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

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfAndElseInEachProcMultipleLinesBeforeAfterAndInIf") {
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

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {3, {4}},
            {5, {6}}
    };

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> result = generateCFG(lines);
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

    unordered_map<int, set<int>> result = generateCFG(lines);
    compareCFG(result, expected);
}
