#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Query.h"
#include "QPS/include/model/Result.h"
#include <set>
#include "catch.hpp"
#include <assert.h>
#include <memory>
#include "pkb/include/PKB.h"

using namespace std;


// ResultTable resultTableGenerator(int sampleNum) {
//	ResultTable resultTable;
//	if (sampleNum == 1) {
//		SynonymLinkageMap s1Ins4LinkageMap({ { "s2", std::set<std::string>({"5", "6"})} });
//		SynonymLinkageMap s1Ins5LinkageMap({ { "s2", std::set<std::string>({"5", "6"})} });
//
//		SynonymLinkageMap s2Ins5LinkageMap({ { "s1", std::set<std::string>({"4", "5"})} });
//		SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"4", "5"})} });
//		std::unordered_map<std::string,
//			std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//				{"s1", {
//					{"4", s1Ins4LinkageMap},
//					{"5", s1Ins5LinkageMap}
//					}
//				},
//				{"s2", {
//					{"5", s2Ins5LinkageMap},
//					{"6", s2Ins6LinkageMap}
//					}
//				}
//		};
//		resultTable = ResultTable(testTable);
//	}
//	else if (sampleNum == 2) {
//		SynonymLinkageMap s1Ins4LinkageMap({ { "s2", std::set<std::string>({"5"})} });

//		SynonymLinkageMap s1Ins5LinkageMap({
//			{ "s2", std::set<std::string>({"6"})},
//			{ "s3", std::set<std::string>({"7"})} });
//
//		SynonymLinkageMap s2Ins5LinkageMap({

//			{ "s1", std::set<std::string>({"4"})},
//			{ "s3", std::set<std::string>({"7"})} });
//		SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//

//			{ "s1", std::set<std::string>({"5"})},
//			{ "s2", std::set<std::string>({"5"})} });
//		std::unordered_map<std::string,
//			std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//				{"s1", {
//					{"4", s1Ins4LinkageMap},
//					{"5", s1Ins5LinkageMap}
//					}
//				},
//				{"s2", {
//					{"5", s2Ins5LinkageMap},
//					{"6", s2Ins6LinkageMap}
//					}
//				},
//				{"s3", {
//					{"7", s2Ins7LinkageMap}
//					}
//				}
//		};
//		resultTable = ResultTable(testTable);
//	}
//	else if (sampleNum == 3) {
//		SynonymLinkageMap s1Ins4LinkageMap({ { "s2", std::set<std::string>({"5", "7"})}});
//
//		SynonymLinkageMap s2Ins5LinkageMap({{ "s1", std::set<std::string>({"4"})} });
//		SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"4"})} });
//
//		std::unordered_map<std::string,
//			std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//				{"s1", {
//					{"4", s1Ins4LinkageMap}
//					}
//				},
//				{"s2", {
//					{"5", s2Ins5LinkageMap},
//					{"7", s2Ins7LinkageMap}
//					}
//				}
//		};
//		resultTable = ResultTable(testTable);
//	}
//	return resultTable;

//	Result result;
//	if (sampleNum == 1) {
//		SynonymLinkageMap currS2Ins5LinkageMap = SynonymLinkageMap();
//		SynonymLinkageMap currS2Ins6LinkageMap = SynonymLinkageMap();
//		std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"5", currS2Ins5LinkageMap},
//				{"6", currS2Ins6LinkageMap}
//		};
//		result = Result(true, "s1", currLeftResult);
//	}
//	else if (sampleNum == 2) {
//		SynonymLinkageMap currS2Ins5LinkageMap = SynonymLinkageMap();
//		SynonymLinkageMap currS2Ins6LinkageMap = SynonymLinkageMap();
//		std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"5", currS2Ins5LinkageMap},
//				{"6", currS2Ins6LinkageMap}
//		};
//		result.setSecondArg("s1", currRightResult);
//	}
//	else if (sampleNum == 3) {
//		SynonymLinkageMap currS1Ins5LinkageMap = SynonymLinkageMap({ { "s2", std::set<std::string>({"4"})} });
//		SynonymLinkageMap currS1Ins6LinkageMap = SynonymLinkageMap({ { "s2", std::set<std::string>({"3"})} });
//		SynonymLinkageMap currS2Ins3LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"6"})} });
//		SynonymLinkageMap currS2Ins4LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"5"})} });

