#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"



TEST_CASE("Follows* test")
{
    try
    {
        PKB pkb;

        // Synon-int
        string retStr = TestUtility::testDriver("read s1; Select s1 such that Follows*(s1, 5)", pkb);
        
        REQUIRE(retStr == "1,2,3,4");

        // Int-synon
        string retStr1 = TestUtility::testDriver("read s1; Select s1 such that Follows*(1,s1)", pkb);
        
        REQUIRE(retStr1 == "2,3,4,5");

        // (int,_)
        string retStr2 = TestUtility::testDriver("read s1; Select s1 such that Follows*(4, _)", pkb);
        
        REQUIRE(retStr2 == "1,2,3,4,5");

        string retStr3 = TestUtility::testDriver("read s1; Select s1 such that Follows*(5, _)", pkb);
        
        REQUIRE(retStr3 == "none");

        //(int, int)
        string retStr4 = TestUtility::testDriver("read s1; Select s1 such that Follows*(4, 5)", pkb);
        
        REQUIRE(retStr4 == "1,2,3,4,5");

        string retStr5 = TestUtility::testDriver("read s1; Select s1 such that Follows*(5,4)", pkb);
        
        REQUIRE(retStr5 == "none");

        //WC-Synon
        string retStr6 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows*(_,s1)", pkb);
        
        REQUIRE(retStr6 == "2,3,4,5");

        string retStr7 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows*(s1,_)", pkb);
        
        REQUIRE(retStr7 == "1,2,3,4");

        // Synon-Synon
        string retStr8 = TestUtility::testDriver("read s1, s2; Select s1 such that Follows*(s1,s2)", pkb);
        
        REQUIRE(retStr8 == "1,2,3,4");

        string retStr9 = TestUtility::testDriver("read s1, s2; Select s2 such that Follows*(s1,s2)", pkb);
        
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

        //do not add one by one to pkb
        /*
        pkb.addStmt("read", 1);
        pkb.addStmt("read", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);

        pkb.addFollows(1, 2);
        pkb.addFollows(2, 3);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);
        */

        // (_, int)
        string retStr1 = TestUtility::testDriver("read s1; Select s1 such that Follows(_,3)", pkb);
        
        REQUIRE(retStr1 == "1,2,3,4,5");

        // (int,_)
        string retStr2 = TestUtility::testDriver("read s1; Select s1 such that Follows(4, _)", pkb);
        
        REQUIRE(retStr2 == "1,2,3,4,5");

        string retStr3 = TestUtility::testDriver("read s1; Select s1 such that Follows(5, _)", pkb);
        
        REQUIRE(retStr3 == "none");

        //(int, int)
        string retStr4 = TestUtility::testDriver("read s1; Select s1 such that Follows(4, 5)", pkb);
        
        REQUIRE(retStr4 == "1,2,3,4,5");

        string retStr5 = TestUtility::testDriver("read s1; Select s1 such that Follows(5,4)", pkb);
        
        REQUIRE(retStr5 == "none");

        //Synon-int
        string retStr6 = TestUtility::testDriver("read s1; Select s1 such that Follows(s1,5)", pkb);
        
        REQUIRE(retStr6 == "4");

        string retStr7 = TestUtility::testDriver("read s1; Select s1 such that Follows(1,s1)", pkb);
        
        REQUIRE(retStr7 == "2");

        // Synon-Synon
        string retStr8 = TestUtility::testDriver("read s1, s2; Select s1 such that Follows(s1,s2)", pkb);
        
        REQUIRE(retStr8 == "1,2,3,4");

        string retStr9 = TestUtility::testDriver("read s1, s2; Select s2 such that Follows(s1,s2)", pkb);
        
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

        //do not add one by one to pkb
        /*
        pkb.addFollows(1, 2);
        pkb.addFollows(2, 3);
        pkb.addFollows(3, 4);
        pkb.addFollows(4, 5);
        pkb.addStmt("read", 1);
        pkb.addStmt("call", 2);
        pkb.addStmt("read", 3);
        pkb.addStmt("read", 4);
        pkb.addStmt("read", 5);
        */

        //WC-Synon
        string retStr = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows(_,s1)", pkb);
        
        REQUIRE(retStr == "3,4,5");

        string retStr3 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows(s1,_)", pkb);
        
        REQUIRE(retStr3 == "1,3,4");

        // Synon-Synon
        string retStr2 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows(c1,s1)", pkb);
        
        REQUIRE(retStr2 == "3");


        //Int-WC
        string retStr4 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows(1,_)", pkb);
        
        REQUIRE(retStr4 == "1,3,4,5");

        string retStr5 = TestUtility::testDriver("read s1; call c1; Select s1 such that Follows(_,1)", pkb);
        
        REQUIRE(retStr5 == "none");

    }
    catch (exception e)
    {
        std::cout << "exception occured!";
    }
}