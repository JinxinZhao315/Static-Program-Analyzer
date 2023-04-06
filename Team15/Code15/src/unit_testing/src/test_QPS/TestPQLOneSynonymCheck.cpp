#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Query.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"

#include "catch.hpp"

using namespace std;


//TEST_CASE("PQLOneSynonym test 1") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a); Select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors a) found, PQLOneSynonym test 1 passed" << endl;
//	}
//}
//TEST_CASE("PQLOneSynonym test 2") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax error select found, PQLOneSynonym test 2 passed" << endl;
//	}
//}
//TEST_CASE("PQLOneSynonym test 3") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; Select a such that Follow(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax error Follow found, PQLOneSynonym test 3 passed" << endl;
//	}
//}
//TEST_CASE("PQLOneSynonym test 4") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; Select a such that Follows ( a ,  11)");
//		cout << "syntax correct, PQLOneSynonym test 4 passed" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "no syntax error, PQLOneSynonym test 4 failed" << endl;
//	}
//}
//TEST_CASE("PQLOneSynonym test 5") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a; Select a such that Follows(a, 1*1)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax error 1*1 found, PQLOneSynonym test 5 failed" << endl;
//	}
//}
//TEST_CASE("PQLOneSynonym test 6") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; read r1, r2, r3; stmt s; Select a such that Follows(a, 11)");
//		cout << "syntax correct, PQLOneSynonym test 6 passed" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "No syntax error, PQLOneSynonym test 6 failed" << endl;
//	}
//}