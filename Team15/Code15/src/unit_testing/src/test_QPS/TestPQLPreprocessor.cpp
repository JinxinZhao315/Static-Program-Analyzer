#include "QPS/include/tokenizer/PQLPreprocessor.h"
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
        string varName = selectClause.getSynNameVec()[0].getSynName();
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
        string varName = selectClause.getSynNameVec()[0].getSynName();
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
        string varName = selectClause.getSynNameVec()[0].getSynName();
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
    string varName = selectClause.getSynNameVec()[0].getSynName();
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
    string varName = selectClause.getSynNameVec()[0].getSynName();
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
    string varName = selectClause.getSynNameVec()[0].getSynName();
    REQUIRE(varName == "w");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    for (PatternClause cl : patternClauseVec) {
        REQUIRE(cl.getPatternSynonym() == "w");
        REQUIRE(cl.getFirstArg() == "v");
        REQUIRE(cl.getSecondArg() == "_");
        REQUIRE(cl.getThirdArg() == "");
    }
}

TEST_CASE("PQLPreprocessor multi clause") {
    PQLPreprocessor preprocessor;
    string str = "assign a; Select a such that Follows(a,10) such that Uses(a, \"x\") pattern a (\"y\",_)";
    Query query = preprocessor.preprocess(str);

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    string type = varTable.find("a")->second;
    REQUIRE(type == "assign");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    REQUIRE(patternClauseVec.size() == 1);
    REQUIRE(suchThatClauseVec.size() == 2);

    PatternClause pcl = patternClauseVec[0];
    REQUIRE(pcl.getPatternSynonym() == "a");
    REQUIRE(pcl.getFirstArg() == "\"y\"");
    REQUIRE(pcl.getSecondArg() == "_");

    SuchThatClause scl1 = suchThatClauseVec[0];
    REQUIRE(scl1.getRelationShip() == "Follows");
    REQUIRE(scl1.getLeftArg() == "a");
    REQUIRE(scl1.getRightArg() == "10");

    SuchThatClause scl2 = suchThatClauseVec[1];
    REQUIRE(scl2.getRelationShip() == "Uses");
    REQUIRE(scl2.getLeftArg() == "a");
    REQUIRE(scl2.getRightArg() == "\"x\"");
}

TEST_CASE("PQLPreprocessor multi clause with and") {
    PQLPreprocessor preprocessor;
    string str = "assign a; Select a such that Follows(a,10) and Uses(a, \"x\") pattern a (\"y\",_) and a(_, \"xyz\")";
    Query query = preprocessor.preprocess(str);

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    string type = varTable.find("a")->second;
    REQUIRE(type == "assign");

    vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    REQUIRE(patternClauseVec.size() == 2);
    REQUIRE(suchThatClauseVec.size() == 2);

    PatternClause pcl = patternClauseVec[0];
    REQUIRE(pcl.getPatternSynonym() == "a");
    REQUIRE(pcl.getFirstArg() == "\"y\"");
    REQUIRE(pcl.getSecondArg() == "_");
    REQUIRE(pcl.getThirdArg() == "");

    PatternClause pcl2 = patternClauseVec[1];
    REQUIRE(pcl2.getPatternSynonym() == "a");
    REQUIRE(pcl2.getFirstArg() == "_");
    REQUIRE(pcl2.getSecondArg() == "\"xyz\"");
    REQUIRE(pcl.getThirdArg() == "");

    SuchThatClause scl1 = suchThatClauseVec[0];
    REQUIRE(scl1.getRelationShip() == "Follows");
    REQUIRE(scl1.getLeftArg() == "a");
    REQUIRE(scl1.getRightArg() == "10");

    SuchThatClause scl2 = suchThatClauseVec[1];
    REQUIRE(scl2.getRelationShip() == "Uses");
    REQUIRE(scl2.getLeftArg() == "a");
    REQUIRE(scl2.getRightArg() == "\"x\"");
}

TEST_CASE("PQLPreprocessor multi clause with and negative test") {
    PQLPreprocessor preprocessor;
    string str1 = "assign a; while w; Select a such that Parent* (w, a) and Modifies (a, \"x\") and such that Next* (1, a)";
    REQUIRE_THROWS_AS(preprocessor.preprocess(str1), PQLSyntaxError);

    string str2 = "assign a; while w; Select a such that Parent* (w, a) and pattern a (\"x\", _) such that Next* (1, a))";
    REQUIRE_THROWS_AS(preprocessor.preprocess(str2), PQLSyntaxError);

    string str3 = "assign a; while w; Select a such that Parent* (w, a) pattern a (\"x\", _) and Next* (1, a)";
    REQUIRE_THROWS_AS(preprocessor.preprocess(str3), PQLSyntaxError);
}

TEST_CASE("PQLPreprocessor with clause") {
    PQLPreprocessor preprocessor;

    std::string str1 = "assign a1, a2; Select a1 with a1.stmt# = a2.stmt#";
    Query query1 = preprocessor.preprocess(str1);
    WithClause withCl1 = query1.getWithClauseVec()[0];
    
    REQUIRE(withCl1.isFirstArgAttrRef() == true);
    REQUIRE(withCl1.getFirstArgAttrRef().getSynName() == "a1");
    REQUIRE(withCl1.getFirstArgAttrRef().getAttrName() == "stmt#");

    REQUIRE(withCl1.isSecondArgAttrRef() == true);
    REQUIRE(withCl1.getSecondArgAttrRef().getSynName() == "a2");
    REQUIRE(withCl1.getSecondArgAttrRef().getAttrName() == "stmt#");


    std::string str2 = "assign a1, a2; procedure p1; Select a1 with a1.stmt# = p1.procName";
    REQUIRE_THROWS_AS(preprocessor.preprocess(str2), PQLSemanticError);
}
