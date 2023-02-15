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

string testFollows(string queryStr, PKB& pkb);

string testFollows(string queryStr, PKB& pkb) {
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator = PQLEvaluator(pkb);
    Query query = preprocessor.preprocess(queryStr);
    string retStr = evaluator.evaluate(query);
    return retStr;
}

TEST_CASE("Follows* test")
{
    try
    {
        PKB pkb;

        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::READ, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);

        pkb.addFollows(1, 2);
        pkb.addFollows(2, 3);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        pkb.addFollowsStar(1, set<int>({2,3,4,5}));
        pkb.addFollowsStar(2, set<int>({3,4,5}));
        pkb.addFollowsStar(3, set<int>({4,5}));
        pkb.addFollowsStar(4, set<int>({5}));

        // Synon-int
        string retStr = testFollows("read s1; Select s1 such that Follows*(s1, 5)", pkb);
        std::cout << retStr << std::endl;
        REQUIRE(retStr == "1,2,3,4");

        // Int-synon
        string retStr1 = testFollows("read s1; Select s1 such that Follows*(1,s1)", pkb);
        std::cout << retStr1 << std::endl;
        REQUIRE(retStr1 == "2,3,4,5");

        // (int,_)
        string retStr2 = testFollows("read s1; Select s1 such that Follows*(4, _)", pkb);
        std::cout << retStr2 << std::endl;
        REQUIRE(retStr2 == "1,2,3,4,5");

        string retStr3 = testFollows("read s1; Select s1 such that Follows*(5, _)", pkb);
        std::cout << retStr3 << std::endl;
        REQUIRE(retStr3 == "None");

        //(int, int)
        string retStr4 = testFollows("read s1; Select s1 such that Follows*(4, 5)", pkb);
        std::cout << retStr4 << std::endl;
        REQUIRE(retStr4 == "1,2,3,4,5");

        string retStr5 = testFollows("read s1; Select s1 such that Follows*(5,4)", pkb);
        std::cout << retStr5 << std::endl;
        REQUIRE(retStr5 == "None");

        //WC-Synon
        string retStr6 = testFollows("read s1; call c1; Select s1 such that Follows*(_,s1)", pkb);
        std::cout << retStr6 << std::endl;
        REQUIRE(retStr6 == "2,3,4,5");

        string retStr7 = testFollows("read s1; call c1; Select s1 such that Follows*(s1,_)", pkb);
        std::cout << retStr7 << std::endl;
        REQUIRE(retStr7 == "1,2,3,4");

        // Synon-Synon
        string retStr8 = testFollows("read s1, s2; Select s1 such that Follows*(s1,s2)", pkb);
        std::cout << retStr8 << std::endl;
        REQUIRE(retStr8 == "1,2,3,4");

        string retStr9 = testFollows("read s1, s2; Select s2 such that Follows*(s1,s2)", pkb);
        std::cout << retStr9 << std::endl;
        REQUIRE(retStr9 == "2,3,4,5");

    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Follows test 1")
{
    try
    {

        PKB pkb;

        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::READ, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);

        pkb.addFollows(1, 2);
        pkb.addFollows(2, 3);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);

        // (_, int)
        string retStr1 = testFollows("read s1; Select s1 such that Follows(_,3)", pkb);
        std::cout << retStr1 << std::endl;
        REQUIRE(retStr1 == "1,2,3,4,5");

        // (int,_)
        string retStr2 = testFollows("read s1; Select s1 such that Follows(4, _)", pkb);
        std::cout << retStr2 << std::endl;
        REQUIRE(retStr2 == "1,2,3,4,5");

        string retStr3 = testFollows("read s1; Select s1 such that Follows(5, _)", pkb);
        std::cout << retStr3 << std::endl;
        REQUIRE(retStr3 == "None");

        //(int, int)
        string retStr4 = testFollows("read s1; Select s1 such that Follows(4, 5)", pkb);
        std::cout << retStr4 << std::endl;
        REQUIRE(retStr4 == "1,2,3,4,5");

        string retStr5 = testFollows("read s1; Select s1 such that Follows(5,4)", pkb);
        std::cout << retStr5 << std::endl;
        REQUIRE(retStr5 == "None");

        //Synon-int
        string retStr6 = testFollows("read s1; Select s1 such that Follows(s1,5)", pkb);
        std::cout << retStr6 << std::endl;
        REQUIRE(retStr6 == "4");

        string retStr7 = testFollows("read s1; Select s1 such that Follows(1,s1)", pkb);
        std::cout << retStr7 << std::endl;
        REQUIRE(retStr7 == "2");

        // Synon-Synon
        string retStr8 = testFollows("read s1, s2; Select s1 such that Follows(s1,s2)", pkb);
        std::cout << retStr8 << std::endl;
        REQUIRE(retStr8 == "1,2,3,4");

        string retStr9 = testFollows("read s1, s2; Select s2 such that Follows(s1,s2)", pkb);
        std::cout << retStr9 << std::endl;
        REQUIRE(retStr9 == "2,3,4,5");

    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}



TEST_CASE("Follows test 2")
{
    try
    {

        PKB pkb;

        pkb.addFollows(1, 2);
        pkb.addFollows(2, 3);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);
        pkb.addStmt(Tokens::READ, 1);
        pkb.addStmt(Tokens::CALL, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 4);
        pkb.addStmt(Tokens::READ, 5);

        //WC-Synon
        string retStr = testFollows("read s1; call c1; Select s1 such that Follows(_,s1)", pkb);
        std::cout << retStr << std::endl;
        REQUIRE(retStr == "3,4,5");

        string retStr3 = testFollows("read s1; call c1; Select s1 such that Follows(s1,_)", pkb);
        std::cout << retStr3 << std::endl;
        REQUIRE(retStr3 == "1,3,4");

        // Synon-Synon
        string retStr2 = testFollows("read s1; call c1; Select s1 such that Follows(c1,s1)", pkb);
        std::cout << retStr2 << std::endl;
        REQUIRE(retStr2 == "3");


        //Int-WC
        string retStr4 = testFollows("read s1; call c1; Select s1 such that Follows(1,_)", pkb);
        std::cout << retStr4 << std::endl;
        REQUIRE(retStr4 == "1,3,4,5");

        string retStr5 = testFollows("read s1; call c1; Select s1 such that Follows(_,1)", pkb);
        std::cout << retStr5 << std::endl;
        REQUIRE(retStr5 == "None");

    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}