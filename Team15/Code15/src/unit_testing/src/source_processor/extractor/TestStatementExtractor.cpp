#include "catch.hpp"
#include "source_processor/include/extractor/StatementExtractor.h";

using namespace std;

vector<Line> lines = {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"x", "=", "1", ";"}, "="),
        Line(2, {"y", "=", "2", ";"}, "="),
        Line(3, {"read", "z", ";"}, "read"),
        Line({"}"}, "}")
};

unordered_map<string, set<int>> expectedStatements = {
        {"call", {}},
        { "print", {}},
        { "=", {1, 2}},
        { "if", {}},
        { "read", {3}},
        { "while", {}},
};

TEST_CASE("Extract statements from program with no nesting") {
    bool correct = true;
    unordered_map<string, set<int>> statements = extractStatements(lines);
    for(auto [key, value] : statements) {
        for(int i : value) {
            if(expectedStatements[key].find(i) == value.end()) {
                correct = false;
            }
        }
    }
    assert(correct);
}