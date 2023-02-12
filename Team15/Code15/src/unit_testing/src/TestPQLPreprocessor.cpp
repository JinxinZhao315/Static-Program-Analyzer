#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/tokenizer/PQLSyntaxChecker.h"
#include "exceptions/PQLSemanticError.h"
#include "exceptions/PQLSyntaxError.h"
#include <assert.h>
#include "QPS/include/tokenizer/QueryTokenizer.h"
#include "QPS/include/tokenizer/PQLSemanticCheck.h"

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

TEST_CASE("PQLPreprocessor test 2") {
    Query query = Query();
    std::multimap<std::string, std::string> varTable;
    SelectClause selectClause;
    SuchThatClause suchThatClause;
    PatternClause patternClause;
    QueryTokenizer tokenizer;
    PQLSemanticCheck semanticChecker;

    string input = "constant c; Select c";
    // Tokenize & syntax check
    std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
    varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
    query.addSynonymTable(varTable);
    tokenizer.tokenizeClauses(declarationClausePair.second, selectClause, suchThatClause, patternClause);
    query.addSelectClause(selectClause);
    query.addSuchThatClause(suchThatClause);
    query.addPatternClause(patternClause);

    // semantic check
    std::pair<bool,std::string> semanticCheckPair = semanticChecker.checkSemantics(query);
    bool isSemanticValid = semanticCheckPair.first;
    if (!isSemanticValid) {
        throw PQLSemanticError(semanticCheckPair.second);
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


TEST_CASE("PQLPreprocessor query object test 1") {
    try {
        PQLPreprocessor preprocessor;
        Query query = Query();

        query = preprocessor.preprocess("assign a; Select a such that Follows(a, 11)");

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        string type = varTable.find("a")->second;
        assert(type == "assign");

        SelectClause selectClause = query.getSelectClause();
        string varName = selectClause.getVarName();
        assert(varName == "a");

        vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
        for (SuchThatClause cl : suchThatClauseVec) {
            string relationship = cl.getRelationShip();
            string leftArg = cl.getLeftArg();
            string rightArg = cl.getRightArg();
            assert(relationship == "Follows");
            assert(leftArg == "a");
            assert(rightArg == "11");
        }
        std::cout << "syntax correct" << std::endl;
    }
    catch (PQLSyntaxError e) {
        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
    }
}

TEST_CASE("PQLPreprocessor query object test follows*(synon,_)") {
    try {
        PQLPreprocessor preprocessor;
        Query query = Query();

        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows*(s1,_)");

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        string type = varTable.find("s1")->second;
        assert(type == "stmt");
        std::cout << "var table correct" << std::endl;

        SelectClause selectClause = query.getSelectClause();
        string varName = selectClause.getVarName();
        assert(varName == "s1");
        std::cout << "select correct" << std::endl;

        vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
        for (SuchThatClause cl : suchThatClauseVec) {
            string relationship = cl.getRelationShip();
            string leftArg = cl.getLeftArg();
            string rightArg = cl.getRightArg();
            assert(relationship == "Follows*");
            std::cout << "relationship correct" << std::endl;
            assert(leftArg == "s1");
            std::cout << "leftArg correct" << std::endl;
            assert(rightArg == "_");
            std::cout << "rightArg correct" << std::endl;
        }
        std::cout << "syntax correct" << std::endl;
    }
    catch (PQLSyntaxError e) {
        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
    }
}

TEST_CASE("PQLPreprocessor query object test follows(_,_)") {
    try {
        PQLPreprocessor preprocessor;
        Query query = Query();

        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,_)");

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        string type = varTable.find("s1")->second;
        assert(type == "stmt");
        std::cout << "var table correct" << std::endl;

        SelectClause selectClause = query.getSelectClause();
        string varName = selectClause.getVarName();
        assert(varName == "s1");
        std::cout << "select correct" << std::endl;

        vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
        for (SuchThatClause cl : suchThatClauseVec) {
            string relationship = cl.getRelationShip();
            string leftArg = cl.getLeftArg();
            string rightArg = cl.getRightArg();
            assert(relationship == "Follows");
            std::cout << "relationship correct" << std::endl;
            assert(leftArg == "_");
            std::cout << "leftArg correct" << std::endl;
            assert(rightArg == "_");
            std::cout << "rightArg correct" << std::endl;
        }
        std::cout << "syntax correct" << std::endl;
    }
    catch (PQLSyntaxError e) {
        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
    }
}

TEST_CASE("PQLPreprocessor query object test with pattern 1") {
    try {
        PQLPreprocessor preprocessor;
        Query query = Query();

        query = preprocessor.preprocess("assign a; Select a pattern a (_,_\"x\"_)");

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        string type = varTable.find("a")->second;
        REQUIRE(type == "assign");
        std::cout << "type: " << type << std::endl;

        SelectClause selectClause = query.getSelectClause();
        string varName = selectClause.getVarName();
        REQUIRE(varName == "a");
        std::cout << "varName: " << varName << std::endl;

        vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
        for (PatternClause cl : patternClauseVec) {

            std::cout << "pattern synon: " << cl.getPatternSynonym() << endl;
            REQUIRE(cl.getPatternSynonym() == "a");

            std::cout << "left arg " << cl.getLeftArg() << endl;
            REQUIRE(cl.getLeftArg() == "_");

            std::cout << "right arg " << cl.getRightArg() << endl;
            REQUIRE(cl.getRightArg() == "_\"x\"_");
        }
    }
    catch (PQLSyntaxError e) {
        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
    }
}

