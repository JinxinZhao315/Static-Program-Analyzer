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

TEST_CASE("extractAssignmentRS_oneAssignmentSelfIncrement") {
    set<string> variables = {"count"};
    auto result = extractAssignmentRS(singleAssignmentSelfIncrement, variables);
    unordered_map<string, set<Line>> expected = {
            {"count", {Line(6, {"count","1","+"})}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractAssignmentRS_oneAssignmentAddVariable") {
    set<string> variables = {"cenX", "x"};
    auto result = extractAssignmentRS(singleAssignmentAddVariable, variables);
    unordered_map<string, set<Line>> expected = {
            {"cenX", {Line(7, {"cenX","x","+"})}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractAssignmentRS_manyAssignmentsWhileLoop") {
    set<string> variables = {"count", "cenX", "cenY", "x", "y"};
    auto result = extractAssignmentRS(whileLoop, variables);
    unordered_map<string, set<Line>> expected = {
        {"count", {Line(6, {"count", "1", "+"})}},
        {"cenX", {Line(7, {"cenX", "x", "+"})}},
        {"cenY", {Line(8, {"cenY", "y", "+"})}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractAssignmentRS_manyAssignmentsIfAndWhileLoop") {
    set<string> variables = {"count", "cenX", "cenY", "x", "y", "flag", "normSq"};
    auto result = extractAssignmentRS(computeCentroid, variables);
    unordered_map<string, set<Line>> expected = {
            {"count", { Line(1, {"0"}), Line(6, {"count", "1", "+"}) }},
            {"cenX", { Line(2, {"0"}), Line(7, {"cenX", "x", "+"}), Line(12, {"cenX", "count", "/"}) }},
            {"cenY", { Line(3, {"0"}), Line(8, {"cenY", "y", "+"}), Line(13, {"cenY", "count", "/"}) }},
            {"flag", { Line(11, {"1"}) }},
            {"normSq", { Line(14, {"cenX", "cenX", "*", "cenY", "cenY", "*", "+"}) }},
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractAssignmentRS_source4") {
    set<string> variables = {"a", "b", "c"};
    auto result = extractAssignmentRS(source4, variables);
    unordered_map<string, set<Line>> expected = {
            {"a", { Line(1, {"0"}), Line(9, {"a", "5", "+"}), Line(13, {"a", "2", "*"}), Line(14, {"a", "1", "+"}) }},
            {"b", { Line(2, {"100"}), Line(8, {"b", "2", "/"}), Line(11, {"b", "3", "/"}), Line(12, {"b", "4", "/"}) }},
            {"c", { Line(3, {"50"})}}
    };
    REQUIRE(result == expected);
}