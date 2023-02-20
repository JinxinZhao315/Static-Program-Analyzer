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
                "} else {",
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
        Line({"}","else", "{"}, "else"),
        Line(7, {"x", "=", "z", "/", "x", "*", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}"}, "}")
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
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
    }
};

pair<vector<string>, vector<Line>> nonEmptyLines5 = {{
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

pair<vector<string>, vector<Line>> nonEmptyLines6 = {{
    "procedure test {",
        "printX = 1;",
        "callY = 2;",
        "read readZ;",
    "}"
    }, {
        Line({"procedure", "test", "{"}, "procedure"),
        Line(1, {"printX", "=", "1", ";"}, "="),
        Line(2, {"callY", "=", "2", ";"}, "="),
        Line(3, {"read", "readZ", ";"}, "read"),
        Line({"}"}, "}")
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

<<<<<<< HEAD
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
        Line({"procedure", "proc1", "{"}, "procedure"),
        Line(1, {"a", "=", "0", ";"}, "="),
        Line(2, {"b", "=", "100", ";"}, "="),
        Line(3, {"c", "=", "50", ";"}, "="),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, "while"),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, "while"),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, "if"),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, "if"),
        Line(8, {"b", "=", "b", "/", "2", ";"}, "="),
        Line(9, {"a", "=", "a", "+", "5", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, "if"),
        Line(11, {"b", "=", "b", "/", "3", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(12, {"b", "=", "b", "/", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}", "else", "{"}, "else"),
        Line(13, {"a", "=", "a", "*", "2", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line(14, {"a", "=", "a", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
}
};

TEST_CASE("test source 4") {
    Tokeniser* tokeniser = new Tokeniser();
    tokeniser->feedLines(source4_tok.first);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    REQUIRE(source4_tok.second == extractedLines);
}
=======
//pair<vector<string>, vector<Line>> source4 = {{
//    "procedure proc1 {",
//    "a = 0;",
//    "b = 100;",
//    "c = 50;",
//    "while (a < 50) {",
//    "while (b > 1) {",
//    "if (a > 25) then {",
//    "if (b < 50) then {",
//    "b = b / 2;",
//    "a = a + 5;",
//    "} else {",
//    "if (b < 75) then {",
//    "b = b / 3;",
//    "} else {",
//    "b = b / 4;",
//    "}",
//    "}",
//    "} else {",
//    "a = a * 2;",
//    "}",
//    "}",
//    "a = a + 1;",
//    "}",
//    "}",
//    }, {
//        Line({"procedure", "proc1", "{"}, "procedure"),
//        Line(1, {"a", "=", "0", ";"}, "="),
//        Line(2, {"b", "=", "100", ";"}, "="),
//        Line(3, {"c", "=", "50", ";"}, "="),
//        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, "while"),
//        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, "while"),
//        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, "if"),
//        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, "if"),
//        Line(8, {"b", "=", "b", "/", "2", ";"}, "="),
//        Line(9, {"a", "=", "a", "+", "5", ";"}, "="),
//        Line({"}", "else", "{"}, "else"),
//        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, "if"),
//        Line(11, {"b", "=", "b", "/", "3", ";"}, "="),
//        Line({"}", "else", "{"}, "else"),
//        Line(12, {"b", "=", "b", "/", "4", ";"}, "="),
//        Line({"}"}, "}"),
//        Line({"}"}, "}"),
//        Line({"}", "else", "{"}, "else"),
//        Line(13, {"a", "=", "a", "*", "2", ";"}, "="),
//        Line({"}"}, "}"),
//        Line({"}"}, "}"),
//        Line(14, {"a", "=", "a", "+", "1", ";"}, "="),
//        Line({"}"}, "}"),
//        Line({"}"}, "}")
//}
//};

//TEST_CASE("source 4") {
//    Tokeniser* tokeniser = new Tokeniser();
//    tokeniser->feedLines(source4.first);
//    vector<Line> extractedLines = tokeniser->getExtractedLines();
//    REQUIRE(source4.second == extractedLines);
//}
>>>>>>> e42032e (change asserts to require in tests)
