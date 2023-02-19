#include "catch.hpp"
#include "source_processor/include/extractor/StatementExtractor.h";

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
    bool correct = true;
    unordered_map<string, set<int>> statements = extractStatements(lines1);
    for(auto [key, value] : statements) {
        for(int i : value) {
            if(expectedStatements1[key].find(i) == value.end()) {
                correct = false;
            }
        }
    }
    assert(correct);
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
    bool correct = true;
    unordered_map<string, set<int>> statements = extractStatements(lines2);
    for(auto [key, value] : statements) {
        for(int i : value) {
            if(expectedStatements2[key].find(i) == value.end()) {
                correct = false;
            }
        }
    }
    assert(correct);
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
    bool correct = true;
    unordered_map<string, set<int>> statements = extractStatements(lines3);
    for(auto [key, value] : statements) {
        for(int i : value) {
            if(expectedStatements3[key].find(i) == value.end()) {
                correct = false;
            }
        }
    }
    assert(correct);
}
