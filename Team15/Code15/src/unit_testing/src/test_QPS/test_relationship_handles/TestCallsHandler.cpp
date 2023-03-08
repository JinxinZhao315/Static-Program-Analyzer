#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;


string testCalls(string queryStr);

string testCalls(string queryStr) {
    PKB pkb;
    pkb.addAllProcs({ "main", "proc1", "proc2", "proc3","proc4" });
    pkb.addAllCalls({ {"main",{"proc1","proc2"}}, {"proc1", {"proc2", "proc3"}} });
    pkb.addAllCallsStar({{ "main",{"proc1","proc2","proc3"} }, { "proc1", {"proc2", "proc3"} }
});
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}

TEST_CASE("Calls/Call* empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a such that Calls(\"main\", \"x\")", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Calls(\"main\",_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; procedure p; Select v such that Calls*(\"main\",p)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; procedure p; Select a such that Calls*(p,\"proc1\")", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("Calls/Calls* (quoted_ident, quoted_ident)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(\"main\", \"proc1\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2,proc3,proc4");

    string retStr2 = testCalls("procedure p; Select p such that Calls(\"main\", \"proc3\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(\"main\", \"proc3\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main,proc1,proc2,proc3,proc4");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(\"main\", \"main\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");

    string retStr5 = testCalls("procedure p; Select p such that Calls(\"main\", \"main\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Calls/Calls* (quoted_ident, _)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(\"main\", _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2,proc3,proc4");

    string retStr2 = testCalls("procedure p; Select p such that Calls(\"proc2\", _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(\"proc1\", _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main,proc1,proc2,proc3,proc4");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(\"proc3\", _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Calls/Calls* (quoted_ident, procedure)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(\"main\", a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "proc1,proc2");

    string retStr2 = testCalls("procedure p; Select p such that Calls(\"proc2\", p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(\"main\", p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "proc1,proc2,proc3");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(\"proc3\", p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Calls/Calls* syntax error test") {

    string retStr1 = testCalls("assign a; Select a such that Calls(a, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SyntaxError");

    string retStr2 = testCalls("variable v; Select v such that Calls(_, v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "SyntaxError");
}

TEST_CASE("Calls/Calls* (procedure, quoted_ident)") {
    string retStr1 = testCalls("procedure a; Select a such that Calls(a, \"proc2\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main");

    string retStr2 = testCalls("procedure p; Select p such that Calls(p, \"main\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(p, \"proc1\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(p, \"proc3\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "main,proc1");
}

TEST_CASE("Calls/Calls* (procedure, procedure)") {
    string retStr1 = testCalls("procedure a,b; Select a such that Calls(a, b)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr2 = testCalls("procedure p; Select p such that Calls(p, p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr5 = testCalls("procedure p,q; Select q such that Calls(p, q)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "proc1,proc2,proc3");

    string retStr3 = testCalls("procedure p,q; Select q such that Calls*(p, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "proc1,proc2,proc3");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(p, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Calls/Calls* (procedure, _)") {
    string retStr1 = testCalls("procedure a,b; Select a such that Calls(a, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr5 = testCalls("procedure p,q; Select q such that Calls(p, _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "main,proc1,proc2,proc3,proc4");

    string retStr3 = testCalls("procedure p,q; Select q such that Calls*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main,proc1,proc2,proc3,proc4");

    string retStr4 = testCalls("procedure p; Select p such that Calls*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "main,proc1");
}

TEST_CASE("Calls/Calls* (_, _)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(_, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2,proc3,proc4");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main,proc1,proc2,proc3,proc4");

    string retStr4 = testCalls("procedure p,q; Select q such that Calls*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "main,proc1,proc2,proc3,proc4");
}

TEST_CASE("Calls/Calls* (_, procedure)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(_, a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "proc1,proc2,proc3");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(_, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "proc1,proc2,proc3");

    string retStr4 = testCalls("procedure p,q; Select p such that Calls*(_, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "main,proc1,proc2,proc3,proc4");
}

TEST_CASE("Calls/Calls* (_, quoted_ident)") {

    string retStr1 = testCalls("procedure a; Select a such that Calls(_, \"proc3\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2,proc3,proc4");

    string retStr3 = testCalls("procedure p; Select p such that Calls*(_, \"proc1\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "main,proc1,proc2,proc3,proc4");

    string retStr4 = testCalls("procedure p,q; Select p such that Calls*(_, \"main\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}