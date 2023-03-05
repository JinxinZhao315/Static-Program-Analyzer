#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

// Test calls
TEST_CASE("extractCalls_noCalls") {
    auto result = extractModifiesUsesAndCallRS(source4, source4Variables).callsRS;
    unordered_map<string, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_oneCalls") {
    auto result = extractModifiesUsesAndCallRS(source2, source2Variables).callsRS;
    unordered_map<string, set<string>> expected = {
            {"proc1", {"proc2"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_manyCalls") {
    auto result = extractModifiesUsesAndCallRS(onlyCallStatements, onlyCallStatementsVariables).callsRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"computeCentroid", "printResults"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_manyCallsManyProcedures") {
    auto result = extractModifiesUsesAndCallRS(program, programVariables).callsRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"computeCentroid", "printResults"}},
            {"computeCentroid", {"readPoint"}}
    };
    REQUIRE(result == expected);
}

// Test callsStar
TEST_CASE("extractCalls_noCallsStar") {
    auto result = extractModifiesUsesAndCallRS(source4, source4Variables).callsStarRS;
    unordered_map<string, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_oneCallsStar") {
    auto result = extractModifiesUsesAndCallRS(source2, source2Variables).callsStarRS;
    unordered_map<string, set<string>> expected = {
            {"proc1", {"proc2"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_manyCallsStar") {
    auto result = extractModifiesUsesAndCallRS(onlyCallStatements, onlyCallStatementsVariables).callsStarRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"computeCentroid", "printResults"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractCalls_manyCallsStarManyProcedures") {
    auto result = extractModifiesUsesAndCallRS(program, programVariables).callsStarRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"computeCentroid", "printResults", "readPoint"}},
            {"computeCentroid", {"readPoint"}}
    };
    REQUIRE(result == expected);
}