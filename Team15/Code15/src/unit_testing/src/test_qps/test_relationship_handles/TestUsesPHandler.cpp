#include "pkb/include/PKB.h"
#include "qps/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;


string testUsesP(string queryStr);

string testUsesP(string queryStr) {
    PKB pkb;
    pkb.addAllProcs({ "main", "proc1", "proc2"});
    pkb.addAllVars({ "a", "b", "c" ,"d","e"});
    pkb.addAllUsesProc({ {"main", {"a","b", "d"}}, {"proc1", {"c", "d"}}});
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}


TEST_CASE("UsesP empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a such that Uses(\"main\", \"x\")", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Uses(\"main\",_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; Select v such that Uses(\"main\",v)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; procedure p; Select a such that Uses(p,v)", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("UsesP (quoted_ident, quoted_ident)") {

    string retStr1 = testUsesP("procedure a; Select a such that Uses(\"main\", \"a\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2");

    string retStr2 = testUsesP("assign a; Select a such that Uses(\"main\", \"t\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testUsesP("variable b; Select b such that Uses(\"proc1\", \"a\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("UsesP (quoted_ident, variable)") {

    string retStr1 = testUsesP("variable v; Select v such that Uses(\"main\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "a,b,d");

    string retStr2 = testUsesP("variable v; Select v such that Uses(\"proc1\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "c,d");

    string retStr3 = testUsesP("variable v; Select v such that Uses(\"proc2\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("UsesP (quoted_ident, _)") {
    string retStr1 = testUsesP("procedure p; Select p such that Uses(\"main\",_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2");

    string retStr2 = testUsesP("variable v; Select v such that Uses(\"proc1\",_)");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "a,b,c,d,e");

    string retStr3 = testUsesP("variable v; Select v such that Uses(\"proc2\",_)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("UsesP semantic error test") {

    string retStr1 = testUsesP("assign a; Select a such that Uses(_, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SemanticError");

}

TEST_CASE("UsesP (procedure, quoted_ident)") {
    string retStr1 = testUsesP("procedure p; Select p such that Uses(p,\"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr3 = testUsesP("procedure p; Select p such that Uses(p,\"a\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "main");

    string retStr2 = testUsesP("procedure a; variable v; Select a such that Uses(a,\"d\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "main,proc1");
}

TEST_CASE("UsesP (procedure, variable)") {
    string retStr1 = testUsesP("procedure p; variable v; Select p such that Uses(p,v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr3 = testUsesP("procedure p; variable v; Select v such that Uses(p,v)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "a,b,c,d");
}

TEST_CASE("UsesP (procedure, _)") {
    string retStr1 = testUsesP("procedure p; variable v; Select p such that Uses(p,_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr3 = testUsesP("procedure p; variable v; Select v such that Uses(p,_)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "a,b,c,d,e");
}