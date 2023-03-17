#include "QPS/include/model/ResultTable.h"
#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Elem.h"

#include "catch.hpp"

//void testSelectSynPkb(PKB& pkb) {
//	pkb.addAllVars(set<string>({ "x", "y" }));
//	pkb.addAllConsts(set<string>({ "5", "10" }));
//
//	unordered_map<string, set<int>> stmts;
//	stmts.insert(make_pair("=", set<int>({ 2, 3 })));
//	stmts.insert(make_pair("if", set<int>({ 1 })));
//	pkb.addAllStmts(stmts);
//
//	unordered_map<string, set<Line>> assignPatterns;
//	Line line2 = Line(2, vector<string>({ "n", "1", "+" }), "=");
//	Line line3 = Line(3, vector<string>({ "m", "1", "-" }), "=");
//
//	assignPatterns.insert(make_pair("n", set<Line>({ line2 })));
//	assignPatterns.insert(make_pair("m", set<Line>({ line3 })));
//	pkb.addAllAssignPatterns(assignPatterns);
//
//	unordered_map<string, set<Line>> ifPatterns;
//	Line line1 = Line(1, vector<string>({ "x", "5", ">" }), "if");
//	ifPatterns.insert(make_pair("x", set<Line>({ line1 })));
//	pkb.addAllIfPatterns(ifPatterns);
//
//	/*
//	procedure main{
//		if (y < 5) {--------------1
//			print x;--------------2
//		} else {
//			read x;---------------3
//		}
//		call foo;-----------------4
//	}
//
//	procedure foo{
//		x = 10;-------------------5
//	}
//	*/
//}

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
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList = { "a1", "a2", "a3" };
	
	ResultTable resultTable = ResultTable(tempTable, synList);
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
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList = { "a1", "a2", "a3" };

	ResultTable resultTable = ResultTable(tempTable, synList);
	resultTable.insertTuple({ "4", "8", "13" });
	REQUIRE(resultTable.getColNum() == 5);
	std::vector<std::string> resultTuple = resultTable.getTuple(4);
	std::vector<std::string> expectedResult = { "4", "8", "13" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}

TEST_CASE("Test deleteTuple") {
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList = { "a1", "a2", "a3" };

	ResultTable resultTable = ResultTable(tempTable, synList);
	resultTable.deleteTuple(2);
	REQUIRE(resultTable.getColNum() == 3);
	std::vector<std::string> resultTuple = resultTable.getTuple(1);
	std::vector<std::string> expectedResult = { "2", "6", "10" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));

	resultTuple = resultTable.getTuple(2);
	expectedResult = { "4", "8", "12" };
	REQUIRE(std::equal(resultTuple.begin(), resultTuple.end(), expectedResult.begin(), expectedResult.end()));
}

TEST_CASE("Test SelectedResult 1") {
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList = { "a1", "a2" };

	ResultTable resultTable = ResultTable(tempTable, synList);
    PKB pkb;
	std::set<std::string> result = resultTable.getSelectedResult({Elem("a1")}, pkb);
	REQUIRE(result.size() == 1 );
	REQUIRE(result.count("1") == 1);
}

TEST_CASE("Test SelectedResult 2 multiple return synonyms") {
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList = { "a1", "a2" };
	ResultTable resultTable(tempTable, synList);
    PKB pkb;
	std::set<std::string> result = resultTable.getSelectedResult({ Elem("a1"), Elem("a2")}, pkb);

	std::set<std::string> expectedResult = { "1 5", "1 6", "1 7", "1 8" };
	REQUIRE(result == expectedResult);
}

TEST_CASE("Test SelectedResult 3 multiple return same synonyms") {
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "1", "2", "2"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList = { "a1", "a2" };
	ResultTable resultTable(tempTable, synList);
    PKB pkb;
	std::set<std::string> result = resultTable.getSelectedResult({ Elem("a1"), Elem("a2"), Elem("a2") }, pkb);

	std::set<std::string> expectedResult = { "1 5 5", "1 6 6", "2 7 7", "2 8 8"};
	REQUIRE(result == expectedResult);
}

