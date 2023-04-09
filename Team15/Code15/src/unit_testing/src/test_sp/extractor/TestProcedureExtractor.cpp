#include "catch.hpp"
#include "Constants.hpp"
#include "sp/include/extractor/ProcedureExtractor.h"

TEST_CASE("extract procedures from mainProgram") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(mainProgram);
	set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "main" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from onlyCallStatements") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(onlyCallStatements);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "main" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from singleAssignmentSelfIncrement") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(singleAssignmentSelfIncrement);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from singleAssignmentAddVariable") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(singleAssignmentAddVariable);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from whileLoop") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(whileLoop);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from whileLoop2") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(whileLoop2);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from computeCentroid") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(computeCentroid);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "computeCentroid" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from ifElse") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(ifElse);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from ifElse2") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(ifElse2);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected;
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from superNested") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(superNested);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "proc1" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from readPoint") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(readPoint);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "readPoint" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from program") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(program);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "computeCentroid", "main", "printResults", "readPoint" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from source2") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(source2);
    set<string> results = procedureExtractor->getProcedures();
	set<string> expected = { "proc1", "proc2" };
	REQUIRE(results == expected);
}

TEST_CASE("extract procedures from source4") {
    ProcedureExtractor* procedureExtractor = new ProcedureExtractor();
    procedureExtractor->extractProcedures(source4);
    set<string> results = procedureExtractor->getProcedures();
    set<string> expected = { "proc1" };
    REQUIRE(results == expected);
}
