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
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), ASSIGN);
    Line line2 = Line(2, vector<string>({ "1", "2", "+" }), ASSIGN);
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
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), ASSIGN);
    Line line2 = Line(2, vector<string>({ "1", "2", "+" }), ASSIGN);
    Line line3 = Line(3, vector<string>({ "2", "3", "+" }), ASSIGN);
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
    Line line1 = Line(1, vector<string>({ "x", "y", "+" }), ASSIGN);
    Line line2 = Line(2, vector<string>({ "t", "2", "+" }), ASSIGN);
    Line line3 = Line(3, vector<string>({ "2", "y", "+" }), ASSIGN);
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

void testMulticlauseFillPkb4(PKB& pkb) {
    pkb.addAllVars(set<string>({"x", "y", "n", "m"}));
    pkb.addAllConsts(set<string>({"1", "0", "5"}));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({2,3,5,7})));
    stmts.insert(make_pair("if", set<int>({1})));
    stmts.insert(make_pair("while", set<int>({4,6})));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> assignPatterns;
    Line line2 = Line(2, vector<string>({"n", "1", "+"}), ASSIGN);
    Line line3 = Line(3, vector<string>({"m", "1", "-"}), ASSIGN);
    Line line5 = Line(5, vector<string>({"y", "1", "-"}), ASSIGN);
    Line line7 = Line(7, vector<string>({"x", "1", "-"}), ASSIGN);

    assignPatterns.insert(make_pair("n", set<Line>({line2})));
    assignPatterns.insert(make_pair("m", set<Line>({line3})));
    assignPatterns.insert(make_pair("y", set<Line>({line5})));
    assignPatterns.insert(make_pair("x", set<Line>({line7})));
    pkb.addAllAssignPatterns(assignPatterns);

    unordered_map<string, set<Line>> ifPatterns;
    Line line1 = Line(1, vector<string>({"x", "5", ">"}), IF);
    ifPatterns.insert(make_pair("x", set<Line>({line1})));
    pkb.addAllIfPatterns(ifPatterns);

    unordered_map<string, set<Line>> whilePatterns;
    Line line4 = Line(4, vector<string>({"y", "0", ">"}), WHILE);
    whilePatterns.insert(make_pair("y", set<Line>({line4})));
    Line line6 = Line(6, vector<string>({"x", "0", ">"}), WHILE);
    whilePatterns.insert(make_pair("x", set<Line>({line6})));
    pkb.addAllWhilePatterns(whilePatterns);

    unordered_map<int, int> follows = { {1, 4}, {4, 6} };
    pkb.addAllFollows(follows);

    unordered_map<int, std::set<int>> followsStar = {
            {1, {4, 6} },
            {4, {6} }
    };
    pkb.addAllFollowsStar(followsStar);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
    // Line 4: while ( y > 0 ) {
    // Line 5: y = y - 1}
    // Line 6: while ( x > 0) {
    // Line7:  x = x - 1}
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

TEST_CASE("Multiple such that & pattern clauses test 1") {
    PKB pkb;
    testMulticlauseFillPkb3(pkb);

    // Line 1: k = x + y;
    // Line 2: m = t + 2;
    // Line 3: n = 2 + y

    string retStr1 = TestUtility::testDriver("assign a; Select a pattern a (\"k\",_) such that Follows*(a,3) and Uses(a,\"y\")", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable v; Select v such that Follows*(1, a) and Uses(a,\"y\") pattern a (v,_\"2\"_)", pkb);
    REQUIRE(retStr2 == "n");
}

TEST_CASE("Multiple With clauses test 1") {
    PKB pkb;
    testMulticlauseFillPkb3(pkb);

    // Line 1: k = x + y;
    // Line 2: m = t + 2;
    // Line 3: n = 2 + y

    string retStr1 = TestUtility::testDriver("stmt s1, s2, s3; Select s1 with s1.stmt# = 1 and s2.stmt# = 2 and s3.stmt# = 3", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("stmt s1, s2; Select s1 such that Follows(s1, s2) with s1.stmt# = s2.stmt#", pkb);
    REQUIRE(retStr2 == "none");
}

TEST_CASE("Combination of Clauses test 1") {
    PKB pkb;
    testMulticlauseFillPkb3(pkb);
}