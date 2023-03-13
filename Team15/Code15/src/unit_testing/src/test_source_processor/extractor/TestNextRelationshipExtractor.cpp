//              procedure Second {
//        01        x = 0;
//        02        i = 5;
//        03        while (i!=0) {
//        04            x = x + 2*y;
//        05            call Third;
//        06            i = i - 1; }
//        07        if (x==1) then {
//        08            x = x+1; }
//                  else {
//        09            z = 1; }
//        10        z = z + x + i;
//        11        y = z + 2;
//        12        x = x * y + z; }

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
    unordered_map<int, set<int>> expectedNext = {{1,{2, 4}}, {2,{3}}, {3, {4}}};
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
    unordered_map<int, set<int>> expectedNext = {{1,{2, 4}}, {2,{3}}, {3, {4}}};
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_singleIfWithElseNoWhile") {
    const vector<Line>& lines =  {
            Line({"procedure", "test", "{"}, "procedure"),
            Line(1, {"x", "=", "1", ";"}, "="),
            Line(2, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
            Line(3, {"c", "=", "c",  "-",  "1", ";", "}"}, "="),
            Line({"else", "{"}, "else"),
            Line(4, {"c", "=", "c",  "-",  "1"}, "="),
            Line({"}"}, "}"),
            Line(5, {"read", "z", ";"}, "read"),
            Line({"}"}, "}")
    };

    // shouldn't have 3, 4 should have 1, 4
    auto extractedNext = extractNextRS(lines);
    unordered_map<int, set<int>> expectedNext = {{1 , {2, 4}}, {2, {3}}, {4, {5}}};
    REQUIRE(extractedNext == expectedNext);
}
