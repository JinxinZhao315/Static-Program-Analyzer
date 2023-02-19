#include "catch.hpp"
#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

vector<Line> mainProgram = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
};
vector<Line> whileLoop = {
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
};

vector<Line> whileLoop2 = {
        Line(4, {"call", "readPoint", ";"}, "call"),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(10, {"call", "readPoint", ";"}, "call"),
};

vector<Line> computeCentroid = {
        Line({"procedure", "computeCentroid", "{"}, "procedure"),
        Line(1, {"count", "=", "0", ";"}, "="),
        Line(2, {"cenX", "=", "0", ";"}, "="),
        Line(3, {"cenY", "=", "0", ";"}, "="),
        Line(4, {"call", "readPoint", ";"}, "call"),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(10, {"if", "(", "count", "==", "0", ")", "then", "{"}, "if"),
        Line(11, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(12, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(13, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(14, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
};

vector<Line> ifElse = {
        Line(19, {"if", "(", "count", "==", "0", ")", "then", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
};

vector<Line> ifElse2 = {
        Line(18, {"call", "readPoint", ";"}, "call"),
        Line(19, {"if", "(", "count", "==", "0", ")", "then", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
};

vector<Line> program = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
        Line({"procedure", "readPoint", "{"}, "procedure"),
        Line(4, {"read", "x", ";"}, "READ_STATEMENT"),
        Line(5, {"read", "y", ";"}, "READ_STATEMENT"),
        Line({"}"}, "}"),
        Line({"procedure", "printResults", "{"}, "procedure"),
        Line(6, {"print", "flag", ";"}, "print"),
        Line(7, {"print", "cenX", ";"}, "print"),
        Line(8, {"print", "cenY", ";"}, "print"),
        Line(9, {"print", "normSq", ";"}, "print"),
        Line({"}"}, "}"),
        Line({"procedure", "computeCentroid", "{"}, "procedure"),
        Line(10, {"count", "=", "0", ";"}, "="),
        Line(11, {"cenX", "=", "0", ";"}, "="),
        Line(12, {"cenY", "=", "0", ";"}, "="),
        Line(13, {"call", "readPoint", ";"}, "call"),
        Line(14, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(15, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(16, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(17, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(18, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(19, {"if", "(", "count", "==", "0", ")", "then", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
};

TEST_CASE("extractFollowsRelationship_noNesting") {
    auto [result, result2] = extractFollowsRelationship(mainProgram);
    unordered_map<int, int> expectedFollows = {{1,2}, {2,3}};
    unordered_map<int, set<int>> expectedFollowsStar = {{1, {2, 3}}, {2, {3}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withWhileLoop") {
    auto [result, result2] = extractFollowsRelationship(whileLoop);
    unordered_map<int, int> expectedFollows = {{6,7}, {7,8}, {8,9}};
    unordered_map<int, set<int>> expectedFollowsStar = {{6, {7,8,9}}, {7, {8,9}}, {8, {9}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withWhileLoopStatementBeforeAndAfter") {
    auto [result, result2] = extractFollowsRelationship(whileLoop2);
    unordered_map<int, int> expectedFollows = {{4,5}, {6,7}, {7,8}, {8,9}, {5, 10}};
    unordered_map<int, set<int>> expectedFollowsStar = {{4, {5,10}}, {5, {10}}, {6, {7,8,9}}, {7, {8,9}}, {8, {9}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withIfElse") {
    auto [result, result2] = extractFollowsRelationship(ifElse);
    unordered_map<int, int> expectedFollows = {{21,22}};
    unordered_map<int, set<int>> expectedFollowsStar = {{21, {22}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withIfElseStatementBeforeAndAfter") {
    auto [result, result2] = extractFollowsRelationship(ifElse2);
    unordered_map<int, int> expectedFollows = {{18,19}, {19,23}, {21,22}};
    unordered_map<int, set<int>> expectedFollowsStar = {{18, {19,23}}, {19, {23}}, {21, {22}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withNesting") {
    auto [result, result2] = extractFollowsRelationship(computeCentroid);
    unordered_map<int, int> expectedFollows = {{1,2}, {2,3}, {3,4}, {4,5}, {6,7}, {7,8},
                                               {8,9}, {5,10}, {10,14}, {12,13}};
    unordered_map<int, set<int>> expectedFollowsStar = {{1,{2,3,4,5,10,14}},{2,{3,4,5,10,14}},{3,{4,5,10,14}},
        {4,{5,10,14}},{5,{10,14}},{6,{7,8,9}},{7,{8,9}},{8,{9}},{10,{14}},{12,{13}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}
