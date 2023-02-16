#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include <set>
#include "catch.hpp"
#include <assert.h>
#include <memory> 
#include "PKB.h"

using namespace std;

TEST_CASE("Test deleteSynTableEntry function in ClauseHandler") {
	SynonymLinkageMap s1Ins5LinkageMap({ { "s2", {"7", "8"} } });
	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})}});
	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"5"})}});
	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable ={
			{"s1", {
				{"5", s1Ins5LinkageMap}
				}
			},
			{"s2", {
				{"7", s2Ins7LinkageMap},
				{"8", s2Ins8LinkageMap}
				}
			}
		};
	ResultTable resultTable(testTable);
	PKB pkb;
	ClauseHandler clauseHandler(pkb);
	clauseHandler.deleteSynTableEntry("s1", "5", resultTable);
	REQUIRE(resultTable.getSynonymEntry("s1").empty());
	REQUIRE(resultTable.getSynonymEntry("s2").empty());
}

TEST_CASE("Test combineOneSynResult function in ClauseHandler 1: table intersect synonym key from curr result") {
	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
			{"s1", {
				{"5", SynonymLinkageMap()},
				{"6", SynonymLinkageMap()},
				{"7", SynonymLinkageMap()}
				}
			}
	};
	ResultTable resultTable(testTable);
	
	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
				{"6", SynonymLinkageMap()},
				{"7", SynonymLinkageMap()},
				{"8", SynonymLinkageMap()}
	};
	PKB pkb;
	ClauseHandler clauseHandler(pkb);
	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
	REQUIRE(resultTable.getSynonymEntry("s1").find("5") == resultTable.getSynonymEntry("s1").end());
	REQUIRE(resultTable.getSynonymEntry("s1").find("8") == resultTable.getSynonymEntry("s1").end());
	REQUIRE(resultTable.getSynonymEntry("s1").find("6") != resultTable.getSynonymEntry("s1").end());
	REQUIRE(resultTable.getSynonymEntry("s1").find("7") != resultTable.getSynonymEntry("s1").end());
}

TEST_CASE("Test combineOneSynResult function in ClauseHandler 2: synonym has linkage to other synonym") {
	SynonymLinkageMap s1Ins5LinkageMap({ 
		{"s2", std::set<std::string>({"6", "7", "8"}) },
		{"s3", std::set<std::string>({"6"})} 
		});
	SynonymLinkageMap s1Ins6LinkageMap({ { "s2", std::set<std::string>({"7", "8"})}});
	SynonymLinkageMap s1Ins7LinkageMap({ { "s2", std::set<std::string>({"8"})} });

	SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5", "6"})}});
	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})}});

	SynonymLinkageMap s3Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
			{"s1", {
				{"5", s1Ins5LinkageMap},
				{"6", s1Ins6LinkageMap},
				{"7", s1Ins7LinkageMap}
				}
			},
			{"s2", {
				{"6", s2Ins6LinkageMap},
				{"7", s2Ins7LinkageMap},
				{"8", s2Ins8LinkageMap}
				}
			},
			{"s3", {
				{"6", s3Ins6LinkageMap}
			}}
	};
	ResultTable resultTable(testTable);

	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
				{"6", SynonymLinkageMap()},
				{"7", SynonymLinkageMap()},
				{"8", SynonymLinkageMap()}
	};
	PKB pkb;
	ClauseHandler clauseHandler(pkb);
	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
	//instance 5 should be deleted
	REQUIRE(resultTable.getSynonymEntry("s1").find("5") == resultTable.getSynonymEntry("s1").end());
	//instance 6 in s2 should also be deleted since it has only one linked synonym 5
	REQUIRE(resultTable.getSynonymEntry("s2").find("6") == resultTable.getSynonymEntry("s2").end());
	//instance 7 and 8 in s2 should not contain links to 5 in s1
	REQUIRE(resultTable.getSynonymEntry("s2").find("7")->second.getLinkageMap().find("s1")->second.count("5") == 0);
	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.count("5") == 0);
	//instance 6 in s3 should also delete 5, and since 6 in s3 only contains one link and it is deleted, 6 should be deleted
	REQUIRE(resultTable.getSynonymEntry("s3").count("6") == 0);
}

TEST_CASE("Test combineOneSynResult function in ClauseHandler 3: there are 2 step links") {
	SynonymLinkageMap s1Ins5LinkageMap({ { "s2", std::set<std::string>({"6"}) }});

	SynonymLinkageMap s2Ins6LinkageMap({ 
		{ "s1", std::set<std::string>({"5"})},
		{ "s3", std::set<std::string>({"7"})} });

	SynonymLinkageMap s3Ins7LinkageMap({ { "s2", std::set<std::string>({"6"})} });
	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
			{"s1", {
				{"5", s1Ins5LinkageMap}
				}
			},
			{"s2", {
				{"6", s2Ins6LinkageMap}
				}
			},
			{"s3", {
				{"7", s3Ins7LinkageMap}
			}}
	};
	ResultTable resultTable(testTable);

	std::unordered_map<std::string, SynonymLinkageMap> currResult = {
				{"6", SynonymLinkageMap()},
				{"7", SynonymLinkageMap()},
				{"8", SynonymLinkageMap()}
	};
	PKB pkb;
	ClauseHandler clauseHandler(pkb);
	clauseHandler.combineOneSynResult("s1", currResult, resultTable);
	//instance 5 should be deleted
	REQUIRE(resultTable.getSynonymEntry("s1").count("5") == 0);
	//instance 6 in s2 should also be deleted since it has only one linked s1: 5
	REQUIRE(resultTable.getSynonymEntry("s2").count("6") == 0);
	//instance 7 in s3 should also be deleted
	REQUIRE(resultTable.getSynonymEntry("s3").count("7") == 0);
}

