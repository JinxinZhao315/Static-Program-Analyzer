#include "PKB.h"
#include "QPS/include/PQLDriver.h"

#include "catch.hpp"

using namespace std;

string testUses(string queryStr);

string testUses(string queryStr) {

    PKB pkb;

    pkb.addStmt("=", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addUsesStmt(1,  {"x", "y"});

    pkb.addStmt("=", 2);
    pkb.addVar("m");
    pkb.addVar("i");
    pkb.addVar("j");
    pkb.addUsesStmt(2, {"i", "j"});

    pkb.addStmt("print", 3);
    pkb.addVar("t");
    pkb.addUsesStmt(3, {"t"});

    // Line 1: k = x + y;
    // Line 2: m = i + j;
    // Line 3: print t;

    PQLDriver driver = PQLDriver(pkb);
    string retStr = driver.processPQL(queryStr);
    return retStr;
}

TEST_CASE("UsesS (int, quoted_ident)"){

    string retStr1 = testUses("assign a; Select a such that Uses(1, \"x\")");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr3 = testUses("assign a; Select a such that Uses(3, \"t\")");
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "1,2");

    string retStr2 = testUses("assign a; Select a such that Uses(1, \"i\")");
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");
}

TEST_CASE("UsesS (int, _)"){

    string retStr1 = testUses("assign a; Select a such that Uses(1,_)");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

}

TEST_CASE("UsesS (int, synon)"){

    string retStr1 = testUses("variable v; Select v such that Uses(1,v)");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "x,y");

    string retStr2 = testUses("variable v; Select v such that Uses(3,v)");
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "t");

}

TEST_CASE("UsesS semantic error test"){

    string retStr1 = testUses("assign a; Select a such that Uses(_, \"x\")");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "SemanticError");

}

TEST_CASE("UsesS (synon, _)") {
    string retStr1 = testUses("assign a; Select a such that Uses(a,_)");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr3 = testUses("print p; Select p such that Uses(p,_)");
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "3");

    string retStr2 = testUses("assign a; variable v; Select v such that Uses(a,_)");
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "i,j,k,m,t,x,y");
}

TEST_CASE("UsesS (synon, quoted_ident)") {
    string retStr1 = testUses("assign a; Select a such that Uses(a,\"x\")");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testUses("print p; Select p such that Uses(p,\"t\")");
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "3");
}

TEST_CASE("UsesS (synon, synon)") {
    string retStr1 = testUses("assign a; variable v; Select a such that Uses(a,v)");
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testUses("assign a; variable v; Select v such that Uses(a,v)");
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "i,j,x,y");

    string retStr3 = testUses("print p; variable v; Select v such that Uses(p,v)");
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "t");

    string retStr4 = testUses("print p; variable v; Select p such that Uses(p,v)");
    cout << retStr4 << endl;
    REQUIRE(retStr4 == "3");

}

