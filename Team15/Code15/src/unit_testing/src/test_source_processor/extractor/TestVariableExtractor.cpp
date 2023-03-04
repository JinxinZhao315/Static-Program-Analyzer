#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/VariableExtractor.h"

VariableExtractor* variableExtractor = new VariableExtractor();

TEST_CASE("extract variables from mainProgram") {
	set<string> results = variableExtractor->extractVariables(mainProgram);
	set<string> expected = { "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from onlyCallStatements") {
	set<string> results = variableExtractor->extractVariables(onlyCallStatements);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentSelfIncrement") {
	set<string> results = variableExtractor->extractVariables(singleAssignmentSelfIncrement);
	set<string> expected = { "count" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentAddVariable") {

	set<string> results = variableExtractor->extractVariables(singleAssignmentAddVariable);
	set<string> expected = { "cenX", "x" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop") {
	set<string> results = variableExtractor->extractVariables(whileLoop);
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop2") {
	set<string> results = variableExtractor->extractVariables(whileLoop2);
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from computeCentroid") {
	set<string> results = variableExtractor->extractVariables(computeCentroid);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse") {
	set<string> results = variableExtractor->extractVariables(ifElse);
	set<string> expected = { "cenX", "cenY", "count", "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse2") {
	set<string> results = variableExtractor->extractVariables(ifElse2);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from superNested") {
	set<string> results = variableExtractor->extractVariables(superNested);
	set<string> expected = { "a", "b", "c" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from readPoint") {
	set<string> results = variableExtractor->extractVariables(readPoint);
	set<string> expected = { "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from program") {
	set<string> results = variableExtractor->extractVariables(program);
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from source2") {
	set<string> results = variableExtractor->extractVariables(source2);
	set<string> expected = { "a", "b", "c", "count", "d", "e", "f", "v", "w", "x", "y", "z" };
	REQUIRE(results == expected);
}

TEST_CASE("extract undeclared variables") {
    set<string> results = variableExtractor->extractVariables(source6);
    set<string> expected = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s"};
    REQUIRE(results == expected);
}