//		std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"5", currS1Ins5LinkageMap},
//				{"6", currS1Ins6LinkageMap}
//		};
//		std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"3", currS2Ins3LinkageMap},
//				{"4", currS2Ins4LinkageMap}
//		};
//		result = Result(true, "s1", currLeftResult, "s2", currRightResult);
//	} else if (sampleNum == 4) {
//		SynonymLinkageMap currS1Ins4LinkageMap = SynonymLinkageMap({ { "s2", std::set<std::string>({"7", "8"})}});
//		SynonymLinkageMap currS1Ins5LinkageMap = SynonymLinkageMap({ { "s2", std::set<std::string>({"6", "7"})}});
//		SynonymLinkageMap currS2Ins6LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"5"})} });
//		SynonymLinkageMap currS2Ins7LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"4", "5"})}});
//		SynonymLinkageMap currS2Ins8LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"4"})} });
//
//		std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"4", currS1Ins4LinkageMap},
//				{"5", currS1Ins5LinkageMap}
//		};
//		std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"6", currS2Ins6LinkageMap},
//				{"7", currS2Ins7LinkageMap},
//				{"8", currS2Ins8LinkageMap}
//		};
//		result = Result(true, "s1", currLeftResult, "s2", currRightResult);
//	}
//	else if (sampleNum == 5) {
//		SynonymLinkageMap currS2Ins5LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"4"})} });
//		SynonymLinkageMap currS2Ins6LinkageMap = SynonymLinkageMap({ { "s1", std::set<std::string>({"4"})} });
//
//		std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"5", currS2Ins5LinkageMap},
//				{"6", currS2Ins6LinkageMap}
//		};
//		result.setSecondArg("s2", currRightResult);
//	}
//	return result;

//}
//
//TEST_CASE("Test combineResult function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result resultLeftSyn = resultGenerator(1);
//	clauseHandler.combineResult(resultTable, resultLeftSyn);
//
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("5").getLinkedSynValueSet("s2").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet("s2").count("4") == 0);
//
//	Result resultRightSyn = resultGenerator(2);
//	clauseHandler.combineResult(resultTable, resultRightSyn);
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("5").getLinkedSynValueSet("s2").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet("s2").count("4") == 0);
//}
//
//TEST_CASE("Test resultTableCheckAndAdd function in ClauseHandler") {
//	PKB pkb;
//	pkb.addVar("x");
//	pkb.addVar("y");
//	pkb.addVar("k");
//	ClauseHandler clauseHandler(pkb);
//	ResultTable resultTable;
//	clauseHandler.resultTableCheckAndAdd("v1", resultTable, "variable");
//	REQUIRE(resultTable.getSynonymEntry("v1").size() == 3);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("x") == 1);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("y") == 1);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("k") == 1);
//}
//
//TEST_CASE("Test combineTwoSynResult function in ClauseHandler") {
//	SynonymLinkageMap s1Ins5LinkageMap({
//		{ "s2", {"6", "7"}},
//		{ "s3", {"9"} }
//		});
//
//	SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//
//	SynonymLinkageMap s3Ins9LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", s1Ins5LinkageMap}
//				}
//			},
//			{"s2", {
//				{"6", s2Ins6LinkageMap},
//				{"7", s2Ins7LinkageMap}
//				}
//			},
//			{"s3", {
//				{"9", s3Ins9LinkageMap}
//				}
//			}
//	};
//	ResultTable resultTable(testTable);
//
//	SynonymLinkageMap currS1Ins5LinkageMap({ { "s2", std::set<std::string>({"7", "8"})} });
//
//	SynonymLinkageMap currS2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap currS2Ins8LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"5", currS1Ins5LinkageMap}
//	};
//	std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"7", currS2Ins7LinkageMap},
//				{"8", currS2Ins8LinkageMap}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//

