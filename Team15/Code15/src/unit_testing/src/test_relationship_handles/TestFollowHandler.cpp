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

TEST_CASE("Follows Handler test 1") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(4, 5);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(s1,5)");
        /*Query query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(5,_)");
        Query query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(1, 2)");
        Query query = preprocessor.preprocess("stmt s1; stmt s2; Select s1 such that Follows(s1,s2)");*/


        SelectHandler selectHandler = SelectHandler(pkb);
        multimap<string, string> varTable = query.getVarTable();
        std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);// update resultTable and return the synonym name

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        REQUIRE(selectedVarName == "s1");
        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{ "4" };
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
        multimap<string, string> varTable = query.getVarTable();
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollowsStar(isStar, suchThatClause, resultTable, varTable);
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

