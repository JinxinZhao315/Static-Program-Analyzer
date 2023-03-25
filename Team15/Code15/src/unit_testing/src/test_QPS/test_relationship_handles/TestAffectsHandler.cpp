#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;


string testAffects(string queryStr);

string testAffects(string queryStr) {
    PKB pkb;
    pkb.addAllStmts({ {"while",{2}}, {"if",{3}},{"=",{1,4,5,7,8}},{"read",{6}} });
    pkb.addAllAffects({ {1,{4, 5,7}}, {2,{}},{3,{}}, {4, {}}, {5,{4, 5,7}},{6,{}}, {8,{}}, {7,{8}} });
    pkb.addAllAffectsStar({ { 1,{4,5,7,8} }, {2,{}},{3,{}},{ 5, {4,5,7,8} }, {7,{8}}, {8,{}}, {4, {}},{6,{}}
        });
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}

TEST_CASE("Affects/Affects* empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a such that Affects(1, 3)", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Affects(a,_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; assign p; Select v such that Affects*(1,_)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; assign p; Select a such that Affects*(_,a)", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("Affects/Affects* (Integer, Integer)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(1, 4)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,4,5,7,8");

    string retStr6 = testAffects("assign a; Select a such that Affects(1, 1)");
    //cout << retStr1 << endl;
    REQUIRE(retStr6 == "none");

    string retStr2 = testAffects("assign p; Select p such that Affects(1, 3)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testAffects("assign p; Select p such that Affects*(5, 5)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,4,5,7,8");

    string retStr4 = testAffects("assign p; Select p such that Affects*(1, 8)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,4,5,7,8");

    string retStr5 = testAffects("assign p; Select p such that Affects*(5, 4)");
    //cout << retStr2 << endl;
    REQUIRE(retStr5 == "1,4,5,7,8");
}

TEST_CASE("Affects/Affects* (Integer, _)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(1, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,4,5,7,8");

    string retStr2 = testAffects("assign p; Select p such that Affects(4, _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testAffects("assign p; Select p such that Affects*(5, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,4,5,7,8");

    string retStr4 = testAffects("assign p; Select p such that Affects*(8, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Affects/Affects* (Integer, assign)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(1, a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "4,5,7");

    string retStr2 = testAffects("assign p; Select p such that Affects(5, p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "4,5,7");

    string retStr3 = testAffects("assign p; Select p such that Affects*(1, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "4,5,7,8");

    string retStr4 = testAffects("assign p; Select p such that Affects*(7, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "8");
}

TEST_CASE("Affects/Affects* semantic error test") {

    string retStr1 = testAffects("assign a; Select a such that Affects(a, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SyntaxError");

    string retStr2 = testAffects("read v; Select v such that Affects(_, v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "SemanticError");
}

TEST_CASE("Affects/Affects* (assign, Integer)") {
    string retStr1 = testAffects("assign a; Select a such that Affects(a, 1)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = testAffects("assign p; Select p such that Affects(p, 8)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "7");

    string retStr3 = testAffects("assign p; Select p such that Affects*(p, 4)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,5");

    string retStr4 = testAffects("assign p; Select p such that Affects*(p, 7)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,5");
}

TEST_CASE("Affects/Affects* (assign, assign)") {
    string retStr1 = testAffects("assign a,b; Select a such that Affects(a, b)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,5,7");

    string retStr2 = testAffects("assign p; Select p such that Affects(p, p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr5 = testAffects("assign p,q; Select q such that Affects(p, q)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "4,5,7,8");

    string retStr3 = testAffects("assign p,q; Select q such that Affects*(p, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "4,5,7,8");

    string retStr4 = testAffects("assign p; Select p such that Affects*(p, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "5");
}

TEST_CASE("Affects/Affects* (assign, _)") {
    string retStr1 = testAffects("assign a,b; Select a such that Affects(a, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,5,7");

    string retStr5 = testAffects("assign p,q; Select q such that Affects(p, _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "1,4,5,7,8");

    string retStr3 = testAffects("assign p,q; Select q such that Affects*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,4,5,7,8");

    string retStr4 = testAffects("assign p; Select p such that Affects*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,5,7");
}

TEST_CASE("Affects/Affects* (_, _)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(_, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,4,5,7,8");

    string retStr3 = testAffects("assign p; Select p such that Affects*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,4,5,7,8");

    string retStr4 = testAffects("assign p,q; Select q such that Affects*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,4,5,7,8");
}

TEST_CASE("Affects/Affects* (_, assign)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(_, a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "4,5,7,8");

    string retStr4 = testAffects("assign p,q; Select p such that Affects*(_, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,4,5,7,8");
}

TEST_CASE("Affects/Affects* (_, Integer)") {

    string retStr1 = testAffects("assign a; Select a such that Affects(_, 1)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr3 = testAffects("assign p; Select p such that Affects*(_, 4)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,4,5,7,8");

    string retStr4 = testAffects("assign p,q; Select p such that Affects*(_, 5)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,4,5,7,8");
}