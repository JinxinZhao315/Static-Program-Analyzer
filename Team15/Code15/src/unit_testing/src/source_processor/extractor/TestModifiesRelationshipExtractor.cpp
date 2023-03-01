#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

// Test modifiesS
TEST_CASE("extractModifiesUsesAndCallRS_noModifications") {
    auto result = extractModifiesUsesAndCallRS(onlyCallStatements, onlyCallStatementsVariables).modifiesRS;
    unordered_map<int, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_oneAssignment") {
    auto result = extractModifiesUsesAndCallRS(singleAssignmentSelfIncrement, singleAssignmentSelfIncrementVariables).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {6, {"count"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_manyAssignments") {
    auto result = extractModifiesUsesAndCallRS(whileLoop, whileLoopVariables).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {5, {"count", "cenX", "cenY"}},
            {6, {"count"}},
            {7, {"cenX"}},
            {8, {"cenY"}},
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_complicatedProgram") {
    auto result = extractModifiesUsesAndCallRS(computeCentroid, computeCentroidVariables).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {1, {"count"}},
            {2, {"cenX"}},
            {3, {"cenY"}},
            {5, {"count", "cenX", "cenY"}},
            {6, {"count"}},
            {7, {"cenX"}},
            {8, {"cenY"}},
            {10, {"flag", "cenX", "cenY"}},
            {11, {"flag"}},
            {12, {"cenX"}},
            {13, {"cenY"}},
            {14, {"normSq"}}
    };
    REQUIRE(result == expected);
}


TEST_CASE("extractModifiesUsesAndCallRS_twoReadStatements") {
    auto result = extractModifiesUsesAndCallRS(readPoint, readPointVariables).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {4, {"x"}},
            {5, {"y"}},
    };
    REQUIRE(result == expected);
}

// Test modifiesP
TEST_CASE("extractModifiesUsesAndCallRS_manyModifies") {
    auto result = extractModifiesUsesAndCallRS(computeCentroid, computeCentroidVariables).procedureModifiesRS;
    unordered_map<string, set<string>> expected = {
            {"computeCentroid", {"count", "cenX", "cenY", "flag", "normSq"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_manyModifiesWithNesting") {
    auto result = extractModifiesUsesAndCallRS(superNested, superNestedVariables).procedureModifiesRS;
    unordered_map<string, set<string>> expected = {
            {"proc1", {"a", "b", "c"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_manyProcedureManyModifiesWithNesting") {
    auto result = extractModifiesUsesAndCallRS(program, programVariables).procedureModifiesRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"count", "cenX", "cenY", "flag", "normSq", "x", "y"}},
            {"readPoint", {"x", "y"}},
            {"computeCentroid", {"count", "cenX", "cenY", "flag", "normSq", "x", "y"}}
    };
    REQUIRE(result == expected);
}