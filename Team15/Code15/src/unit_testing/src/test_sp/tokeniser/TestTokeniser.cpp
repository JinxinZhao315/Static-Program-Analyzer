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
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"x", "=", "1", ";"}, ASSIGN),
        Line(2, {"y", "=", "2", ";"}, ASSIGN),
        Line(3, {"read", "z", ";"}, READ),
        Line({"}"}, CLOSE_CURLY)
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
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"read", "x", ";"}, READ),
        Line(2, {"if", "(", "x", ">", "0", ")", "{"}, IF),
        Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
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
                "} else {",
                    "x = z / x * 4;",
                "}",
            "}",
        "}",
    }, {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"read", "x", ";"}, READ),
        Line(2, {"while", "(", "x", ">", "0", ")", "{"}, WHILE),
        Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
        Line(4, {"read", "z", ";"}, READ),
        Line(5, {"if", "(", "z", "!=", "0", ")", "{"}, IF),
        Line(6, {"x", "=", "x", "*", "z", "/", "5", ";"}, ASSIGN),
        Line({"}","else", "{"}, ELSE),
        Line(7, {"x", "=", "z", "/", "x", "*", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines4 = {{
    "procedure test {",
        "flag = 0;",
        "call computeCentroid;",
        "call printResults;",
    "}",
    "procedure readPoint {",
        "read x;",
        "read y;",
    "}",
    "procedure printResults {",
        "print flag;",
        "print cenX;",
        "print cenY;",
        "print normSq;",
    "}",
    "procedure computeCentroid {",
        "count = 0;",
        "cenX = 0;",
        "cenY = 0;",
        "call readPoint;",
        "while((x != 0) && (y != 0)) {",
            "count = count + 1;",
            "cenX = cenX + x;",
            "cenY = cenY + y;",
            "call readPoint;",
            "if(count == 0) {",
                "flag = 1;",
            "} else {",
                "cenX = cenX / count;",
                "cenY = cenY / count;",
            "}",
        "normSq = cenX * cenX + cenY * cenY;",
    "}",
    }, {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"flag", "=", "0", ";"}, ASSIGN),
        Line(2, {"call", "computeCentroid", ";"}, CALL),
        Line(3, {"call", "printResults", ";"}, CALL),
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
        Line(13, {"call", "readPoint", ";"}, CALL),
        Line(14, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(15, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(16, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(17, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(18, {"call", "readPoint", ";"}, CALL),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(20, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines5 = {{
    "procedure test {",
        "x = 1;",
        "y = 2;",
        "read z;",
    "}"
    }, {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"x", "=", "1", ";"}, ASSIGN),
        Line(2, {"y", "=", "2", ";"}, ASSIGN),
        Line(3, {"read", "z", ";"}, READ),
        Line({"}"}, CLOSE_CURLY)
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines6 = {{
    "procedure test {",
        "printX = 1;",
        "callY = 2;",
        "read readZ;",
    "}"
    }, {
        Line({"procedure", "test", "{"}, PROCEDURE),
        Line(1, {"printX", "=", "1", ";"}, ASSIGN),
        Line(2, {"callY", "=", "2", ";"}, ASSIGN),
        Line(3, {"read", "readZ", ";"}, READ),
        Line({"}"}, CLOSE_CURLY)
    }
};

TEST_CASE("Empty lines vector should return empty extracted lines vector") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(emptyLines);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(extractedLines.empty());
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 1, all same nesting level") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines1.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines1.second == extractedLines);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 2, 2 nesting levels") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines2.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines2.second == extractedLines);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 3, 3 nesting levels") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines3.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines3.second == extractedLines);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 4, multiple procedures") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines4.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines4.second == extractedLines);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 5, procedure name contains keyword") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines5.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines5.second == extractedLines);
}

TEST_CASE("Non-empty lines vector should return non-empty extracted line vector 6, variable name contains keyword") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(nonEmptyLines6.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(nonEmptyLines6.second == extractedLines);
}

pair<vector<string>, vector<Line>> source4_tok = {{
    "procedure proc1 {",
    "a = 0;",
    "b = 100;",
    "c = 50;",
    "while (a < 50) {",
    "while (b > 1) {",
    "if (a > 25) then {",
    "if (b < 50) then {",
    "b = b / 2;",
    "a = a + 5;",
    "} else {",
    "if (b < 75) then {",
    "b = b / 3;",
    "} else {",
    "b = b / 4;",
    "}",
    "}",
    "} else {",
    "a = a * 2;",
    "}",
    "}",
    "a = a + 1;",
    "}",
    "}",
    }, {
        Line({"procedure", "proc1", "{"}, PROCEDURE),
        Line(1, {"a", "=", "0", ";"}, ASSIGN),
        Line(2, {"b", "=", "100", ";"}, ASSIGN),
        Line(3, {"c", "=", "50", ";"}, ASSIGN),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, WHILE),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, WHILE),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, IF),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, IF),
        Line(8, {"b", "=", "b", "/", "2", ";"}, ASSIGN),
        Line(9, {"a", "=", "a", "+", "5", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, IF),
        Line(11, {"b", "=", "b", "/", "3", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(12, {"b", "=", "b", "/", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}", "else", "{"}, ELSE),
        Line(13, {"a", "=", "a", "*", "2", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line(14, {"a", "=", "a", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
}
};

TEST_CASE("test source 4 tokeniser") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(source4_tok.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(source4_tok.second == extractedLines);
}
