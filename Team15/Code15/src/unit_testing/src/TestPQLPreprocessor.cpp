#include "PQLPreprocessor.h"
//#include "PQLDriver.h"

#include "catch.hpp"

#pragma once

using namespace std;

TEST_CASE("PQLPreprocessor test syntax cheker 1") {
	try {
		PQLPreprocessor preprocessor;
		Query query = Query();
		//preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");

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
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors a)" << endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 3") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; select a such that Follows(a, 11)");
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors select" << endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 4") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follow(a, 11)");
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors Follow" << endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 5") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follows ( a ,  11)");
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors Follows ( a ,  11)" << endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 6") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assigns a; Select a such that Follows(a, 1*1)");
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors 1*1" << endl;
	}
}

TEST_CASE("PQLPreprocessor test syntax cheker 7") {

	PQLPreprocessor preprocessor;
	Query query;
	try {
		query = preprocessor.preprocess("assign a; read r1, r2, r3; stmt s; Select a such that Follows(a, 11)");
		cout << "syntax correct" << endl;
	}
	catch (PQLSyntaxError e) {
		cout << "syntax errors: assigns" << endl;
	}
}

TEST_CASE("PQLPreprocessor test semantic checker 1") {
	try {
		PQLPreprocessor preprocessor;
		Query query = Query();
		//preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");

		query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");
		std::cout << "syntax correct" << std::endl;
	}

	catch (PQLSemanticError e) {
		std::cout << "semantic errors: assigns" << std::endl;
	}
}