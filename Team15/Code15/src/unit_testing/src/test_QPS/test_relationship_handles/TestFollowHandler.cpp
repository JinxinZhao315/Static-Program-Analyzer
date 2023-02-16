#include "PKB.h"
#include "QPS/include/PQLDriver.h"

#include "catch.hpp"

string testFollows(string queryStr, PKB& pkb);

string testFollows(string queryStr, PKB& pkb) {
    PQLDriver driver = PQLDriver(pkb);
    string retStr = driver.processPQL(queryStr);
    return retStr;
}

TEST_CASE("Follows* test")
{
    try
    {
        PKB pkb;

        pkb.addStmt("read", 1);
        pkb.addStmt("read", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

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

        pkb.addStmt("read", 1);
        pkb.addStmt("read", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

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
        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

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