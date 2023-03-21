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
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
    };

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
            {2, {3}}
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
            {3, {2, 4}}
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
