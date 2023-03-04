#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

// Test UsesS
TEST_CASE("extractUses_noUsesInAllCalls") {
    auto result = extractModifiesUsesAndCallRS(onlyCallStatements, onlyCallStatementsVariables).usesRS;
    unordered_map<int, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_noUsesInAssignment") {
    auto result = extractModifiesUsesAndCallRS(mainProgram, mainProgramVariables).usesRS;
    unordered_map<int, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_singleUsesSingleVar") {
    auto result = extractModifiesUsesAndCallRS(singleAssignmentSelfIncrement, singleAssignmentSelfIncrementVariables).usesRS;
    unordered_map<int, set<string>> expected = {
            {6, {"count"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_singleUsesTwoVar") {
    auto result = extractModifiesUsesAndCallRS(singleAssignmentAddVariable, singleAssignmentAddVariableVariables).usesRS;
    unordered_map<int, set<string>> expected = {
            {7, {"cenX", "x"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_ifElse") {
    auto result = extractModifiesUsesAndCallRS(ifElse, ifElseVariables).usesRS;
    unordered_map<int, set<string>> expected = {
            {19, {"count", "cenX", "cenY"}},
            {21, {"cenX", "count"}},
            {22, {"cenY", "count"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_ifElseStmtBeforeAndAfter") {
    auto result = extractModifiesUsesAndCallRS(ifElse2, ifElse2Variables).usesRS;
    unordered_map<int, set<string>> expected = {
            {19, {"count", "cenX", "cenY"}},
            {21, {"cenX", "count"}},
            {22, {"cenY", "count"}},
            {23, {"cenX", "cenY"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_while") {
    auto result = extractModifiesUsesAndCallRS(whileLoop, whileLoopVariables).usesRS;
    unordered_map<int, set<string>> expected = {
            {5, {"x", "y", "count", "cenX", "cenY"}},
            {6, {"count"}},
            {7, {"cenX", "x"}},
            {8, {"cenY", "y"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_whileStmtBeforeAndAfter") {
    auto result = extractModifiesUsesAndCallRS(whileLoop2, whileLoop2Variables).usesRS;
    unordered_map<int, set<string>> expected = {
            {5, {"x", "y", "count", "cenX", "cenY"}},
            {6, {"count"}},
            {7, {"cenX", "x"}},
            {8, {"cenY", "y"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_complexProcedure") {
    auto result = extractModifiesUsesAndCallRS(computeCentroid, computeCentroidVariables).usesRS;
    unordered_map<int, set<string>> expected = {
            {5, {"x", "y", "count", "cenX", "cenY"}},
            {6, {"count"}},
            {7, {"cenX", "x"}},
            {8, {"cenY", "y"}},
            {10, {"count", "cenX", "cenY"}},
            {12, {"cenX", "count"}},
            {13, {"cenY", "count"}},
            {14,{"cenX", "cenY"}}
    };
    REQUIRE(result == expected);
}

// Test UsesP
TEST_CASE("extractUses_oneProcedureNoUses") {
    auto result = extractModifiesUsesAndCallRS(mainProgram, mainProgramVariables).procedureUsesRS;
    unordered_map<string, set<string>> expected;
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_oneProcedureManyUses") {
    auto result = extractModifiesUsesAndCallRS(computeCentroid, computeCentroidVariables).procedureUsesRS;
    unordered_map<string, set<string>> expected = {
            {"computeCentroid", {"x", "y", "count", "cenX", "cenY"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractUses_manyProcedureManyUses") {
    auto result = extractModifiesUsesAndCallRS(program, programVariables).procedureUsesRS;
    unordered_map<string, set<string>> expected = {
            {"main", {"x", "y", "count", "cenX", "cenY", "flag", "normSq"}},
            {"printResults", {"flag", "cenX", "cenY", "normSq"}},
            {"computeCentroid", {"x", "y", "count", "cenX", "cenY"}}
    };
    REQUIRE(result == expected);
}
