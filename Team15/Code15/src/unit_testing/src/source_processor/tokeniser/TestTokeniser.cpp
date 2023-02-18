#include "catch.hpp"
#include "source_processor/include/tokeniser/Tokeniser.h"

vector<string> emptyLines = {};
pair<vector<string>, vector<Line>> nonEmptyLines1 = {{
    "procedure test {",
        "x = 1;",
        "y = 2;",
        "read z;",
    "}"
    }, {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"x", "=", "1", ";"}, "="),
        Line(2, {"y", "=", "2", ";"}, "="),
        Line(3, {"read", "z", ";"}, "read"),
        Line({"}"}, "}")
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines2 = {{
    "procedure test {",
        "read x;",
        "if(x > 0) {",
            "x = x + 1;",
        "}",
    "}",
    }, {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"read", "x", ";"}, "read"),
        Line(2, {"if", "(", "x", ">", "0", ")", "{"}, "if"),
        Line(3, {"x", "=", "x", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines3 = {{
        "procedure test {",
            "read x;",
            "while(x > 0) {",
                "x = x + 1;",
                "read z;",
                "if(z != 0) {",
                    "x = x * z / 5;",
                "}",
                "else {",
                    "x = z / x * 4;",
                "}",
            "}",
        "}",
    }, {
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
    }
};

TEST_CASE("Empty lines vector should return empty extracted lines vector") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(emptyLines);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    assert(extractedLines.empty());
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 1, all same nesting level") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines1.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    bool correct = true;
    for(int i = 0; i < extractedLines.size(); i++) {
        if(!(extractedLines[i] == nonEmptyLines1.second[i])) correct = false;
    }
    assert(correct);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 2, 2 nesting levels") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines2.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    bool correct = true;
    for(int i = 0; i < extractedLines.size(); i++) {
        if(!(extractedLines[i] == nonEmptyLines2.second[i])) correct = false;
    }
    assert(correct);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 3, 3 nesting levels") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines3.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    bool correct = true;
    for(int i = 0; i < extractedLines.size(); i++) {
        if(!(extractedLines[i] == nonEmptyLines3.second[i])) correct = false;
    }
    assert(correct);
}
