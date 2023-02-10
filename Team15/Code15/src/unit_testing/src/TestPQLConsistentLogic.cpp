#include "QPS/include/tokenizer/PQLRefConsistentLogic.h"
#include "QPS/include/model/Query.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"

#include "catch.hpp"

using namespace std;
shared_ptr<PQLRefConsistentLogic> refConsistentLogic = make_shared<PQLRefConsistentLogic>();

TEST_CASE("Test Parent Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("Parent", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Parent Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("Parent", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Parent Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test Parent* Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("Parent*", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Parent* Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("Parent*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Parent*", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Parent* Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test Follows* Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("Follows*", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Follows* Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("Follows*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows*", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Follows* Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test Follows Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("Follows", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRef("Follows", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Follows Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("Follows", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("Follows", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Follows Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test ModifiesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "call", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "read", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "stmt", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "integer", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test ModifiesS Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "procedure", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesS", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test ModifiesS Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test ModifiesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "procedure", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "quotedIdent", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "quotedIdent", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "quotedIdent", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test ModifiesP Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "assign", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("ModifiesP", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test ModifiesP Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test UsesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("UsesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "procedure", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "quotedIdent", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "quotedIdent", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "quotedIdent", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test UsesP Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("UsesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "assign", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesP", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test UsesP Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test UsesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRef("UsesS", "print", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "while", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "integer", "variable") == true);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "stmt", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test UsesS Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRef("UsesS", "read", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "procedure", "_") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "quotedIdent", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "read", "_") == false);
		REQUIRE(refConsistentLogic->hasRef("UsesS", "variable", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test UsesS Cases:Test Negative Cases:passed" << endl;
	}
}
