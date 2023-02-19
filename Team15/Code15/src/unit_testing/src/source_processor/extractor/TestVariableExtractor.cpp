#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/VariableExtractor.h"

TEST_CASE("extract variables from mainProgram") {
	set<string> results = extractVariables(mainProgram);
	set<string> expected = { "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from onlyCallStatements") {
	set<string> results = extractVariables(onlyCallStatements);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentSelfIncrement") {
	set<string> results = extractVariables(singleAssignmentSelfIncrement);
	set<string> expected = { "count" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentAddVariable") {
	set<string> results = extractVariables(singleAssignmentAddVariable);
	set<string> expected = { "cenX", "x" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop") {
	set<string> results = extractVariables(whileLoop);
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop2") {
	set<string> results = extractVariables(whileLoop2);
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from computeCentroid") {
	set<string> results = extractVariables(computeCentroid);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse") {
	set<string> results = extractVariables(ifElse);
	set<string> expected = { "cenX", "cenY", "count", "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse2") {
	set<string> results = extractVariables(ifElse2);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from superNested") {
	set<string> results = extractVariables(superNested);
	set<string> expected = { "a", "b", "c" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from readPoint") {
	set<string> results = extractVariables(readPoint);
	set<string> expected = { "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from program") {
	set<string> results = extractVariables(program);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from source2") {
	set<string> results = extractVariables(source2);
	set<string> expected = { "a", "b", "c", "count", "d", "e", "f", "v", "w", "x", "y", "z" };
	REQUIRE(results == expected);
}
