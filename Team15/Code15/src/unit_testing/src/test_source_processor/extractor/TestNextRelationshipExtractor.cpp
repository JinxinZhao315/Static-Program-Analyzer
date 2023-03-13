#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/NextRelationshipExtractor.h"

TEST_CASE("extractNextRelationship_noIfNoWhile") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"y", "=", "2", ";"}, "="),
            Line(3, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_noIfSingleWhile") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(3, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line(4, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 4}}, {3, {4}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_singleIfNoElseNoWhile") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line(4, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 4}}, {3, {4}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_singleIfWithElseNoWhile") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"c", "=", "c",  "-",  "1", ";", "}"}, "="),
            Line({"else", "{"}, "else"),
            Line(4, {"c", "=", "c",  "-",  "1", ";", "}"}, "="),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 4}}, {3, {4}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedWhiles") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(3, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(4, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 5}}, {3, {4, 5}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedIfsNoElse") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(4, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 5}}, {3, {4, 5}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedWhileInIfNoElse") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(4, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 5}}, {3, {4, 5}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedIfInWhileNoElse") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(3, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(4, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line({"}"}, "}"),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 5}}, {3, {4, 5}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedWhileInIfWithElse") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"while", "(", "c", ">", "25", ")", "then", "{"}, "while"),
            Line(4, {"c", "=", "c",  "-",  "1", ";", "}"}, "="),
            Line({"}"}, "}"),
            Line({"else", "{"}, "else"),
            Line(5, {"c", "=", "c",  "-",  "1", ";", "}"}, "="),
            Line(6, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1,{2}}, {2,{3, 5}}, {3, {4, 6}}, {4, {6}}, {5, {6}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_nestedIfInWhileWithElse") {

}
