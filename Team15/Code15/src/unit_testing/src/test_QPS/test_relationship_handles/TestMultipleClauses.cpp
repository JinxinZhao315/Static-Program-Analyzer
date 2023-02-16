#include "PKB.h"
#include "QPS/include/PQLDriver.h"

#include "catch.hpp"

string testDriver(string queryStr, PKB& pkb);

string testDriver(string queryStr, PKB& pkb) {
    PQLDriver driver = PQLDriver(pkb);
    string retStr = driver.processPQL(queryStr);
    return retStr;
}

TEST_CASE("Follows/Follow* and pattern test") {
    PKB pkb;

    pkb.addStmt("assign", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);


    pkb.addStmt("read", 2);
    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    pkb.addStmt("read", 3);
    pkb.addVar("t");
    pkb.addStmt("read", 4);
    pkb.addVar("i");
    pkb.addStmt("read", 5);
    pkb.addVar("j");

    pkb.addFollows(1, 2);
    pkb.addFollows(2, 3);
    pkb.addFollows(3, 4);
    pkb.addFollows(4, 5);

    pkb.addFollowsStar(1, set<int>({2,3,4,5}));
    pkb.addFollowsStar(2, set<int>({3,4,5}));
    pkb.addFollowsStar(3, set<int>({4,5}));
    pkb.addFollowsStar(4, set<int>({5}));

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: read i;
    // Line 5: read j;

    //Follows
    string retStr1 = testDriver("assign a; Select a such that Follows(a,2) pattern a (\"k\",_)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testDriver("assign a; Select a such that Follows(a,3) pattern a (\"k\",_)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr3 = testDriver("assign a; Select a such that Follows(a,3) pattern a (\"m\",_)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "2");

    // Follows*
    string retStr4 = testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_)", pkb);
    cout << retStr4 << endl;
    REQUIRE(retStr4 == "1");

    string retStr5 = testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_\"y\"_)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "1");

    string retStr6 = testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_\"t\"_)", pkb);
    cout << retStr6 << endl;
    REQUIRE(retStr6 == "None");

    string retStr7 = testDriver("assign a; Select a such that Follows*(a,3) pattern a (_,_)", pkb);
    cout << retStr7 << endl;
    REQUIRE(retStr7 == "1,2");

    string retStr8 = testDriver("assign a; Select a such that Follows*(a,3) pattern a (_,_\"2\"_)", pkb);
    cout << retStr8 << endl;
    REQUIRE(retStr8 == "2");



}

TEST_CASE("Follows/Follow* and pattern test 2") {
    PKB pkb;

    pkb.addStmt("read", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);


    pkb.addStmt("read", 2);
    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    pkb.addStmt("read", 3);
    pkb.addVar("n");
    vector<string> rhs3 = {"2", "3", "+"};
    set<vector<string>> rhsSet3 = {rhs3};
    pkb.addPattern(2, "n", rhsSet3);

    pkb.addFollows(1, 2);
    pkb.addFollows(2, 3);

    pkb.addFollowsStar(1, set<int>({2,3}));
    pkb.addFollowsStar(2, set<int>({3}));


    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: n = 2 + 3;

//    string retStr1 = testDriver("assign a1, a2; Select a1 such that Follows(a1,a2)", pkb);
//    cout << retStr1 << endl;
//    REQUIRE(retStr1 == "1,2");
//
//    string retStr2 = testDriver("assign a1, a2; Select a2 such that Follows(a1,a2)", pkb);
//    cout << retStr2 << endl;
//    REQUIRE(retStr2 == "2,3");
//
//    string retStr3 = testDriver("assign a1, a2; Select a2 pattern a2 (\"m\",_)", pkb);
//    cout << retStr3 << endl;
//    REQUIRE(retStr3 == "2");

    string retStr = testDriver("assign a1, a2; Select a1 such that Follows(a1,a2) pattern a2 (\"m\",_)", pkb);
    // Follows: a1: 1,2
    //          a2: 2,3
    // pattern: a2: 2
    cout << retStr << endl;
    REQUIRE(retStr == "1");
}