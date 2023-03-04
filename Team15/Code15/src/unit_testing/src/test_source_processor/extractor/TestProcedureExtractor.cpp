#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ProcedureExtractor.h"

TEST_CASE("extract procedures from mainProgram") {
	set<string> results = extractProcedures(mainProgram);
	set<string> expected = { "main" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from onlyCallStatements") {
	set<string> results = extractProcedures(onlyCallStatements);
	set<string> expected = { "main" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from singleAssignmentSelfIncrement") {
	set<string> results = extractProcedures(singleAssignmentSelfIncrement);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from singleAssignmentAddVariable") {
	set<string> results = extractProcedures(singleAssignmentAddVariable);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from whileLoop") {
	set<string> results = extractProcedures(whileLoop);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from whileLoop2") {
	set<string> results = extractProcedures(whileLoop2);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from computeCentroid") {
	set<string> results = extractProcedures(computeCentroid);
	set<string> expected = { "computeCentroid" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from ifElse") {
	set<string> results = extractProcedures(ifElse);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from ifElse2") {
	set<string> results = extractProcedures(ifElse2);
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from superNested") {
	set<string> results = extractProcedures(superNested);
	set<string> expected = { "proc1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from readPoint") {
	set<string> results = extractProcedures(readPoint);
	set<string> expected = { "readPoint" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from program") {
	set<string> results = extractProcedures(program);
	set<string> expected = { "computeCentroid", "main", "printResults", "readPoint" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from source2") {
	set<string> results = extractProcedures(source2);
	set<string> expected = { "proc1", "proc2" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from source4") {
    set<string> results = extractProcedures(source4);
    set<string> expected = { "proc1" };
    REQUIRE(results == expected);
}
