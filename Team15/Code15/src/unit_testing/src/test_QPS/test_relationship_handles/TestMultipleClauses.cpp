#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"


TEST_CASE("Follows/Follow* and pattern test") {
    PKB pkb;
    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 1, 2 })));
    stmts.insert(make_pair("read", set<int>({ 3, 4, 5 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k", "m", "t", "i", "j"});

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), "=");
    Line line2 = Line(2, vector<string>({ "1", "2", "+" }), "=");
    patterns.insert(make_pair("k", set<Line>({ line1 })));
    patterns.insert(make_pair("m", set<Line>({ line2 })));
    pkb.addAllAssignPatterns(patterns);

    unordered_map<int, int> follows = { {1, 2}, {2, 3}, {3, 4}, {4, 5} };
    pkb.addAllFollows(follows);

    unordered_map<int, std::set<int>> followsStar = {
            {1, {2, 3, 4, 5} },
            {2, {3, 4, 5} },
            {3, {4, 5} },
            {4, {5} }
    };
    pkb.addAllFollowsStar(followsStar);

    //do not add one by one to pkb
    /*
    pkb.addStmt("=", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);


    pkb.addStmt("=", 2);
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
    */

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: read i;
    // Line 5: read j;

    //Follows
    string retStr1 = TestUtility::testDriver("assign a; Select a such that Follows(a,2) pattern a (\"k\",_)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; Select a such that Follows(a,3) pattern a (\"k\",_)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; Select a such that Follows(a,3) pattern a (\"m\",_)", pkb);
    REQUIRE(retStr3 == "2");

    // Follows*
    string retStr4 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_)", pkb);
    REQUIRE(retStr4 == "1");

    string retStr5 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_\"y\"_)", pkb);
    REQUIRE(retStr5 == "1");

    string retStr6 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_\"t\"_)", pkb);
    REQUIRE(retStr6 == "none");

    string retStr7 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (_,_)", pkb);
    REQUIRE(retStr7 == "1,2");

    string retStr8 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (_,_\"2\"_)", pkb);
    REQUIRE(retStr8 == "2");



}

TEST_CASE("Follows/Follow* and pattern linked synons test") {
    PKB pkb;

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 1, 2, 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k", "m", "n"});

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), "=");
    Line line2 = Line(2, vector<string>({ "1", "2", "+" }), "=");
    Line line3 = Line(3, vector<string>({ "2", "3", "+" }), "=");
    patterns.insert(make_pair("k", set<Line>({ line1 })));
    patterns.insert(make_pair("m", set<Line>({ line2 })));
    patterns.insert(make_pair("n", set<Line>({ line3 })));
    pkb.addAllAssignPatterns(patterns);

    unordered_map<int, int> follows = { {1, 2}, {2, 3} };
    pkb.addAllFollows(follows);

    unordered_map<int, std::set<int>> followsStar = {
            {1, {2, 3} },
            {2, {3} }
    };
    pkb.addAllFollowsStar(followsStar);

    //do not add one by one to pkb
    /*
    pkb.addStmt("=", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);


    pkb.addStmt("=", 2);
    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    pkb.addStmt("=", 3);
    pkb.addVar("n");
    vector<string> rhs3 = {"2", "3", "+"};
    set<vector<string>> rhsSet3 = {rhs3};
    pkb.addPattern(2, "n", rhsSet3);

    pkb.addFollows(1, 2);
    pkb.addFollows(2, 3);

    pkb.addFollowsStar(1, set<int>({2,3}));
    pkb.addFollowsStar(2, set<int>({3}));
    */

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: n = 2 + 3;

    string retStr1 = TestUtility::testDriver("assign a1, a2; Select a1 such that Follows(a1,a2)", pkb);
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a1, a2; Select a2 such that Follows(a1,a2)", pkb);
    REQUIRE(retStr2 == "2,3");

    string retStr3 = TestUtility::testDriver("assign a1, a2; Select a2 pattern a2 (\"m\",_)", pkb);
    REQUIRE(retStr3 == "2");

    string retStr = TestUtility::testDriver("assign a1, a2; Select a1 such that Follows(a1,a2) pattern a2 (\"m\",_)", pkb);
    // Follows: a1: 1,2
    //          a2: 2,3
    // pattern: a2: 2
    REQUIRE(retStr == "1");
}

