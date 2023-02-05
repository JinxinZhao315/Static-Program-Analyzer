#include "PQLPreprocessor.h"
#include "PQLSyntaxChecker.h"
#include "exceptions/PQLSemanticError.h"
#include "exceptions/PQLSyntaxError.h"
#include <assert.h>

#include "catch.hpp"

using namespace std;


TEST_CASE("PQLPreprocessor test syntax cheker 1") {
	try {
		PQLPreprocessor preprocessor;
		Query query = Query();

		query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 2") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a); Select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors a)" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 3") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors select" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 4") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follow(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors Follow" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 5") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follows ( a ,  11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors Follows ( a ,  11)" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 6") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follows(a, 1*1)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors 1*1" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 7") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assign a; read r1, r2, r3; stmt s; Select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e) {
		std::cout << "syntax errors: assigns" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test semantic checker 1") {
	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assign a; Select a1 such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e1) {
		std::cout << "syntax should not give errors" << std::endl;
	}
	catch (PQLSemanticError e2) {
		std::cout << "semantic errors: a1 not found" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test semantic checker 2") {
	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assign a; Select a such that Follows(a2, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e1) {
		std::cout << "syntax should not give errors" << std::endl;
	}
	catch (PQLSemanticError e2) {
		std::cout << "semantic errors: a2 not found" << std::endl;
	}
}

TEST_CASE("PQLPreprocessor test semantic checker 3") {
	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assign a, a; Select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}
	catch (PQLSyntaxError e1) {
		std::cout << "syntax should not give errors" << std::endl;
	}
	catch (PQLSemanticError e2) {
		std::cout << "semantic errors: a repeated" << std::endl;
	}
}