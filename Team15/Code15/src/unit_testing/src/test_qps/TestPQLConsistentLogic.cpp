#include "qps/include/tokenizer/PQLRefConsistentLogic.h"
#include "qps/include/model/Query.h"
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
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent", "while", "quoted_ident") == false);
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
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Parent*", "while", "quoted_ident") == false);
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
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows*", "while", "quoted_ident") == false);
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
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "variable", "integer") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "procedure", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("Follows", "while", "quoted_ident") == false);
	}
}
TEST_CASE("Test ModifiesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "call", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "read", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "stmt", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "integer", "quoted_ident") == true);
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "procedure", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesS", "while", "while") == false);
	}
}

TEST_CASE("Test ModifiesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "procedure", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quoted_ident", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quoted_ident", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quoted_ident", "quoted_ident") == true);
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "assign", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("ModifiesP", "while", "while") == false);
	}
}

TEST_CASE("Test UsesP Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "procedure", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quoted_ident", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quoted_ident", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quoted_ident", "quoted_ident") == true);
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "print", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "while", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "variable", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "assign", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "print", "procedure") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "quoted_ident", "if") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesP", "while", "while") == false);
	}
}

TEST_CASE("Test UsesS Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "print", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "assign", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "while", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "if", "_") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "integer", "variable") == true);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "stmt", "quoted_ident") == true);
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "read", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "procedure", "_") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "quoted_ident", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "procedure", "variable") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "read", "_") == false);
		REQUIRE(refConsistentLogic->hasRelationRef("UsesS", "variable", "quoted_ident") == false);
	}
}

TEST_CASE("Test With Cases") {
	SECTION("Test Positive Cases") {
		REQUIRE(refConsistentLogic->isWithRefCompatible("call", "procName", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->isWithRefCompatible("call", "stmt#", "integer") == true);
		REQUIRE(refConsistentLogic->isWithRefCompatible("print", "varName", "quoted_ident") == true);
		REQUIRE(refConsistentLogic->isWithRefCompatible("read", "stmt#", "integer") == true);
		REQUIRE(refConsistentLogic->isWithRefCompatible("constant", "value", "integer") == true);
		REQUIRE(refConsistentLogic->isWithRefCompatible("while", "stmt#", "integer") == true);
	}
	SECTION("Test Negative Cases") {
		REQUIRE(refConsistentLogic->isWithRefCompatible("call", "value", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->isWithRefCompatible("call", "stmt#", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->isWithRefCompatible("print", "varName", "integer") == false);
		REQUIRE(refConsistentLogic->isWithRefCompatible("read", "procName", "quoted_ident") == false);
		REQUIRE(refConsistentLogic->isWithRefCompatible("constant", "stmt#", "integer") == false);
		REQUIRE(refConsistentLogic->isWithRefCompatible("while", "variable", "quoted_ident") == false);
	}
}