// }
//
// TEST_CASE("Test combineResult function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result resultLeftSyn = resultGenerator(1);
//	clauseHandler.combineResult(resultTable, resultLeftSyn);
//
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("5").getLinkedSynValueSet("s2").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet("s2").count("4") == 0);
//
//	Result resultRightSyn = resultGenerator(2);
//	clauseHandler.combineResult(resultTable, resultRightSyn);
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("5").getLinkedSynValueSet("s2").count("4") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet("s2").count("4") == 0);
// }
//
// TEST_CASE("Test resultTableCheckAndAdd function in ClauseHandler") {
//	PKB pkb;
//	pkb.addVar("x");
//	pkb.addVar("y");
//	pkb.addVar("k");
//	ClauseHandler clauseHandler(pkb);
//	ResultTable resultTable;
//	clauseHandler.resultTableCheckAndAdd("v1", resultTable, "variable");
//	REQUIRE(resultTable.getSynonymEntry("v1").size() == 3);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("x") == 1);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("y") == 1);
//	REQUIRE(resultTable.getSynonymEntry("v1").count("k") == 1);
// }
//
// TEST_CASE("Test combineTwoSynResult function in ClauseHandler") {
//	SynonymLinkageMap s1Ins5LinkageMap({
//		{ "s2", {"6", "7"}},
//		{ "s3", {"9"} }
//		});
//
//	SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//
//	SynonymLinkageMap s3Ins9LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", s1Ins5LinkageMap}
//				}
//			},
//			{"s2", {
//				{"6", s2Ins6LinkageMap},
//				{"7", s2Ins7LinkageMap}
//				}
//			},
//			{"s3", {
//				{"9", s3Ins9LinkageMap}
//				}
//			}
//	};
//	ResultTable resultTable(testTable);
//
//	SynonymLinkageMap currS1Ins5LinkageMap({ { "s2", std::set<std::string>({"7", "8"})} });
//
//	SynonymLinkageMap currS2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap currS2Ins8LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"5", currS1Ins5LinkageMap}
//	};
//	std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"7", currS2Ins7LinkageMap},
//				{"8", currS2Ins8LinkageMap}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//

//	clauseHandler.combineTwoSynResult("s1", currLeftResult, "s2", currRightResult, resultTable);
//	std::unordered_map<std::string, std::set<std::string>> synonymInstance5LinkageMap = resultTable.getSynonymEntry("s1").find("5")->second.getLinkageMap();
//
//	//only the intersected linkage 7 left
//	REQUIRE(synonymInstance5LinkageMap.count("s2") != 0);
//	REQUIRE(synonymInstance5LinkageMap.find("s2")->second.size() == 1);
//	REQUIRE(synonymInstance5LinkageMap.find("s2")->second.count("7") == 1);
//	//s3 entry with 9 should still be kept
//	REQUIRE(synonymInstance5LinkageMap.find("s3")->second.size() == 1);
//
//	//in the table, 6 in s2 should be deleted
//	REQUIRE(resultTable.getSynonymEntry("s2").count("6") == 0);

//	SynonymLinkageMap s1Ins6LinkageMap({ { "s2", std::set<std::string>({"8"})} });
//	SynonymLinkageMap s1Ins7LinkageMap({ { "s2", std::set<std::string>({"9"})} });
//	SynonymLinkageMap s1Ins8LinkageMap({ { "s2", std::set<std::string>({"8"})} });
//
//	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"6", "8"})} });
//	SynonymLinkageMap s2Ins9LinkageMap({ { "s1", std::set<std::string>({"7"})} });
//
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"6", s1Ins6LinkageMap},
//				{"7", s1Ins7LinkageMap},
//				{"8", s1Ins8LinkageMap}
//				}
//			},
//			{"s2", {
//				{"8", s2Ins8LinkageMap},
//				{"9", s2Ins9LinkageMap}
//				}
//			}
//	};
//	ResultTable resultTable(testTable);
//
//	SynonymLinkageMap currS1Ins5LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})} });
//	SynonymLinkageMap currS1Ins6LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})} });
//	SynonymLinkageMap currS1Ins7LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})} });
//
//	SynonymLinkageMap currS2Ins8LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})} });
//	SynonymLinkageMap currS2Ins9LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})} });
//	SynonymLinkageMap currS2Ins10LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})} });
//	std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
//				{"5", currS1Ins5LinkageMap},
//				{"6", currS1Ins6LinkageMap},
//				{"7", currS1Ins7LinkageMap}
//	};
//	std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
//				{"8", currS2Ins8LinkageMap},
//				{"9", currS2Ins9LinkageMap},
//				{"10", currS2Ins10LinkageMap}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	clauseHandler.combineTwoSynResult("s1", currLeftResult, "s2", currRightResult, resultTable);
//
//	//only the intersected linkage 7 left
//	REQUIRE(resultTable.getSynonymEntry("s1").find("6")->second.getLinkageMap().find("s2")->second.size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").find("6")->second.getLinkageMap().find("s2")->second.count("8") == 1);
//
//	REQUIRE(resultTable.getSynonymEntry("s1").find("7")->second.getLinkageMap().find("s2")->second.size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").find("7")->second.getLinkageMap().find("s2")->second.count("9") == 1);
//
//	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.count("6") == 1);
//
//	REQUIRE(resultTable.getSynonymEntry("s2").find("9")->second.getLinkageMap().find("s1")->second.size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s2").find("9")->second.getLinkageMap().find("s1")->second.count("7") == 1);