//TEST_CASE("Test SelectedResult 4 select attribute") {
//	PQLPreprocessor preprocessor;
//	string queryStr = "assign a; Select a.stmt#";
//	Query query = preprocessor.preprocess(queryStr);
//	SelectClause selectClause = query.getSelectClause();
//	std::multimap<std::string, std::string> varTable = query.getSynonymTable();
//	ResultTable resultTable = ResultTable();
//
//	PKB pkb;
//	testSelectSynPkb(pkb);
//}

TEST_CASE("Test combineTable 1: no common synonym") {
	std::vector<std::vector<std::string>> currTempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> currSynList = { "a1", "a2", "a3" };

	ResultTable resultTable = ResultTable(currTempTable, currSynList);


	std::vector<std::vector<std::string>> newTempTable = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> newSynList = { "b1", "b2" };

	ResultTable tempResultTable = ResultTable(newTempTable, newSynList);

	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 16);
	REQUIRE(resultTable.getRowNum() == 5);

	std::vector<std::string> expectedSynList = { "a1", "a2", "a3", "b1", "b2" };
	for (int i = 0; i < expectedSynList.size(); i++) {
		REQUIRE(resultTable.getSynList()[i] == expectedSynList[i]);
	}
}

TEST_CASE("Test combineTable 2: one common synonym") {
	std::vector<std::vector<std::string>> tempTable1 = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList1 = { "a1", "a2" };
	ResultTable resultTable = ResultTable(tempTable1, synList1);

	std::vector<std::vector<std::string>> tempTable2 = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList2 = { "a1", "b1" }; 
	ResultTable tempResultTable = ResultTable(tempTable2, synList2);

	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 16);
	REQUIRE(resultTable.getRowNum() == 3);
}

TEST_CASE("Test combineTable 3: two common synonyms") {
	std::vector<std::vector<std::string>> tempTable1 = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList1 = { "a1", "a2", "a3" };
	ResultTable resultTable = ResultTable(tempTable1, synList1);

	std::vector<std::vector<std::string>> tempTable2 = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList2 = { "a1", "a2" };
	ResultTable tempResultTable = ResultTable(tempTable2, synList2);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 1);
	REQUIRE(resultTable.getRowNum() == 3);
}

TEST_CASE("Test combineTable 4: resultTable just initialized to combine with tempResultTable") {
	ResultTable resultTable = ResultTable();
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.getRowNum() == 0);
	REQUIRE(resultTable.isTableEmpty() == true);
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList = { "a1", "a2", "a3" };

	ResultTable tempResultTable = ResultTable(tempTable, synList);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 4);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == false);
}

TEST_CASE("Test combineTable 5: empty tempResultTable") {
	std::vector<std::vector<std::string>> tempTable = {
			{"1", "2", "3", "4"},
			{"5", "6", "7", "8"},
			{"9", "10", "11", "12"}
	};
	std::vector<std::string> synList = { "a1", "a2", "a3" };

	ResultTable resultTable = ResultTable(tempTable, synList);
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
	std::vector<std::vector<std::string>> tempTable1 = {
			{"1", "1", "1", "1"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList1 = { "a1", "a2" };
	ResultTable resultTable = ResultTable(tempTable1, synList1);

	REQUIRE(resultTable.getColNum() == 4);
	REQUIRE(resultTable.getRowNum() == 2);
	REQUIRE(resultTable.isTableEmpty() == false);

	std::vector<std::vector<std::string>> tempTable2 = {
			{"2", "2", "2", "2"},
			{"5", "6", "7", "8"}
	};
	std::vector<std::string> synList2 = { "a1", "b1" };

	ResultTable tempResultTable = ResultTable(tempTable2, synList2);
	resultTable.combineTable(tempResultTable);
	REQUIRE(resultTable.getColNum() == 0);
	REQUIRE(resultTable.getRowNum() == 3);
	REQUIRE(resultTable.isTableEmpty() == true);
}


