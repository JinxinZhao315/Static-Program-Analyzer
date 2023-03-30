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

TEST_CASE("extractModifiesUsesAndCallRS_twoProceduresCallModifiesVarInIfStmtContainer") {
    const vector<Line> lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"if", "(", "y", "==", "0", ")", "{"}, IF),
            Line(2, {"call", "B", ";"}, CALL),
            Line({"}", "else", "{"}, ELSE),
            Line(3, {"z", "=", "z", "/", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"read", "x", ";"}, READ),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> vars = {"x", "y", "z"};
    auto result = extractModifiesUsesAndCallRS(lines, vars).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {1, {"x", "z"}},
            {2, {"x"}},
            {3, {"z"}},
            {4, {"x"}}
    };
    REQUIRE(result == expected);
}

TEST_CASE("extractModifiesUsesAndCallRS_twoProceduresCallModifiesVarInWhileStmtContainer") {
    const vector<Line> lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"while", "(", "y", "==", "0", ")", "{"}, WHILE),
            Line(2, {"z", "=", "z", "/", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(3, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"while", "(", "y", "==", "0", ")", "{"}, WHILE),
            Line(5, {"read", "x", ";"}, READ),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> vars = {"x", "y", "z"};
    auto result = extractModifiesUsesAndCallRS(lines, vars).modifiesRS;
    unordered_map<int, set<string>> expected = {
            {1, {"x", "z"}},
            {2, {"z"}},
            {3, {"x"}},
            {4, {"x"}},
            {5, {"x"}}
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