//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", SynonymLinkageMap()},
//				{"6", SynonymLinkageMap()},
//				{"7", SynonymLinkageMap()}
//				}
//			}
//	};
//	ResultTable resultTable(testTable);

//	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
//				{"6", SynonymLinkageMap()},
//				{"7", SynonymLinkageMap()},
//				{"8", SynonymLinkageMap()}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
//	REQUIRE(resultTable.getSynonymEntry("s1").find("5") == resultTable.getSynonymEntry("s1").end());
//	REQUIRE(resultTable.getSynonymEntry("s1").find("8") == resultTable.getSynonymEntry("s1").end());
//	REQUIRE(resultTable.getSynonymEntry("s1").find("6") != resultTable.getSynonymEntry("s1").end());
//	REQUIRE(resultTable.getSynonymEntry("s1").find("7") != resultTable.getSynonymEntry("s1").end());

//		});
//	SynonymLinkageMap s1Ins6LinkageMap({ { "s2", std::set<std::string>({"7", "8"})}});
//	SynonymLinkageMap s1Ins7LinkageMap({ { "s2", std::set<std::string>({"8"})} });
//
//	SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5", "6"})}});
//	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})}});
//
//	SynonymLinkageMap s3Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", s1Ins5LinkageMap},
//				{"6", s1Ins6LinkageMap},
//				{"7", s1Ins7LinkageMap}
//				}
//			},
//			{"s2", {
//				{"6", s2Ins6LinkageMap},
//				{"7", s2Ins7LinkageMap},
//				{"8", s2Ins8LinkageMap}
//				}
//			},
//			{"s3", {
//				{"6", s3Ins6LinkageMap}
//			}}
//	};
//	ResultTable resultTable(testTable);
//
//	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
//				{"6", SynonymLinkageMap()},
//				{"7", SynonymLinkageMap()},
//				{"8", SynonymLinkageMap()}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
//	//instance 5 should be deleted
//	REQUIRE(resultTable.getSynonymEntry("s1").find("5") == resultTable.getSynonymEntry("s1").end());
//	//instance 6 in s2 should also be deleted since it has only one linked synonym 5
//	REQUIRE(resultTable.getSynonymEntry("s2").find("6") == resultTable.getSynonymEntry("s2").end());
//	//instance 7 and 8 in s2 should not contain links to 5 in s1
//	REQUIRE(resultTable.getSynonymEntry("s2").find("7")->second.getLinkageMap().find("s1")->second.count("5") == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.count("5") == 0);
//	//instance 6 in s3 should also delete 5, and since 6 in s3 only contains one link and it is deleted, 6 should be deleted
//	REQUIRE(resultTable.getSynonymEntry("s3").count("6") == 0);

//		{ "s1", std::set<std::string>({"5"})},
//		{ "s3", std::set<std::string>({"7"})} });
//
//	SynonymLinkageMap s3Ins7LinkageMap({ { "s2", std::set<std::string>({"6"})} });
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", s1Ins5LinkageMap}
//				}
//			},
//			{"s2", {
//				{"6", s2Ins6LinkageMap}
//				}
//			},
//			{"s3", {
//				{"7", s3Ins7LinkageMap}
//			}}
//	};
//	ResultTable resultTable(testTable);
//
//	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
//				{"6", SynonymLinkageMap()},
//				{"7", SynonymLinkageMap()},
//				{"8", SynonymLinkageMap()}
//	};
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
//	//instance 5 should be deleted
//	REQUIRE(resultTable.getSynonymEntry("s1").count("5") == 0);
//	//instance 6 in s2 should also be deleted since it has only one linked s1: 5
//	REQUIRE(resultTable.getSynonymEntry("s2").count("6") == 0);
//	//instance 7 in s3 should also be deleted
//	REQUIRE(resultTable.getSynonymEntry("s3").count("7") == 0);

//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result result = resultGenerator(3);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();

//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterCurrResult(firstArgName, firstArgVal, secondArgName, secondArgVal, resultTable);
//	REQUIRE(firstArgVal.size() == 1);
//	REQUIRE(firstArgVal.count("6") == 0);
//	REQUIRE(secondArgVal.size() == 1);
//	REQUIRE(secondArgVal.count("3") == 0);
//}
//
//TEST_CASE("Test filterResultTable function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(2);
//	Result result = resultGenerator(3);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterResultTable(firstArgName, firstArgVal, resultTable);
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").size() == 0);
//	REQUIRE(resultTable.getSynonymEntry("s3").size() == 0);
//}
//
//TEST_CASE("Test filterCurrResultLinkageSet function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result result = resultGenerator(4);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterCurrResultLinkageSet(firstArgName, firstArgVal, secondArgName, secondArgVal, resultTable);
//	REQUIRE(firstArgVal.size() == 1);
//	REQUIRE(firstArgVal.at("5").getLinkedSynValueSet("s2").size() == 1);
//	REQUIRE(firstArgVal.at("5").getLinkedSynValueSet("s2").count("6") == 1);
//	REQUIRE(secondArgVal.size() == 1);
//	REQUIRE(secondArgVal.count("6") == 1);
//
//}
//
//TEST_CASE("Test filterResultTableLinkageSet function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//

