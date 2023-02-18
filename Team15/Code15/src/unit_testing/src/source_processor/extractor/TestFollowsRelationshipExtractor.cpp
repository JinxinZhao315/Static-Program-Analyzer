#include "catch.hpp"
//#include "source_processor/include/parser/Parser.h"
//#include "source_processor/include/tokeniser/tokeniser.h"
#include "source_processor/include/extractor/extractor.h"
#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

vector<Line> mainProgram = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
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
//    REQUIRE(result2 == expectedFollowsStar);
}
//TEST_CASE("parseProgram_emptyString_shouldReturnEmptyString") {
//    Parser parser;
//    Extractor extractor;
//    Tokeniser tokeniser;
//
//    parser.parseProgram(sourceProgram);
//    auto parsedProg = parser.getParsedProgram();

//    auto tokenisedProg = tokeniser.tokenise(parsedProgram);
//    extractor.extractEntities(tokenisedProg);
//    tokeniser->feedLines(fileName);
//    vector<Line> extractedLines = tokeniser->getExtractedLines();
//}