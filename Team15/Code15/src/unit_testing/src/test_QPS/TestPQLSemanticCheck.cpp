#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Query.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("PQLSemanticChecker positive test 1") {
	PQLPreprocessor preprocessor;
	REQUIRE_NOTHROW(preprocessor.preprocess("assign a; Select a such that Follows(a, 11)"));
}

TEST_CASE("PQLSemanticChecker negative test 1: undefined syn") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("assign a; Select a1 such that Follows(a, 11)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("assign a; Select a such that Follows(a2, 11)"), PQLSemanticError);

}
TEST_CASE("PQLSemanticChecker negative test 2: repeated syn a") {
	PQLPreprocessor preprocessor;
	Query query;
	REQUIRE_THROWS_AS(query = preprocessor.preprocess("assign a, a; Select a such that Follows(a, 11)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 3: Uses invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("variable v; Select v such that Uses(v, \"x\")"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 4: Uses invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("assign a1, a2; variable v; Select v such that Uses(a1, a2)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 5: Follows invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows(v, 11)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows(p, 11)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 6: Follows invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows(11, v)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows(11, p)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 7: Follows* invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows*(v, 11)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows*(p, 11)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 8: Follows* invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows*(11, v)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Follows*(11, p)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 9: Modifies invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("variable v; Select v such that Modifies(v, \"x\")"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 10: Modifies invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("assign a1, a2; variable v; Select v such that Modifies(a1, a2)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 11: Parent invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent(v, 11)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent(p, 11)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 12: Parent invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent(11, v)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent(11, p)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 13: Parent* invalid left type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent*(v, 11)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent*(p, 11)"), PQLSemanticError);
}
TEST_CASE("PQLSemanticChecker negative test 14: Parent* invalid right type") {
	PQLPreprocessor preprocessor;
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent*(11, v)"), PQLSemanticError);
	REQUIRE_THROWS_AS(preprocessor.preprocess("procedure p; assign a1, a2; variable v; Select a such that Parent*(11, p)"), PQLSemanticError);
}