#include "QPS/include/model/SynonymLinkageMap.h"
#include "catch.hpp"

TEST_CASE("Test isEmpty function") {
	SECTION("return true") {
		SynonymLinkageMap map;
		REQUIRE(map.isEmpty() == true);
	}
	SECTION("return false") {
		SynonymLinkageMap map;
		map.insertLinkage("synon1", "11" );
		REQUIRE(map.isEmpty() == false);
	}
}

TEST_CASE("Test isEmptyLinkageSet function") {
	SECTION("return true") {
		SynonymLinkageMap map;
		map.insertLinkage("synon1",  "11" );
		REQUIRE(map.isEmptyLinkageSet("synon1") == false);
	}
	SECTION("return false") {
		SynonymLinkageMap map;
		map.deleteLinkage("synon1", "11");
		REQUIRE(map.isEmptyLinkageSet("synon1") == true);
	}
}

TEST_CASE("Test insertLinkage function") {
	SynonymLinkageMap map;

	map.insertLinkage("synon1", "11");
	std::set<std::string> expectedSet = { "11"};
	REQUIRE(map.getLinkageMap().find("synon1")->second == expectedSet);

	map.insertLinkage("synon1", "11");
	map.insertLinkage("synon1", "13");
	//keep only the intersection
	REQUIRE(map.getLinkageMap().find("synon1")->second == expectedSet);
}

TEST_CASE("Test deleteLinkage") {
	SynonymLinkageMap map;

	map.insertLinkage("synon1", "11");
	map.insertLinkage("synon1", "12");
	std::set<std::string> expectedSet = { "11", "12" };
	REQUIRE(map.getLinkageMap().find("synon1")->second == expectedSet);

	expectedSet.erase("11");
	map.deleteLinkage("synon1", "11");
	REQUIRE(map.getLinkageMap().find("synon1")->second == expectedSet);

	expectedSet.erase("12");
	map.deleteLinkage("synon1", "12");
	REQUIRE(map.isEmptyLinkageSet("synon1") == true);
}

