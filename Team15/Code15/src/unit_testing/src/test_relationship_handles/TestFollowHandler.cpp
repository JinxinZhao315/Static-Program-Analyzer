#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/SelectHandler.h"
#include "PKBStub.h"
#include "Tokens.h"
#include "Query.h"
#include "PQLPreprocessor.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Follows Handler test int, _") {
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

        Query query1 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(4,_)");
        Query query2 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(1,_)");

        SelectClause selectClause = query1.getSelectClause();
        SelectHandler selectHandler = SelectHandler(pkb);
        std::string selectedVarName = selectHandler.evalSelect(selectClause, query1.getVarTable(), resultTable);// update resultTable and return the synonym name
        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;

        SuchThatClause suchThatClause = query1.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query1.getVarTable());
        
        followsHandler.combineResult(resultTable, followResult);
        std::set<std::string> result = resultTable.getValueFromKey(selectedVarName);
        std::set<std::string> expectedResult{"5"};
        REQUIRE(result == expectedResult);
        resultTable = ResultTable();

        //selectClause = query2.getSelectClause();
        //selectHandler = SelectHandler(pkb);
        //selectedVarName = selectHandler.evalSelect(selectClause, query2.getVarTable(), resultTable);// update resultTable and return the synonym name
        //followsHandler = FollowsHandler(pkb);
        //isStar = false;
        //suchThatClause = query2.getSuchThatClauseVec()[0];
        //followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query2.getVarTable());
        //followsHandler.combineResult(resultTable, followResult);
        //result = resultTable.getValueFromKey(selectedVarName);
        //expectedResult = {"3", "4", "5"};
        //REQUIRE(result == expectedResult);
        //resultTable = ResultTable();

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

//TEST_CASE("Follows Handler test int , _") {
//    try {
//        ResultTable resultTable = ResultTable();
//        PQLPreprocessor preprocessor;
//        PKB pkb;
//        PQLEvaluator evaluator = PQLEvaluator(pkb);
//
//        pkb.addFollows(2, 3);
//        pkb.addFollows(1, 2);
//        pkb.addFollows(3, 4);
//        pkb.addFollows(4, 5);
//
//        pkb.addStmt(Tokens::READ, 1);
//        pkb.addStmt(Tokens::CALL, 2);
//        pkb.addStmt(Tokens::READ, 3);
//        pkb.addStmt(Tokens::READ, 4);
//        pkb.addStmt(Tokens::READ, 5);
//        Query query1 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(10,_)");
//        Query query2 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(10,_)");
//        Query query3 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(10,_)");
//        Query query4 = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(10,_)");
//
//        SelectClause selectClause = query1.getSelectClause();
//        SelectHandler selectHandler = SelectHandler(pkb);
//        std::string selectedVarName = selectHandler.evalSelect(selectClause, query1.getVarTable(), resultTable);// update resultTable and return the synonym name
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        bool isStar = false;
//        SuchThatClause suchThatClause = query1.getSuchThatClauseVec()[0];
//        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query1.getVarTable());
//        followsHandler.combineResult(resultTable, followResult);
//
//        std::set<std::string> result = resultTable.getValueFromKey("s1");
//        std::set<std::string> expectedResult{ "1", "3" , "4", "5" };
//        REQUIRE(result == expectedResult);
//
//
//
//        selectClause = query2.getSelectClause();
//        SelectClause selectClause = query2.getSelectClause();
//        SelectHandler selectHandler = SelectHandler(pkb);
//        std::string selectedVarName = selectHandler.evalSelect(selectClause, query2.getVarTable(), resultTable);// update resultTable and return the synonym name
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        bool isStar = false;
//        SuchThatClause suchThatClause = query2.getSuchThatClauseVec()[0];
//        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query2.getVarTable());
//        followsHandler.combineResult(resultTable, followResult);
//
//        std::set<std::string> result = resultTable.getValueFromKey("s1");
//        std::set<std::string> expectedResult{ "1", "3" , "4", "5" };
//        REQUIRE(result == expectedResult);
//
//
//
//        selectClause = query3.getSelectClause();
//        SelectClause selectClause = query3.getSelectClause();
//        SelectHandler selectHandler = SelectHandler(pkb);
//        std::string selectedVarName = selectHandler.evalSelect(selectClause, query3.getVarTable(), resultTable);// update resultTable and return the synonym name
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        bool isStar = false;
//        SuchThatClause suchThatClause = query3.getSuchThatClauseVec()[0];
//        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query3.getVarTable());
//        followsHandler.combineResult(resultTable, followResult);
//
//        std::set<std::string> result = resultTable.getValueFromKey("s1");
//        std::set<std::string> expectedResult{ "1", "3" , "4", "5" };
//        REQUIRE(result == expectedResult);
//
//
//
//        selectClause = query2.getSelectClause();
//        SelectClause selectClause = query4.getSelectClause();
//        SelectHandler selectHandler = SelectHandler(pkb);
//        std::string selectedVarName = selectHandler.evalSelect(selectClause, query4.getVarTable(), resultTable);// update resultTable and return the synonym name
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        bool isStar = false;
//        SuchThatClause suchThatClause = query4.getSuchThatClauseVec()[0];
//        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query4.getVarTable());
//        followsHandler.combineResult(resultTable, followResult);
//
//        std::set<std::string> result = resultTable.getValueFromKey("s1");
//        std::set<std::string> expectedResult{ "1", "3" , "4", "5" };
//        REQUIRE(result == expectedResult);
//
//        std::cout << "select handler successful" << std::endl;
//    }
//    catch (exception e) {
//        std::cout << "exception occured!";
//    }
//}
//
//TEST_CASE("Follows Handler WildCard Synonym test") {
//    try {
//        ResultTable resultTable = ResultTable();
//        PQLPreprocessor preprocessor;
//        PKB pkb;
//        PQLEvaluator evaluator = PQLEvaluator(pkb);
//
//        Query query = Query();
//        pkb.addFollows(2, 3);
//        pkb.addFollows(1, 2);
//        pkb.addFollows(3, 4);
//        pkb.addFollows(4, 5);
//
//        pkb.addStmt(Tokens::READ, 1);
//        pkb.addStmt(Tokens::CALL, 2);
//        pkb.addStmt(Tokens::READ, 3);
//        pkb.addStmt(Tokens::READ, 4);
//        pkb.addStmt(Tokens::READ, 5);
//        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,s1)");
//
//        FollowsHandler followsHandler = FollowsHandler(pkb);
//        bool isStar = false;
//        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
//        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, query.getVarTable());
//        followsHandler.combineResult(resultTable, followResult);
//
//        std::set<std::string> result = resultTable.getValueFromKey("s1");
//        std::set<std::string> expectedResult{ "3" , "4", "5" };
//        REQUIRE(result == expectedResult);
//
//        std::cout << "select handler successful" << std::endl;
//    }
//    catch (exception e) {
//        std::cout << "exception occured!";
//    }
//}

