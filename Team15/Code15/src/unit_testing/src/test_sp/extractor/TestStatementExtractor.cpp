#include "catch.hpp"
#include "sp/include/extractor/StatementExtractor.h"
#include "Constants.hpp"

using namespace std;

vector<Line> lines1 = {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"x", "=", "1", ";"}, ASSIGN),
        Line(2, {"y", "=", "2", ";"}, ASSIGN),
        Line(3, {"read", "z", ";"}, READ),
        Line({"}"}, CLOSE_CURLY)
};

unordered_map<KeywordsEnum, set<int>> expectedStatements1 = {
        { CALL, {}},
        { PRINT, {}},
        { ASSIGN , {1, 2}},
        { IF, {}},
        { READ, {3}},
        { WHILE, {}},
};

TEST_CASE("Extract statements from program with no nesting") {
    unordered_map<KeywordsEnum, set<int>> statements = extractStatements(lines1);
    REQUIRE(expectedStatements1 == statements);
}

vector<Line> lines2 = {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"read", "x", ";"}, READ),
        Line(2, {"if", "(", "x", ">", "0", ")", "{"}, IF),
        Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
};

unordered_map<KeywordsEnum, set<int>> expectedStatements2 = {
        { CALL, {}},
        { PRINT, {}},
        { ASSIGN , {3}},
        { IF, {2}},
        { READ, {1}},
        { WHILE, {}},
};

TEST_CASE("Extract statements from program with 1 level of nesting") {
    unordered_map<KeywordsEnum, set<int>> statements = extractStatements(lines2);
    REQUIRE(expectedStatements2 == statements);
}

vector<Line> lines3 = {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"read", "x", ";"}, READ),
        Line(2, {"while", "(", "x", ">", "0", ")", "{"}, WHILE),
        Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
        Line(4, {"read", "z", ";"}, READ),
        Line(5, {"if", "(", "z", "!=", "0", ")", "{"}, IF),
        Line(6, {"x", "=", "x", "*", "z", "/", "5", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"else", "{"}, ELSE),
        Line(7, {"x", "=", "z", "/", "x", "*", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
};

unordered_map<KeywordsEnum, set<int>> expectedStatements3 = {
        { CALL, {}},
        { PRINT, {}},
        { ASSIGN , {3, 6, 7}},
        { IF, {5}},
        { READ, {1, 4}},
        { WHILE, {2}},
};

TEST_CASE("Extract statements from program with 3 level of nesting") {
    unordered_map<KeywordsEnum, set<int>> statements = extractStatements(lines3);
    REQUIRE(expectedStatements3 == statements);
}

vector<Line> lines4 = {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"flag", "=", "0", ";"}, ASSIGN),
        Line(2, { "call", "computeCentroid", ";"}, CALL),
        Line(3, { "call", "printResults", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "readPoint", "{"}, PROCEDURE),
        Line(4, {"read", "x", ";"}, READ),
        Line(5, {"read", "y", ";"}, READ),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "printResults", "{"}, PROCEDURE),
        Line(6, {"print", "flag", ";"}, PRINT),
        Line(7, {"print", "cenX", ";"}, PRINT),
        Line(8, {"print", "cenY", ";"}, PRINT),
        Line(9, {"print", "normSq", ";"}, PRINT),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "computeCentroid", "{"}, PROCEDURE),
        Line(10, {"count", "=", "0", ";"}, ASSIGN),
        Line(11, {"cenX", "=", "0", ";"}, ASSIGN),
        Line(12, {"cenY", "=", "0", ";"}, ASSIGN),
        Line(13, { "call", "readPoint", ";"}, CALL),
        Line(14, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(15, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(16, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(17, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(18, { "call", "readPoint", ";"}, CALL),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(20, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"else", "{"}, ELSE),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
};

unordered_map<KeywordsEnum, set<int>> expectedStatements4 = {
        { CALL, {2, 3, 13, 18}},
        { PRINT, {6, 7, 8, 9}},
        { ASSIGN , {1, 10, 11, 12, 15, 16, 17, 20, 21, 22, 23}},
        { IF, {19}},
        { READ, {4, 5}},
        { WHILE, {14}},
};

TEST_CASE("Extract statements from program with multiple procedures") {
    unordered_map<KeywordsEnum, set<int>> statements = extractStatements(lines4);
    REQUIRE(expectedStatements4 == statements);
}

unordered_map<KeywordsEnum, set<int>> expectedStatementsSource4 = {
        { CALL, {}},
        { PRINT, {}},
        { ASSIGN , {1,2,3,8,9,11,12,13,14}},
        { IF, {6,7,10}},
        { READ, {}},
        { WHILE, {4,5}},
};

TEST_CASE("test source 4 extractor") {
    unordered_map<KeywordsEnum, set<int>> statements = extractStatements(source4);
    REQUIRE(expectedStatementsSource4 == statements);
}
