#include "QPS/include/tokenizer/PQLRefConsistentLogic.h"
#include "QPS/include/model/Query.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"

#include "catch.hpp"

using namespace std;
shared_ptr<PQLRefConsistentLogic> refConsistentLogic = make_shared<PQLRefConsistentLogic>();

TEST_CASE("Test Parent Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Parent Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Parent Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test Parent* Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Parent* Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Parent* Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test Follows* Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Follows* Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Follows* Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test Follows Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "stmt", "stmt") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "read", "read") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "print", "print") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "call", "call") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "while", "if") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "assign", "integer") == true);
		cout << "PQLRefConsistentLogic:Test Follows Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "while", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test Follows Cases:Test Negative Cases:passed" << endl;
	}
}
TEST_CASE("Test ModifiesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "call", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "read", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "stmt", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "integer", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test ModifiesS Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "procedure", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test ModifiesS Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test ModifiesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quotedIdent", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quotedIdent", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quotedIdent", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test ModifiesP Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "assign", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test ModifiesP Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test UsesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quotedIdent", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quotedIdent", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quotedIdent", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test UsesP Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "assign", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quotedIdent", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "while", "while") == false);
		cout << "PQLRefConsistentLogic:Test UsesP Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test UsesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "print", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "while", "quotedIdent") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "integer", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "stmt", "quotedIdent") == true);
		cout << "PQLRefConsistentLogic:Test UsesS Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "read", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "procedure", "_") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "quotedIdent", "quotedIdent") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "read", "_") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "variable", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test UsesS Cases:Test Negative Cases:passed" << endl;
	}
}

TEST_CASE("Test With Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasWithRef("call", "procName", "main") == true);
		REQUIRE(refConsistentLogic->hasWithRef("call", "stmt#", "14") == true);
		REQUIRE(refConsistentLogic->hasWithRef("print", "varName", "var1") == true);
		REQUIRE(refConsistentLogic->hasWithRef("read", "stmt#", "52") == true);
		REQUIRE(refConsistentLogic->hasWithRef("constant", "value", "15") == true);
		REQUIRE(refConsistentLogic->hasWithRef("while", "stmt#", "1") == true);
		cout << "PQLRefConsistentLogic:Test With Cases:Test Positive Cases:passed" << endl;
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasWithRef("call", "value", "main") == false);
		REQUIRE(refConsistentLogic->hasWithRef("call", "stmt#", "main") == false);
		REQUIRE(refConsistentLogic->hasWithRef("print", "varName", "1") == false);
		REQUIRE(refConsistentLogic->hasWithRef("read", "procName", "var1") == false);
		REQUIRE(refConsistentLogic->hasWithRef("constant", "stmt#", "52") == false);
		REQUIRE(refConsistentLogic->hasWithRef("while", "variable", "quotedIdent") == false);
		cout << "PQLRefConsistentLogic:Test With Cases:Test Negative Cases:passed" << endl;
	}
}