//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterCurrResult(firstArgName, firstArgVal, secondArgName, secondArgVal, resultTable);
//	REQUIRE(firstArgVal.size() == 1);
//	REQUIRE(firstArgVal.count("6") == 0);
//	REQUIRE(secondArgVal.size() == 1);
//	REQUIRE(secondArgVal.count("3") == 0);
// }
//
// TEST_CASE("Test filterResultTable function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(2);
//	Result result = resultGenerator(3);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterResultTable(firstArgName, firstArgVal, resultTable);
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 0);
//	REQUIRE(resultTable.getSynonymEntry("s2").size() == 0);
//	REQUIRE(resultTable.getSynonymEntry("s3").size() == 0);
// }
//
// TEST_CASE("Test filterCurrResultLinkageSet function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result result = resultGenerator(4);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterCurrResultLinkageSet(firstArgName, firstArgVal, secondArgName, secondArgVal, resultTable);
//	REQUIRE(firstArgVal.size() == 1);
//	REQUIRE(firstArgVal.at("5").getLinkedSynValueSet("s2").size() == 1);
//	REQUIRE(firstArgVal.at("5").getLinkedSynValueSet("s2").count("6") == 1);
//	REQUIRE(secondArgVal.size() == 1);
//	REQUIRE(secondArgVal.count("6") == 1);
//
// }
//
// TEST_CASE("Test filterResultTableLinkageSet function in ClauseHandler") {
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//
//	ResultTable resultTable = resultTableGenerator(1);
//	Result result = resultGenerator(4);
//	std::string firstArgName = result.getFirstArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
//	std::string secondArgName = result.getSecondArgName();
//	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
//	clauseHandler.filterResultTableLinkageSet(firstArgName, firstArgVal, secondArgName, resultTable);
//	REQUIRE(resultTable.getSynonymEntry("s1").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").at("5").getLinkedSynValueSet(secondArgName).size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s1").at("5").getLinkedSynValueSet(secondArgName).count("6") == 1);
//
//	REQUIRE(resultTable.getSynonymEntry("s2").size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet(firstArgName).size() == 1);
//	REQUIRE(resultTable.getSynonymEntry("s2").at("6").getLinkedSynValueSet(firstArgName).count("5") == 1);

//}

//
////TEST_CASE("Test filterOneSynWithLinkage function in ClauseHandler") {
////	PKB pkb;
////	ClauseHandler clauseHandler(pkb);
////
////	ResultTable resultTable = resultTableGenerator(3);
////	Result result = resultGenerator(5);
////	std::string secondArgName = result.getSecondArgName();
////	std::unordered_map<std::string, SynonymLinkageMap> secondArgVal = result.getSecondArgValue();
////	std::string firstArgName = "s1";
////	clauseHandler.filterOneSynWithLinkage(secondArgName, secondArgVal, firstArgName, resultTable);
////
////	REQUIRE(secondArgVal.count("5") == 1);
////	REQUIRE(secondArgVal.count("6") == 0);
////}
////
////TEST_CASE("Test filterOneSynLinkageSet function in ClauseHandler") {
////
////}
//


//	SynonymLinkageMap s1Ins5LinkageMap({ { "s2", {"7", "8"} } });
//	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"5"})} });
//	std::unordered_map<std::string,
//		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
//			{"s1", {
//				{"5", s1Ins5LinkageMap}
//				}
//			},
//			{"s2", {
//				{"7", s2Ins7LinkageMap},
//				{"8", s2Ins8LinkageMap}
//				}
//			}
//	};
//	ResultTable resultTable(testTable);
//	PKB pkb;
//	ClauseHandler clauseHandler(pkb);
//	clauseHandler.deleteSynTableEntry("s1", "5", resultTable);
//	REQUIRE(resultTable.getSynonymEntry("s1").empty());
//	REQUIRE(resultTable.getSynonymEntry("s2").empty());
//}