TEST_CASE("ModifiesS / UsesS and pattern test") {
    PKB pkb;

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 1, 2, 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k", "m", "t", "n" });

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), "=");
    Line line2 = Line(2, vector<string>({ "t", "2", "+" }), "=");
    Line line3 = Line(3, vector<string>({ "2", "y", "+" }), "=");
    patterns.insert(make_pair("k", set<Line>({ line1 })));
    patterns.insert(make_pair("m", set<Line>({ line2 })));
    patterns.insert(make_pair("n", set<Line>({ line3 })));
    pkb.addAllAssignPatterns(patterns);


    pkb.addAllModifiesStmt({ {1, {"k"}}, {2, {"m"}}, {3, {"n"}} });
    pkb.addAllUsesStmt({ {1, {"x", "y"}}, {2, {"t"}}, {3, {"y"}}});
    
    //do not add one by one to pkb
    /*
    pkb.addStmt("=", 1);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);
    pkb.addModifiesStmt(1, {"k"});
    pkb.addUsesStmt(1, {"x", "y"});

    pkb.addStmt("=", 2);
    pkb.addVar("m");
    pkb.addVar("t");
    vector<string> rhs2 = {"t","2","+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);
    pkb.addModifiesStmt(2, {"m"});
    pkb.addUsesStmt(2, {"t"});

    pkb.addStmt("=", 3);
    pkb.addVar("n");
    vector<string> rhs3 = {"2", "y", "+"};
    set<vector<string>> rhsSet3 = {rhs3};
    pkb.addPattern(3, "n", rhsSet3);
    pkb.addModifiesStmt(3, {"n"});
    pkb.addUsesStmt(3, {"y"});
    */

    // Line 1: k = x + y;
    // Line 2: m = t + 2;
    // Line 3: n = 2 + y

     //ModifiesS
    string retStr1 = TestUtility::testDriver("assign a; Select a such that Modifies(a,_) pattern a (\"k\",_)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable v; Select v such that Modifies(a,v) pattern a (\"k\",_)", pkb);
    REQUIRE(retStr2 == "k");

    string retStr3 = TestUtility::testDriver("assign a; variable v; Select v such that Modifies(a,v) pattern a (_,_\"2\"_)", pkb);
    REQUIRE(retStr3 == "m,n");

    string retStr7 = TestUtility::testDriver("assign a; Select a such that Modifies(a,\"k\") pattern a (_,_\"x\"_)", pkb);
    REQUIRE(retStr7 == "1");

    string retStr8 = TestUtility::testDriver("assign a; Select a such that Modifies(a,\"k\") pattern a (_,_\"t\"_)", pkb);
    REQUIRE(retStr8 == "none");

    // UsesS
    string retStr4 = TestUtility::testDriver("assign a; variable v; Select v such that Uses(a,v) pattern a (_,_\"y\"_)", pkb);
    REQUIRE(retStr4 == "x,y");

    string retStr5 = TestUtility::testDriver("assign a; variable v; Select v such that Uses(a,v) pattern a (_,_)", pkb);
    REQUIRE(retStr5 == "t,x,y");

    string retStr6 = TestUtility::testDriver("assign a; Select a such that Uses(a,\"y\") pattern a (\"k\",_)", pkb);
    REQUIRE(retStr6 == "1");

    //Invalid syntax test
    string retStr10 = TestUtility::testDriver("if i; Select i such that Parents(i,_) pattern i (\"k\",_)", pkb);
    REQUIRE(retStr10 == "SyntaxError");
}