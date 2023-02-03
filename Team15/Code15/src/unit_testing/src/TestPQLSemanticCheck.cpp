//#include "PQLPreprocessor.h"
//#include "Query.h"
//#include "exceptions/PQLSyntaxError.h"
//#include "exceptions/PQLSemanticError.h"
//
//#include "catch.hpp"
//
//using namespace std;
//
//TEST_CASE("PQLSemanticCheck test 1") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors: assigns" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 2") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a); Select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors a)" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 3") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a; select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors select" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 4") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a; Select a such that Follow(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors Follow" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 5") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a; Select a such that Follows ( a ,  11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors Follows ( a ,  11)" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 6") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assigns a; Select a such that Follows(a, 1*1)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors 1*1" << endl;
//	}
//}
//TEST_CASE("PQLPreprocessor test 7") {
//
//	PQLPreprocessor preprocessor;
//	Query query;
//	try {
//		query = preprocessor.preprocess("assign a; read r1, r2, r3; stmt s; Select a such that Follows(a, 11)");
//		cout << "syntax correct" << endl;
//	}
//	catch (PQLSyntaxError e) {
//		cout << "syntax errors: assigns" << endl;
//	}
//}