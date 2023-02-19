#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ConstantExtractor.h"

TEST_CASE("extract constants from mainProgram") {
	set<string> results = extractConstants(mainProgram);
	set<string> expected = { "0" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from onlyCallStatements") {
	set<string> results = extractConstants(onlyCallStatements);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from singleAssignmentSelfIncrement") {
	set<string> results = extractConstants(singleAssignmentSelfIncrement);
	set<string> expected = { "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from singleAssignmentAddVariable") {
	set<string> results = extractConstants(singleAssignmentAddVariable);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from whileLoop") {
	set<string> results = extractConstants(whileLoop);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from whileLoop2") {
	set<string> results = extractConstants(whileLoop2);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from computeCentroid") {
	set<string> results = extractConstants(computeCentroid);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from ifElse") {
	set<string> results = extractConstants(ifElse);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from ifElse2") {
	set<string> results = extractConstants(ifElse2);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from superNested") {
	set<string> results = extractConstants(superNested);
	set<string> expected = {"0", "1", "2", "3", "4", "5", "25", "50", "75", "100"};
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from readPoint") {
	set<string> results = extractConstants(readPoint);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from program") {
	set<string> results = extractConstants(program);
	set<string> expected = { "0", "1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract constants from source2") {
	set<string> results = extractConstants(source2);
	set<string> expected = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	REQUIRE(results == expected);
}
