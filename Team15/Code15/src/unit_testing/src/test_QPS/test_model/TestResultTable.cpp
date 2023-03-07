#include "QPS/include/model/ResultTable.h"

#include "catch.hpp"

ResultTable resultTableGenerator(int sampleNum) {
	ResultTable resultTable = ResultTable();
	if (sampleNum == 1) {
		std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
		};
		std::vector<std::string> synList = { "a1", "a2", "a3" };
		return ResultTable(tempTable, synList);
	}
	else if (sampleNum == 2) {
		std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
		};
		std::vector<std::string> synList = { "a1", "a2" };
		return ResultTable(tempTable, synList);
	}
	else if (sampleNum == 3) {
		std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
		};
		std::vector<std::string> synList = { "b1", "b2" };
		return ResultTable(tempTable, synList);
	}
	else if (sampleNum == 4) {
		std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
		};
		std::vector<std::string> synList = { "a1", "b1" };
		return ResultTable(tempTable, synList);
	}
	else if (sampleNum == 5) {
		std::vector<std::vector<std::string>> tempTable = {
			{"2", "2", "2", "2"},
			{"5", "6", "7", "8"}
		};
		std::vector<std::string> synList = { "a1", "b1" };
		return ResultTable(tempTable, synList);
	}
	return resultTable;
}

TEST_CASE("Test resultTable constructor 1") {
	ResultTable resultTable = ResultTable();
	REQUIRE(resultTable.getRowNum() == 0);
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.isTableEmpty() == true);

}

TEST_CASE("Test resultTable constructor 2") {
	std::vector<std::string> synList = { "a1", "a2" };
	ResultTable resultTable = ResultTable(synList);
	REQUIRE(resultTable.getRowNum() == 2);
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.isTableEmpty() == true);
}

TEST_CASE("Test resultTable constructor 3") {
	std::vector<std::string> synResult = { "1", "2", "3"};
	std::string synName = "a1";
	ResultTable resultTable = ResultTable(synResult, synName);
	REQUIRE(resultTable.getRowNum() == 1);
	REQUIRE(resultTable.getColNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == false);

}

TEST_CASE("Test resultTable constructor 4") {
	std::vector<std::vector<std::string>> tempResultTable = { { "1", "2", "3" }, {"4", "5", "6"}};
	std::vector<std::string> synList = { "a1", "a2" };
	ResultTable resultTable = ResultTable(tempResultTable, synList);
	REQUIRE(resultTable.getRowNum() == 2);
	REQUIRE(resultTable.getColNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == false);

}

TEST_CASE("Test getTuple") {
	ResultTable resultTable = resultTableGenerator(1);
	std::vector<std::string> resultTuple = resultTable.getTuple(0);
	std::vector<std::string> expectedResult = {"1", "5", "9"};
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}

TEST_CASE("Test mergeTuple") {
	ResultTable resultTable;
	std::vector<std::string> oldTuple = { "1", "2", "3" };
	std::vector<std::string> newTuple = { "3", "4", "5" };
	std::vector<int> commonSynIndex = { 2, -1, -1 };
	std::vector<std::string>resultTuple = resultTable.mergeTuple(oldTuple, newTuple, commonSynIndex);
	std::vector<std::string> expectedResult = { "1", "2", "3", "4", "5"};
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}


TEST_CASE("Test insertTuple") {
	ResultTable resultTable = resultTableGenerator(1);
	resultTable.insertTuple({ "4", "8", "13" });
	REQUIRE(resultTable.getColNum() == 5);
	std::vector<std::string> resultTuple = resultTable.getTuple(4);
	std::vector<std::string> expectedResult = { "4", "8", "13" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}

TEST_CASE("Test deleteTuple") {
	ResultTable resultTable = resultTableGenerator(1);
	resultTable.deleteTuple(2);
	REQUIRE(resultTable.getColNum() == 3);
	std::vector<std::string> resultTuple = resultTable.getTuple(1);
	std::vector<std::string> expectedResult = { "2", "6", "10" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));

	resultTuple = resultTable.getTuple(2);
	expectedResult = { "4", "8", "12" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}

TEST_CASE("Test getStringSetFromKey") {
	ResultTable resultTable = resultTableGenerator(2);
	std::set<std::string> result = resultTable.getStringSetFromKey("a1");
	REQUIRE(result.size() == 1 );
	REQUIRE(result.count("1") == 1);
}

TEST_CASE("Test combineTable 1: no common synonym") {
	ResultTable resultTable = resultTableGenerator(1);
	ResultTable tempResultTable = resultTableGenerator(3);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 16);
	REQUIRE(resultTable.getRowNum() == 5);

	std::vector<std::string> expectedSynList = { "a1", "a2", "a3", "b1", "b2" };
	for (int i = 0; i < expectedSynList.size(); i++) {
		REQUIRE(resultTable.getSynList()[i] == expectedSynList[i]);
	}
}

TEST_CASE("Test combineTable 2: one common synonym") {
	ResultTable resultTable = resultTableGenerator(2);
	ResultTable tempResultTable = resultTableGenerator(4);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 16);
	REQUIRE(resultTable.getRowNum() == 3);
}

TEST_CASE("Test combineTable 3: two common synonyms") {
	ResultTable resultTable = resultTableGenerator(1);
	ResultTable tempResultTable = resultTableGenerator(2);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 1);
	REQUIRE(resultTable.getRowNum() == 3);
}

TEST_CASE("Test combineTable 4: resultTable just initialized to combine with tempResultTable") {
	ResultTable resultTable = ResultTable();
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.getRowNum() == 0);
	REQUIRE(resultTable.isTableEmpty() == true);
	ResultTable tempResultTable = resultTableGenerator(1);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 4);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == false);
}

TEST_CASE("Test combineTable 5: empty tempResultTable") {
	ResultTable resultTable = resultTableGenerator(1);
	REQUIRE(resultTable.getColNum() == 4);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == false);
	ResultTable tempResultTable = ResultTable({}, "a1");
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == true);
}

TEST_CASE("Test combineTable 6: common synonym but no intersection, resultTable should be empty, synList should be the union") {
	ResultTable resultTable = resultTableGenerator(2);
	REQUIRE(resultTable.getColNum() == 4);
	REQUIRE(resultTable.getRowNum() == 2);
	REQUIRE(resultTable.isTableEmpty() == false);
	ResultTable tempResultTable = resultTableGenerator(5);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == true);
}


