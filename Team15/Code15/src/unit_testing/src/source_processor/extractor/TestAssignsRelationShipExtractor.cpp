#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/AssignsRelationshipExtractor.h"

TEST_CASE("extractAssignmentRS_noAssignments") {
    set<string> variables;
    auto result = extractAssignmentRS(readPoint, variables);
    unordered_map<string, set<Line>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractAssignmentRS_oneAssignment") {
    set<string> variables = {"flag"};
    auto result = extractAssignmentRS(mainProgram, variables);
    unordered_map<string, set<Line>> expected = {
            {"flag", {Line(1, {"0"})}}
    };
    REQUIRE(result == expected);
}

//TEST_CASE("extractAssignmentRS_manyAssignmentsWhileLoop") {
//    set<string> variables = {"count", "cenX", "cenY"};
//    auto result = extractAssignmentRS(whileLoop, variables);
//    unordered_map<string, set<Line>> expected = {
//        {"count", {Line(6, {"count", "1" "+"})}},
//        {"cenX", {Line(7, {"cenX", "x", "+"})}},
//        {"cenY", {Line(8, {"cenY", "y", "+"})}}
//    };
//    REQUIRE(result == expected);
//}