#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

void testMulticlauseFillPkb1(PKB& pkb) {
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

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: read i;
    // Line 5: read j;

}

void testMulticlauseFillPkb2(PKB& pkb) {

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

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: n = 2 + 3;
}

void testMulticlauseFillPkb3(PKB& pkb) {

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

    unordered_map<int, int> follows = { {1, 2}, {2, 3}};
    pkb.addAllFollows(follows);

    unordered_map<int, std::set<int>> followsStar = {
            {1, {2, 3} },
            {2, {3} }
    };
    pkb.addAllFollowsStar(followsStar);

    // Line 1: k = x + y;
    // Line 2: m = t + 2;
    // Line 3: n = 2 + y
}

TEST_CASE("Follows/Follow* and pattern test") {
    PKB pkb;
    testMulticlauseFillPkb1(pkb);

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
    testMulticlauseFillPkb2(pkb);

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
    testMulticlauseFillPkb3(pkb);

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

TEST_CASE("Multiple such that & pattern clauses test") {
    PKB pkb;
    testMulticlauseFillPkb3(pkb);

    // Line 1: k = x + y;
    // Line 2: m = t + 2;
    // Line 3: n = 2 + y

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Follows*(a,3) pattern a (\"k\",_) such that Uses(a,\"y\")", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable v; Select v such that Follows*(1, a) pattern a (v,_\"2\"_) such that Uses(a,\"y\")", pkb);
    REQUIRE(retStr2 == "n");

}