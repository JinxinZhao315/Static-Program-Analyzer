#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;


string testUsesP(string queryStr);

string testUsesP(string queryStr) {
    PKB pkb;
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}

TEST_CASE("UsesP empty pkb") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr = TestUtility::testDriver("assign a; Select a such that Uses(1, \"x\")", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Uses(1,_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; Select v such that Uses(1,v)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; Select a such that Uses(a,v)", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("UsesP (int, quoted_ident)") {

    string retStr1 = testUsesP("assign a; Select a such that Uses(1, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr3 = testUsesP("assign a; Select a such that Uses(3, \"t\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "1,2");

    string retStr2 = testUsesP("assign a; Select a such that Uses(1, \"i\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");
}

TEST_CASE("UsesP (int, _)") {

    string retStr1 = testUsesP("assign a; Select a such that Uses(1,_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

}

TEST_CASE("UsesP (int, synon)") {

    string retStr1 = testUsesP("variable v; Select v such that Uses(1,v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "x,y");

    string retStr2 = testUsesP("variable v; Select v such that Uses(3,v)");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "t");

}

TEST_CASE("UsesP semantic error test") {

    string retStr1 = testUsesP("assign a; Select a such that Uses(_, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SemanticError");

}

TEST_CASE("UsesP (synon, _)") {
    string retStr1 = testUsesP("assign a; Select a such that Uses(a,_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr3 = testUsesP("print p; Select p such that Uses(p,_)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "3");

    string retStr2 = testUsesP("assign a; variable v; Select v such that Uses(a,_)");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "i,j,k,m,t,x,y");
}

TEST_CASE("UsesP (synon, quoted_ident)") {
    string retStr1 = testUsesP("assign a; Select a such that Uses(a,\"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testUsesP("print p; Select p such that Uses(p,\"t\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "3");
}

TEST_CASE("UsesP (synon, synon)") {
    string retStr1 = testUsesP("assign a; variable v; Select a such that Uses(a,v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testUsesP("assign a; variable v; Select v such that Uses(a,v)");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "i,j,x,y");

    string retStr3 = testUsesP("print p; variable v; Select v such that Uses(p,v)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "t");

    string retStr4 = testUsesP("print p; variable v; Select p such that Uses(p,v)");
    //cout << retStr4 << endl;
    REQUIRE(retStr4 == "3");

}