#include "source_processor/include/extractor/CommonExtractorHeader.h"

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