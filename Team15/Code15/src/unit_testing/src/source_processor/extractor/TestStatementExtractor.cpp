#include "catch.hpp"
#include "source_processor/include/extractor/StatementExtractor.h";
#include "Constants.hpp"

using namespace std;

vector<Line> lines1 = {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"x", "=", "1", ";"}, "="),
        Line(2, {"y", "=", "2", ";"}, "="),
        Line(3, {"read", "z", ";"}, "read"),
        Line({"}"}, "}")
};

unordered_map<string, set<int>> expectedStatements1 = {
        {"call", {}},
        { "print", {}},
        { "=", {1, 2}},
        { "if", {}},
        { "read", {3}},
        { "while", {}},
};

TEST_CASE("Extract statements from program with no nesting") {
    unordered_map<string, set<int>> statements = extractStatements(lines1);
    REQUIRE(expectedStatements1 == statements);
}

vector<Line> lines2 = {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"read", "x", ";"}, "read"),
        Line(2, {"if", "(", "x", ">", "0", ")", "{"}, "if"),
        Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
};

unordered_map<string, set<int>> expectedStatements2 = {
        {"call", {}},
        { "print", {}},
        { "=", {3}},
        { "if", {2}},
        { "read", {1}},
        { "while", {}},
};

TEST_CASE("Extract statements from program with 1 level of nesting") {
    unordered_map<string, set<int>> statements = extractStatements(lines2);
    REQUIRE(expectedStatements2 == statements)
}

vector<Line> lines3 = {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"read", "x", ";"}, "read"),
        Line(2, {"while", "(", "x", ">", "0", ")", "{"}, "while"),
        Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
        Line(4, {"read", "z", ";"}, "read"),
        Line(5, {"if", "(", "z", "!=", "0", ")", "{"}, "if"),
        Line(6, {"x", "=", "x", "*", "z", "/", "5", ";"}, "="),
        Line({"}"}, "}"),
        Line({"else", "{"}, "else"),
        Line(7, {"x", "=", "z", "/", "x", "*", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}"}, "}")
};

unordered_map<string, set<int>> expectedStatements3 = {
        {"call", {}},
        { "print", {}},
        { "=", {3, 6, 7}},
        { "if", {5}},
        { "read", {1, 4}},
        { "while", {2}},
};

TEST_CASE("Extract statements from program with 3 level of nesting") {
    unordered_map<string, set<int>> statements = extractStatements(lines3);
    REQUIRE(expectedStatements3 == statements);
}

vector<Line> lines4 = {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
        Line({"procedure", "readPoint", "{"}, "procedure"),
        Line(4, {"read", "x", ";"}, "read"),
        Line(5, {"read", "y", ";"}, "read"),
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
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
};

unordered_map<string, set<int>> expectedStatements4 = {
        {"call", {2, 3, 13, 18}},
        { "print", {6, 7, 8, 9}},
        { "=", {1, 10, 11, 12, 15, 16, 17, 20, 21, 22, 23}},
        { "if", {}},
        { "read", {4, 5}},
        { "while", {14}},
};

TEST_CASE("Extract statements from program with multiple procedures") {
    unordered_map<string, set<int>> statements = extractStatements(lines4);
    REQUIRE(expectedStatements4 == statements);
}

unordered_map<string, set<int>> expectedStatementsSource4 = {
        {"call", {}},
        { "print", {}},
        { "=", {1,2,3,8,9,11,12,13,14}},
        { "if", {6,7,10}},
        { "read", {}},
        { "while", {4,5}},
};

TEST_CASE("test source 4 extractor") {
    bool correct = true;
    unordered_map<string, set<int>> statements = extractStatements(source4);
    for(auto [key, value] : statements) {
        for(int i : value) {
            if(expectedStatementsSource4[key].find(i) == value.end()) {
                correct = false;
            }
        }
    }
    assert(correct);
}
