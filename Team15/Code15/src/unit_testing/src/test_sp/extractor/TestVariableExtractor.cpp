#include "catch.hpp"
#include "Constants.hpp"
#include "sp/include/extractor/VariableExtractor.h"


TEST_CASE("extract variables from mainProgram") {
    VariableExtractor* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(mainProgram);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from onlyCallStatements") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(onlyCallStatements);
    set<string> results = variableExtractor->getVariables();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentSelfIncrement") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(singleAssignmentSelfIncrement);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "count" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from singleAssignmentAddVariable") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(singleAssignmentAddVariable);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "x" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(whileLoop);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from whileLoop2") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(whileLoop2);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from computeCentroid") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(computeCentroid);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(ifElse);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "flag" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from ifElse2") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(ifElse2);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from superNested") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(superNested);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "a", "b", "c" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from readPoint") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(readPoint);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from program") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(program);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "cenX", "cenY", "count", "flag", "normSq", "x", "y" };
	REQUIRE(results == expected);
}

TEST_CASE("extract variables from source2") {
    auto* variableExtractor = new VariableExtractor();
	variableExtractor->extractVariables(source2);
    set<string> results = variableExtractor->getVariables();
	set<string> expected = { "a", "b", "c", "count", "d", "e", "f", "v", "w", "x", "y", "z" };
	REQUIRE(results == expected);
}

TEST_CASE("extract undeclared variables") {
    auto* variableExtractor = new VariableExtractor();
    variableExtractor->extractVariables(source6);
    set<string> results = variableExtractor->getVariables();
    set<string> expected = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s"};
    REQUIRE(results == expected);
}