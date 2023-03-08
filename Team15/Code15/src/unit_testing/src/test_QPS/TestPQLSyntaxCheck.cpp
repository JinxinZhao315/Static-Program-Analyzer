#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Query.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("PQLSyntaxChecker positive test 1") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("constant c; Select c"));
}
TEST_CASE("PQLSyntaxChecker positive test 2: spaces") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a; Select a such that Follows      (a   ,      11    )    "));
}
TEST_CASE("PQLSyntaxChecker positive test 3: key word as syn name") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign pattern; Select pattern such that Follows(pattern,11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign assign; Select assign such that Follows(assign,11)"));
}
TEST_CASE("PQLSyntaxChecker positive test 4: different format of Select Clause") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1; Select a1"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign BOOLEAN; Select BOOLEAN"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("Select BOOLEAN"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2, a3; Select <a1, a2, a3>"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select <		 a1 ,   a2  >"));
	//REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a; Select<a, a>"));
}
TEST_CASE("PQLSyntaxChecker positive test 5: Follows valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(a1,11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(a1,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(a1,a2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(11,a1)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(11,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(11,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(_,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(_,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows(_,a1)"));
}
TEST_CASE("PQLSyntaxChecker positive test 6: Follows* valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(a1,11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(a1,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(a1,a2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(11,a1)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(11,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(11,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(_,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(_,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Follows*(_,a1)"));
}
TEST_CASE("PQLSyntaxChecker positive test 7: Parent* valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(a1,11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(a1,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(a1,a2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(11,a1)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(11,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(11,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(_,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(_,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent(_,a1)"));
}
TEST_CASE("PQLSyntaxChecker positive test 8: Parent* valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(a1,11)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(a1,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(a1,a2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(11,a1)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(11,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(11,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(_,12)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(_,_)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("assign a1, a2; Select a1 such that Parent*(_,a1)"));
}
TEST_CASE("PQLSyntaxChecker positive test 9: Calls valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(p1, p2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(p1, _)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(p1, \"proc\")"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(_, p2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(_, _)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(_, \"proc\")"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(\"proc\", p2)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(\"proc\", _)"));
	REQUIRE_NOTHROW(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(\"proc\", \"proc\")"));
}
TEST_CASE("PQLSyntaxChecker positive test 9: Uses valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	int count = 0;
	try {preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(a1,_)");}
	catch (PQLSyntaxError e) {REQUIRE(false);}
	catch (PQLSemanticError e) { REQUIRE(true); }

	try {preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(a1,a2)");}
	catch (PQLSyntaxError e) {REQUIRE(false);}
	catch (PQLSemanticError e) { REQUIRE(true); }

	try {preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(a1,\"x\")");}
	catch (PQLSyntaxError e) {REQUIRE(false);}
	catch (PQLSemanticError e) { REQUIRE(true); }

	try {preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(11,a1)");}
	catch (PQLSyntaxError e) {REQUIRE(false);}
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(11,_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(11,\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(_,_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(_,a1)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(_,\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }

	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(\"x\",_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(\"x\",a1)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Uses(\"x\",\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	
}
TEST_CASE("PQLSyntaxChecker positive test 10: Modifies valid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(a1,_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(a1,a2)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(a1,\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(11,a1)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(11,_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(11,\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(_,_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(_,a1)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(_,\"x\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(\"x\",_)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(\"x\",a1)"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
	try { preprocessor.preprocess("assign a1, a2; Select a1 such that Modifies(\"x\",\"y\")"); }
	catch (PQLSyntaxError e) { REQUIRE(false); }
	catch (PQLSemanticError e) { REQUIRE(true); }
}

TEST_CASE("PQLSyntaxChecker negative test 1: assigns") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assigns a; Select a such that Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 2: a)") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a); Select a such that Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 3 : no ;") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a Select a such that Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 4 : select") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; select a such that Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 5: *&^") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select *&^ such that Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 6: such tha") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such tha Follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 7: follows") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that follows(a, 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 8: ; in the end") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11);"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 9: ';' in left arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Follows(';', 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 10: no )") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 11: Follows left input type") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Follows(\"a\", 11)"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 12: Follows right input type") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Follows(a, \"x\")"), PQLSyntaxError);
}
TEST_CASE("PQLSyntaxChecker negative test 13: Uses right input type") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a such that Uses(a, 11)"), PQLSyntaxError);
}

TEST_CASE("PQLSyntaxChecker negative test 14: pattern clause assign comma") {
    PQLPreprocessor preprocessor;
    Query query;
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a; Select a pattern a (_,_,_)"), PQLSyntaxError);
}

TEST_CASE("PQLSyntaxChecker negative test 15: pattern clause while") {
    PQLPreprocessor preprocessor;
    Query query;
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("while w; Select w pattern w (_,_,_)"), PQLSyntaxError);
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("while w; Select w pattern w (_,\"x\")"), PQLSyntaxError);
}

TEST_CASE("PQLSyntaxChecker negative test 16: pattern clause if") {
    PQLPreprocessor preprocessor;
    Query query;
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("if i; Select i pattern i (_,_)"), PQLSyntaxError);
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("if i; Select i pattern i (_,_,\"x\")"), PQLSyntaxError);
    REQUIRE_THROWS_AS(query = preprocessor.preprocess("if i; Select i pattern i (_,\"t\",\"x\")"), PQLSyntaxError);
}

TEST_CASE("PQLSyntaxChecker positive test 17: Calls invalid arg") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(p1, 11)"), PQLSyntaxError);
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(11, p1)"), PQLSyntaxError);
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("procedure p1, p2; Select p1 such that Calls(11, !@#)"), PQLSyntaxError);
}