TEST_CASE("Test combineTwoSynResult function in ClauseHandler") {
	SynonymLinkageMap s1Ins5LinkageMap({
		{ "s2", {"6", "7"}},
		{ "s3", {"9"} }
		});

	SynonymLinkageMap s2Ins6LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	SynonymLinkageMap s2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });

	SynonymLinkageMap s3Ins9LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
			{"s1", {
				{"5", s1Ins5LinkageMap}
				}
			},
			{"s2", {
				{"6", s2Ins6LinkageMap},
				{"7", s2Ins7LinkageMap}
				}
			},
			{"s3", {
				{"9", s3Ins9LinkageMap}
				}
			}
	};
	ResultTable resultTable(testTable);

	SynonymLinkageMap currS1Ins5LinkageMap({ { "s2", std::set<std::string>({"7", "8"})} });

	SynonymLinkageMap currS2Ins7LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	SynonymLinkageMap currS2Ins8LinkageMap({ { "s1", std::set<std::string>({"5"})} });
	std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
				{"5", currS1Ins5LinkageMap}
	};
	std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
				{"7", currS2Ins7LinkageMap},
				{"8", currS2Ins8LinkageMap}
	};
	PKB pkb;
	ClauseHandler clauseHandler(pkb);

	clauseHandler.combineTwoSynResult("s1", currLeftResult, "s2", currRightResult, resultTable);
	std::unordered_map<std::string, std::set<std::string>> synonymInstance5LinkageMap = resultTable.getSynonymEntry("s1").find("5")->second.getLinkageMap();

	//only the intersected linkage 7 left
	REQUIRE(synonymInstance5LinkageMap.count("s2") != 0);
	REQUIRE(synonymInstance5LinkageMap.find("s2")->second.size() == 1);
	REQUIRE(synonymInstance5LinkageMap.find("s2")->second.count("7") == 1);
	//s3 entry with 9 should still be kept
	REQUIRE(synonymInstance5LinkageMap.find("s3")->second.size() == 1);

	//in the table, 6 in s2 should be deleted
	REQUIRE(resultTable.getSynonymEntry("s2").count("6") == 0);
}

TEST_CASE("Test combineTwoSynResult function in ClauseHandler 2") {
	SynonymLinkageMap s1Ins6LinkageMap({{ "s2", std::set<std::string>({"8"})}});
	SynonymLinkageMap s1Ins7LinkageMap({ { "s2", std::set<std::string>({"9"})} });
	SynonymLinkageMap s1Ins8LinkageMap({ { "s2", std::set<std::string>({"8"})} });

	SynonymLinkageMap s2Ins8LinkageMap({ { "s1", std::set<std::string>({"6", "8"})}});
	SynonymLinkageMap s2Ins9LinkageMap({ { "s1", std::set<std::string>({"7"})} });

	std::unordered_map<std::string,
		std::unordered_map<std::string, SynonymLinkageMap>> testTable = {
			{"s1", {
				{"6", s1Ins6LinkageMap},
				{"7", s1Ins7LinkageMap},
				{"8", s1Ins8LinkageMap}
				}
			},
			{"s2", {
				{"8", s2Ins8LinkageMap},
				{"9", s2Ins9LinkageMap}
				}
			}
	};
	ResultTable resultTable(testTable);

	SynonymLinkageMap currS1Ins5LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})}});
	SynonymLinkageMap currS1Ins6LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})} });
	SynonymLinkageMap currS1Ins7LinkageMap({ { "s2", std::set<std::string>({"8", "9", "10"})} });

	SynonymLinkageMap currS2Ins8LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})}});
	SynonymLinkageMap currS2Ins9LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})} });
	SynonymLinkageMap currS2Ins10LinkageMap({ { "s1", std::set<std::string>({"5", "6", "7"})} });
	std::unordered_map<std::string, SynonymLinkageMap> currLeftResult = {
				{"5", currS1Ins5LinkageMap},
				{"6", currS1Ins6LinkageMap},
				{"7", currS1Ins7LinkageMap}
	};
	std::unordered_map<std::string, SynonymLinkageMap> currRightResult = {
				{"8", currS2Ins8LinkageMap},
				{"9", currS2Ins9LinkageMap},
				{"10", currS2Ins10LinkageMap}
	};
	PKB pkb;
	ClauseHandler clauseHandler(pkb);

	clauseHandler.combineTwoSynResult("s1", currLeftResult, "s2", currRightResult, resultTable);

	//only the intersected linkage 7 left
	REQUIRE(resultTable.getSynonymEntry("s1").find("6")->second.getLinkageMap().find("s2")->second.size() == 1);
	REQUIRE(resultTable.getSynonymEntry("s1").find("6")->second.getLinkageMap().find("s2")->second.count("8") == 1);

	REQUIRE(resultTable.getSynonymEntry("s1").find("7")->second.getLinkageMap().find("s2")->second.size() == 1);
	REQUIRE(resultTable.getSynonymEntry("s1").find("7")->second.getLinkageMap().find("s2")->second.count("9") == 1);

	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.size() == 1);
	REQUIRE(resultTable.getSynonymEntry("s2").find("8")->second.getLinkageMap().find("s1")->second.count("6") == 1);

	REQUIRE(resultTable.getSynonymEntry("s2").find("9")->second.getLinkageMap().find("s1")->second.size() == 1);
	REQUIRE(resultTable.getSynonymEntry("s2").find("9")->second.getLinkageMap().find("s1")->second.count("7") == 1);
}