#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "exceptions/PQLSemanticError.h"
#include "exceptions/PQLSyntaxError.h"
#include "QPS/include/tokenizer/QueryTokenizer.h"
#include "QPS/include/tokenizer/PQLSemanticCheck.h"

#include <assert.h>
#include "catch.hpp"

using namespace std;

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

TEST_CASE("PQLPreprocessor query object test pattern 1") {

    PQLPreprocessor preprocessor;
    Query query = Query();

    query = preprocessor.preprocess("assign a; Select a pattern a (_,_\"x\"_)");

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    string type = varTable.find("a")->second;
    REQUIRE(type == "assign");

    SelectClause selectClause = query.getSelectClause();
    string varName = selectClause.getVarName();
    REQUIRE(varName == "a");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    for (PatternClause cl : patternClauseVec) {
        REQUIRE(cl.getPatternSynonym() == "a");
        REQUIRE(cl.getFirstArg() == "_");
        REQUIRE(cl.getSecondArg() == "_\"x\"_");
        REQUIRE(cl.getThirdArg() == "");
    }

}

TEST_CASE("PQLPreprocessor query object test pattern if 1") {

    PQLPreprocessor preprocessor;

    Query query = preprocessor.preprocess("if ifs; variable v; Select ifs pattern ifs (v,_,_)");
    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    string type = varTable.find("ifs")->second;
    REQUIRE(type == "if");
    string type2 = varTable.find("v")->second;
    REQUIRE(type2 == "variable");

    SelectClause selectClause = query.getSelectClause();
    string varName = selectClause.getVarName();
    REQUIRE(varName == "ifs");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    for (PatternClause cl : patternClauseVec) {
        REQUIRE(cl.getPatternSynonym() == "ifs");
        REQUIRE(cl.getFirstArg() == "v");
        REQUIRE(cl.getSecondArg() == "_");
        REQUIRE(cl.getThirdArg() == "_");
    }
}

TEST_CASE("PQLPreprocessor query object test while 1") {

    PQLPreprocessor preprocessor;

    Query query = preprocessor.preprocess("while w; variable v; Select w pattern w (v,_)");
    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    string type = varTable.find("w")->second;
    REQUIRE(type == "while");
    string type2 = varTable.find("v")->second;
    REQUIRE(type2 == "variable");

    SelectClause selectClause = query.getSelectClause();
    string varName = selectClause.getVarName();
    REQUIRE(varName == "w");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    for (PatternClause cl : patternClauseVec) {
        REQUIRE(cl.getPatternSynonym() == "w");
        REQUIRE(cl.getFirstArg() == "v");
        REQUIRE(cl.getSecondArg() == "_");
        REQUIRE(cl.getThirdArg() == "");
    }
}
