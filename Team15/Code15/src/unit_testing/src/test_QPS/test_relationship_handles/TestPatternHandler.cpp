#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"

#include "catch.hpp"

void testPatternFillPkb(PKB& pkb) {
    pkb.addAllVars(set<string>({"x", "y", "k", "m", "t"}));
    pkb.addAllConsts(set<string>({"1", "2"}));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({1,2})));
    stmts.insert(make_pair("read", set<int>({3})));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({"x", "y", "+"}), "=");
    Line line2 = Line(2, vector<string>({"1", "2", "+"}), "=");
    patterns.insert(make_pair("k", set<Line>({line1})));
    patterns.insert(make_pair("m", set<Line>({line2})));
    pkb.addAllAssignPatterns(patterns);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;
    // Line 3: read t;
}

void testPatternFillPkb2(PKB& pkb) {
    pkb.addAllVars(set<string>({"x", "y", "n", "m"}));
    pkb.addAllConsts(set<string>({"1", "0", "5"}));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({2,3,5,7})));
    stmts.insert(make_pair("if", set<int>({1})));
    stmts.insert(make_pair("while", set<int>({4,6})));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> assignPatterns;
    Line line2 = Line(2, vector<string>({"n", "1", "+"}), "=");
    Line line3 = Line(3, vector<string>({"m", "1", "-"}), "=");
    Line line5 = Line(5, vector<string>({"y", "1", "-"}), "=");
    Line line7 = Line(7, vector<string>({"x", "1", "-"}), "=");

    assignPatterns.insert(make_pair("n", set<Line>({line2})));
    assignPatterns.insert(make_pair("m", set<Line>({line3})));
    assignPatterns.insert(make_pair("y", set<Line>({line5})));
    assignPatterns.insert(make_pair("x", set<Line>({line7})));
    pkb.addAllAssignPatterns(assignPatterns);

    unordered_map<string, set<Line>> ifPatterns;
    Line line1 = Line(1, vector<string>({"x", "5", ">"}), "if");
    ifPatterns.insert(make_pair("x", set<Line>({line1})));
    pkb.addAllIfPatterns(ifPatterns);

    unordered_map<string, set<Line>> whilePatterns;
    Line line4 = Line(4, vector<string>({"y", "0", ">"}), "while");
    whilePatterns.insert(make_pair("y", set<Line>({line4})));
    Line line6 = Line(6, vector<string>({"x", "0", ">"}), "while");
    whilePatterns.insert(make_pair("x", set<Line>({line6})));
    pkb.addAllWhilePatterns(whilePatterns);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
    // Line 4: while ( y > 0 ) {
    // Line 5: y = y - 1}
    // Line 6: while ( x > 0) {
    // Line7:  x = x - 1}
}

TEST_CASE("PatternHandler a(_,_) test empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a pattern a (_,_)", pkb);
    REQUIRE(retStr == "none");
}

TEST_CASE("PatternHandler a(_,_) test filled pkb") {
    PKB pkb;
    testPatternFillPkb(pkb);

    string retStr = TestUtility::testDriver("assign a; Select a pattern a (_,_)", pkb);
    REQUIRE(retStr == "1,2");
}

TEST_CASE("PatternHandler a(_,UNDERSCORED_EXPR) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;
    // Line 3: read t;

    string retStr1 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"x\"_)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"t\"_)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"2\"_)", pkb);
    REQUIRE(retStr3 == "2");

    string retStr4 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"+2\"_)", pkb);
    REQUIRE(retStr4 == "SyntaxError");

    string retStr5 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"2+\"_)", pkb);
    REQUIRE(retStr5 == "SyntaxError");
}


TEST_CASE("PatternHandler a(SYNONYM,_/UNDERSCORED_EXPR) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_)", pkb);
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,_)", pkb);
    REQUIRE(retStr2 == "k,m");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_\"1\"_)", pkb);
    REQUIRE(retStr3 == "2");

    string retStr4 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_\"y\"_)", pkb);
    REQUIRE(retStr4 == "1");

    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,_\"y\"_)", pkb);
    REQUIRE(retStr5 == "k");
}

TEST_CASE("PatternHandler a(QUOTED_IDENT,_/UNDERSCORED_EXPR) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;

    string retStr1 = TestUtility::testDriver("assign a; Select a pattern a (\"k\",_)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; Select a pattern a (\"t\",_)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select b pattern a (\"k\", _)", pkb);
    REQUIRE(retStr3 == "k,m,t,x,y");

    string retStr4 = TestUtility::testDriver("assign a; Select a pattern a (\"k\",_\"y\"_)", pkb);
    REQUIRE(retStr4 == "1");

    string retStr5 = TestUtility::testDriver("assign a; Select a pattern a (\"m\",_\"1\"_)", pkb);
    REQUIRE(retStr5 == "2");
}

TEST_CASE("patternHandler while test") {
    PKB pkb;
    testPatternFillPkb2(pkb);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
    // Line 4: while ( y > 0 ) {
    // Line 5: y = y - 1}
    // Line 6: while ( x > 0) {
    // Line7:  x = x - 1}

    string retStr = TestUtility::testDriver("while w; Select w pattern w (_,_)", pkb);
    REQUIRE(retStr == "4,6");

    string retStr1 = TestUtility::testDriver("while w; variable v; Select v pattern w (v,_)", pkb);
    REQUIRE(retStr1 == "x,y");

    string retStr2 = TestUtility::testDriver("while w; Select w pattern w (\"y\",_)", pkb);
    REQUIRE(retStr2 == "4");

    string retStr3 = TestUtility::testDriver("while w; Select w pattern w (\"t\",_)", pkb);
    REQUIRE(retStr3 == "none");

    string retStr4 = TestUtility::testDriver("while w; Select w pattern w (\"t\",_,_)", pkb);
    REQUIRE(retStr4 == "SyntaxError");

}

TEST_CASE("patternHandler if test") {

    PKB pkb;
    testPatternFillPkb2(pkb);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
    // Line 4: while ( y > 0 ) {
    // Line 5: y = y - 1}
    // Line 6: while ( x > 0) {
    // Line7:  x = x - 1}

    string retStr = TestUtility::testDriver("if i; Select i pattern i (_,_,_)", pkb);
    REQUIRE(retStr == "1");

    string retStr1 = TestUtility::testDriver("if i; variable v; Select v pattern i (v,_,_)", pkb);
    REQUIRE(retStr1 == "x");

    string retStr2 = TestUtility::testDriver("if i; Select i pattern i (\"x\",_,_)", pkb);
    REQUIRE(retStr2 == "1");

    string retStr3 = TestUtility::testDriver("if i; Select i pattern i (\"t\",_,_)", pkb);
    REQUIRE(retStr3 == "none");

    string retStr4 = TestUtility::testDriver("if i; Select i pattern i (\"t\",_)", pkb);
    REQUIRE(retStr4 == "SyntaxError");

}