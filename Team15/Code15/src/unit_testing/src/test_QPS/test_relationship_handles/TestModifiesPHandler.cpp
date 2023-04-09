#include "pkb/include/PKB.h"
#include "qps/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;


string testModifiesP(string queryStr);

string testModifiesP(string queryStr) {
    PKB pkb;
    pkb.addAllProcs({ "main", "proc1", "proc2" });
    pkb.addAllVars({ "a", "b", "c" ,"d","e" });
    pkb.addAllModifiesProc({ {"main", {"a","b", "d"}}, {"proc1", {"c", "d"}} });
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}


TEST_CASE("ModifiesP empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a such that Modifies(\"main\", \"x\")", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Modifies(\"main\",_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; Select v such that Modifies(\"main\",v)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; procedure p; Select a such that Modifies(p,v)", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("ModifiesP (quoted_ident, quoted_ident)") {

    string retStr1 = testModifiesP("procedure a; Select a such that Modifies(\"main\", \"a\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2");

    string retStr2 = testModifiesP("assign a; Select a such that Modifies(\"main\", \"t\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testModifiesP("variable b; Select b such that Modifies(\"proc1\", \"a\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("ModifiesP (quoted_ident, variable)") {

    string retStr1 = testModifiesP("variable v; Select v such that Modifies(\"main\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "a,b,d");

    string retStr2 = testModifiesP("variable v; Select v such that Modifies(\"proc1\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "c,d");

    string retStr3 = testModifiesP("variable v; Select v such that Modifies(\"proc2\",v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("ModifiesP (quoted_ident, _)") {

    string retStr1 = testModifiesP("procedure p; Select p such that Modifies(\"main\",_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1,proc2");

    string retStr2 = testModifiesP("variable v; Select v such that Modifies(\"proc1\",_)");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "a,b,c,d,e");

    string retStr3 = testModifiesP("variable v; Select v such that Modifies(\"proc2\",_)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("ModifiesP semantic error test") {

    string retStr1 = testModifiesP("assign a; Select a such that Modifies(_, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SemanticError");

}

TEST_CASE("ModifiesP (procedure, quoted_ident)") {
    string retStr1 = testModifiesP("procedure p; Select p such that Modifies(p,\"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr3 = testModifiesP("procedure p; Select p such that Modifies(p,\"a\")");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "main");

    string retStr2 = testModifiesP("procedure a; variable v; Select a such that Modifies(a,\"d\")");
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "main,proc1");
}

TEST_CASE("ModifiesP (procedure, variable)") {
    string retStr1 = testModifiesP("procedure p; variable v; Select p such that Modifies(p,v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr3 = testModifiesP("procedure p; variable v; Select v such that Modifies(p,v)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "a,b,c,d");
}

TEST_CASE("ModifiesP (procedure, _)") {
    string retStr1 = testModifiesP("procedure p; variable v; Select p such that Modifies(p,_)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "main,proc1");

    string retStr3 = testModifiesP("procedure p; variable v; Select v such that Modifies(p,_)");
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "a,b,c,d,e");
}