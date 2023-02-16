#include "PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/evaluator/SelectHandler.h"
#include "QPS/include/evaluator/ClauseHandler.h"

#include "PKBStub.h"
#include <assert.h>
#include "catch.hpp"

using namespace std;

TEST_CASE("FollowsHandler (_ , int) test 1")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(_,1)");

        bool isStar = false;
        SelectHandler selectHandler = SelectHandler(pkb);
        multimap<string, string> varTable = query.getSynonymTable();
        std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);

        FollowsHandler followsHandler = FollowsHandler(pkb);
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        if (!followResult.isResultTrue())
        {
            result = {};
        }
        for (auto s : result)
        {
            std::cout << s << std::endl;
        }
        std::set<std::string> expectedResult{};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("FollowsHandler (_ , int) test 2")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(_,3)");

        SelectHandler selectHandler = SelectHandler(pkb);
        multimap<string, string> varTable = query.getSynonymTable();
        std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];

        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        if (!followResult.isResultTrue())
        {
            result = {};
        }
        std::set<std::string> expectedResult{};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("FollowsHandler (int , _) test 1")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(4, _)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"1", "2", "3", "4", "5"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("FollowsHandler (int , _) test 2")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(5, _)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        if (!followResult.isResultTrue())
        {
            result = {};
        }
        std::set<std::string> expectedResult{};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("FollowsHandler (int , int) test 1")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(4, 5)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        if (!followResult.isResultTrue())
        {
            result = {};
        }
        std::set<std::string> expectedResult{"1", "2", "3", "4", "5"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("FollowsHandler (int , int) test 2")
{
    try
    {
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
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(5, 4)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        if (!followResult.isResultTrue())
        {
            result = {};
        }
        std::set<std::string> expectedResult{};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Synonym Integer test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(4, 5);
        pkb.addStmt("read", 1);
        pkb.addStmt("read", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(s1,5)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"4"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Integer Synonym test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(1, 2);
        pkb.addStmt("read", 1);
        pkb.addStmt("read", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        query = preprocessor.preprocess("read s1; Select s1 such that Follows(1,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"2"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Synonym Synonym test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(c1,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"3"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Synonym test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);
 
        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"3", "4", "5"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Synonym WildCard test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(s1,_)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"1", "4", "3"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler Integer WildCard test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(1,_)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"1", "4", "3"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Integer test")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();

        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);


        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,1)");

        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        multimap<string, string> varTable = query.getSynonymTable();
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");

        std::set<std::string> expectedResult{"1"};

        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows Handler WildCard Synonym test 2")
{
    try
    {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        pkb.addFollows(2, 3);
        pkb.addFollows(1, 2);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        query = preprocessor.preprocess("read s1; call c1; Select s1 such that Follows(_,s1)");

        FollowsHandler followsHandler = FollowsHandler(pkb);
        bool isStar = false;
        multimap<string, string> varTable = query.getSynonymTable();
        SuchThatClause suchThatClause = query.getSuchThatClauseVec()[0];
        Result followResult = followsHandler.evalFollows(isStar, suchThatClause, resultTable, varTable);
        followsHandler.combineResult(resultTable, followResult);

        std::set<std::string> result = resultTable.getValueFromKey("s1");
        std::set<std::string> expectedResult{"3", "4", "5"};
        REQUIRE(result == expectedResult);

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}