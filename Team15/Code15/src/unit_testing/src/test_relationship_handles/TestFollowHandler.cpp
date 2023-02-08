#include "PKB.h"
#include "QPS/PQLEvaluator.h"
#include "QPS/PQLPreprocessor.h"
#include "QPS/relationship_handlers/Result.h"
#include "QPS/relationship_handlers/ResultTable.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
#include "QPS/relationship_handlers/SelectHandler.h"
#include "QPS/relationship_handlers/ClauseHandler.h"

#include "PKBStub.h"
#include <assert.h>
#include "catch.hpp"

using namespace std;

//TEST_CASE("FollowsHandler Test 1") {
//    //try {
//    //    PQLPreprocessor preprocessor;
//    //    Query query = Query();
//
//    //    query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,_)");
//
//    //    std::multimap<std::string, std::string> synonymTable = query.getSynonymTable();
//    //    string type = synonymTable.find("s1")->second;
//    //    assert(type == "stmt");
//    //    std::cout << "var table correct" << std::endl;
//
//    //    SelectClause selectClause = query.getSelectClause();
//    //    string varName = selectClause.getVarName();
//    //    assert(varName == "s1");
//    //    std::cout << "select correct" << std::endl;
//
//    //    vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
//    //    for (SuchThatClause cl : suchThatClauseVec) {
//    //        string relationship = cl.getRelationShip();
//    //        string leftArg = cl.getLeftArg();
//    //        string rightArg = cl.getRightArg();
//    //        assert(relationship == "Follows");
//    //        std::cout << "relationship correct" << std::endl;
//    //        assert(leftArg == "_");
//    //        std::cout << "leftArg correct" << std::endl;
//    //        assert(rightArg == "_");
//    //        std::cout << "rightArg correct" << std::endl;
//    //    }
//    //    std::cout << "FollowHandler Test 1 syntax correct" << std::endl;
//
//    //    
//    //}
//    //catch (PQLSyntaxError e) {
//    //    std::cout << "FollowHandler Test 1 syntax should be correct, but syntax checker give error!" << std::endl;
//    //}
//
//
//
//    try {
//        std::cout << "hello" << std::endl;
//        SuchThatClause suchThatClause = SuchThatClause();
//        std::multimap<std::string, std::string> synonymTable;
//        ResultTable resultTable = ResultTable();
//
//        synonymTable.insert(pair<std::string, std::string>("a1", "assign"));
//        synonymTable.insert(pair<std::string, std::string>("a2", "assign"));
//        synonymTable.insert(pair<std::string, std::string>("r", "read"));
//        synonymTable.insert(pair<std::string, std::string>("i", "if"));
//        synonymTable.insert(pair<std::string, std::string>("w", "while"));
//        synonymTable.insert(pair<std::string, std::string>("c", "constant"));
//        synonymTable.insert(pair<std::string, std::string>("ca", "call"));
//        synonymTable.insert(pair<std::string, std::string>("p", "procedure"));
//
//        //std::set<std::string> constSet{ "10", "11", "12", "13" };
//        //std::set<std::string> varNameSet{ "x", "y", "z" };
//        //std::set<int> stmtNumberByType{ 1, 2, 3 };
//        //std::set<int> stmtNums{ 1, 2, 3 };
//
//        //PKB pkb = PKBStub(constSet, varNameSet, stmtNumberByType, stmtNums);
//        PKB pkb;
//
//        pkb.addProc("p");
//        pkb.addStmt(Tokens::ASSIGN, 1);
//        pkb.addStmt(Tokens::ASSIGN, 2);
//        pkb.addStmt(Tokens::READ, 3);
//        pkb.addStmt(Tokens::IF, 4);
//        pkb.addStmt(Tokens::WHILE, 5);
//        pkb.addStmt(Tokens::CALL, 6);
//        pkb.addVar("x");
//        pkb.addVar("y");
//        pkb.addVar("z");
//        pkb.addConst("10");
//        pkb.addConst("11");
//        pkb.addConst("12");
//        pkb.addConst("13");
//
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        /*std::string selectedVarName = followsHandler.evalFollows(false, SuchThatClause , synonymTable , resultTable );*/// update resultTable and return the synonym name
//
//        //REQUIRE(assert(selectedVarName == "r");
//        std::set<std::string> result = resultTable.getValueFromKey("r");
//        for (auto s : result) {
//            std::cout << s << "\n" << endl;
//        }
//
//        std::cout << "select handler successful" << std::endl;
//    }
//    catch (exception e) {
//        std::cout << "exception occured!";
//    }
//}


TEST_CASE("Follows Handler Synonym Integer test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(4, 5);
        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::READ, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(s1,5)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "4" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Integer Synonym test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(1, 2);
        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::READ, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(1,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "2" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Synonym Synonym test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(c1,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "3" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Synonym test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);
 
        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "3" , "4", "5"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Synonym WildCard test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);

        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(s1,_)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "1" , "4", "3" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Integer WildCard test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);

        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(1,_)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "1" , "4", "3" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Integer test") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();

        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);


        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,1)");


        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");

        std::set<std::string> expectedResult{ "1"};


        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Synonym test 2") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        multimap<string, string> varTable = query.getSynonymTable();
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "3" , "4", "5" };
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

