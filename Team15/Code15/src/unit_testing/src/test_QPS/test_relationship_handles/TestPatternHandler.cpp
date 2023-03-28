#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "exceptions/PQLSyntaxError.h"
#include "TestUtility.h"

#include "catch.hpp"

void testPatternFillPkb(PKB& pkb) {
    pkb.addAllVars(set<string>({"x", "y", "k", "m", "t"}));
    pkb.addAllConsts(set<string>({"1", "2", "3"}));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({1,2,4})));
    stmts.insert(make_pair("read", set<int>({3})));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({"x", "y", "+"}), "=");
    Line line2 = Line(2, vector<string>({"1", "2", "+"}), "=");
    Line line4 = Line(4, vector<string>({"3"}), "=");
    patterns.insert(make_pair("k", set<Line>({line1})));
    patterns.insert(make_pair("m", set<Line>({line2})));
    patterns.insert(make_pair("x", set<Line>({line4})));
    pkb.addAllAssignPatterns(patterns);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: x = 3
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


void testPatternFillPkb3(PKB& pkb) {
    pkb.addAllVars(set<string>({"x", "y", "k", "m", "t"}));
    pkb.addAllConsts(set<string>({"1", "2", "3", "4", "5"}));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({1,2,4})));
    stmts.insert(make_pair("read", set<int>({3})));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> patterns;
    Line line1 = Line(1, vector<string>({"x", "y", "4", "+", "+"}), "=");
    Line line2 = Line(2, vector<string>({"1", "2", "+", "3", "+"}), "=");
    Line line4 = Line(4, vector<string>({"1", "3", "5", "*", "+"}), "=");
    patterns.insert(make_pair("k", set<Line>({line1})));
    patterns.insert(make_pair("m", set<Line>({line2})));
    patterns.insert(make_pair("x", set<Line>({line4})));
    pkb.addAllAssignPatterns(patterns);

    // Line1:  k = x + (y + 4)
    // Line 2: m = 1 + 2 + 3;
    // Line 3: read t;
    // Line 4: x = 1 + 3 * 5
}

//TEST_CASE("Tokeniser and ConvertToPostfix test") {
//    PKB pkb;
//    PatternHandler handler = PatternHandler(pkb);
//    string input = "aa+bb*cc+dd";
//    vector<string> tokens = handler.simplifiedTokenise(input);
//    vector<string> result = handler.simplifiedConvertToPostfix(tokens);
//    vector<string> expected = {"aa", "bb", "cc", "*", "+", "dd", "+"};
//    REQUIRE(result == expected);
//}

//TEST_CASE("Tokeniser and ConvertToPostfix test throw error") {
//    PKB pkb;
//    PatternHandler handler = PatternHandler(pkb);
//
//    string input = "+bb*cc+dd";
//    vector<string> tokens = handler.simplifiedTokenise(input);
//    REQUIRE_THROWS_AS(handler.simplifiedConvertToPostfix(tokens), PQLSyntaxError);
//
//    string input2 = "bb*cc+(dd";
//    vector<string> tokens2 = handler.simplifiedTokenise(input2);
//    REQUIRE_THROWS_AS(handler.simplifiedConvertToPostfix(tokens2), PQLSyntaxError);
//
//    string input3 = "{aa+bb*cc}+dd";
//    REQUIRE_THROWS_AS(handler.simplifiedTokenise(input3), PQLSyntaxError);
//}

TEST_CASE("PatternHandler a(_,_) test empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a pattern a (_,_)", pkb);
    REQUIRE(retStr == "none");
}

TEST_CASE("PatternHandler a(_,_) test filled pkb") {
    PKB pkb;

    testPatternFillPkb(pkb);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: x = 3

    string retStr = TestUtility::testDriver("assign a; Select a pattern a (_,_)", pkb);
    REQUIRE(retStr == "1,2,4");
}

TEST_CASE("PatternHandler a(_,xx) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: x = 3

    string retStr1 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"x\"_)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"t\"_)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"2\"_)", pkb);
    REQUIRE(retStr3 == "2");

    string retStr4 = TestUtility::testDriver("assign a; Select a pattern a (_,\"2\")", pkb);
    REQUIRE(retStr4 == "none");

    string retStr5 = TestUtility::testDriver("assign a; Select a pattern a (_,\"3\")", pkb);
    REQUIRE(retStr5 == "4");

//    string retStr6 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"+2\"_)", pkb);
//    REQUIRE(retStr6 == "SyntaxError");
//
//    string retStr7 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"2+\"_)", pkb);
//    REQUIRE(retStr7 == "SyntaxError");
}


TEST_CASE("PatternHandler a(SYNONYM,xx) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: x = 3

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_)", pkb);
    REQUIRE(retStr1 == "1,2,4");

    string retStr2 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,_)", pkb);
    REQUIRE(retStr2 == "k,m,x");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_\"1\"_)", pkb);
    REQUIRE(retStr3 == "2");

    string retStr4 = TestUtility::testDriver("assign a; variable b; Select a pattern a (b,_\"y\"_)", pkb);
    REQUIRE(retStr4 == "1");

    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,_\"y\"_)", pkb);
    REQUIRE(retStr5 == "k");

    string retStr6 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,\"y\")", pkb);
    REQUIRE(retStr6 == "none");

    string retStr7 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,\"3\")", pkb);
    REQUIRE(retStr7 == "x");
}

TEST_CASE("PatternHandler a(QUOTED_IDENT,xx) test") {
    PKB pkb;
    testPatternFillPkb(pkb);

    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;
    // Line 4: x = 3

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

    string retStr7 = TestUtility::testDriver("assign a; Select a pattern a (\"m\",\"1\")", pkb);
    REQUIRE(retStr7 == "none");

    string retStr6 = TestUtility::testDriver("assign a; Select a pattern a (\"x\",\"3\")", pkb);
    REQUIRE(retStr6 == "4");

    string retStr8 = TestUtility::testDriver("assign a; Select a pattern a (\"x\",_\"3\"_)", pkb);
    REQUIRE(retStr8 == "4");

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

    string retStr5 = TestUtility::testDriver("while w; Select w pattern w (\"y\",_) such that Follows(w,6)", pkb);
    REQUIRE(retStr5 == "4");

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

    string retStr5 = TestUtility::testDriver("if i; Select i pattern i (\"x\",_,_) such that Follows*(i, 4)", pkb);
    REQUIRE(retStr5 == "1");

    string retStr3 = TestUtility::testDriver("if i; Select i pattern i (\"t\",_,_)", pkb);
    REQUIRE(retStr3 == "none");

    string retStr4 = TestUtility::testDriver("if i; Select i pattern i (\"t\",_)", pkb);
    REQUIRE(retStr4 == "SyntaxError");

}

TEST_CASE("PatternHandler assign with operators test 1") {
    PKB pkb;
    testPatternFillPkb3(pkb);

    // Line1:  k = x + (y + 4)
    // Line 2: m = 1 + 2 + 3;
    // Line 3: read t;
    // Line 4: x = 1 + 3 * 5

    string retStr1 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"x+y\"_)", pkb);
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"y+4\"_)", pkb);
    REQUIRE(retStr2 == "1");

    string retStr3 = TestUtility::testDriver("assign a; Select a pattern a (_,\"y+4\")", pkb);
    REQUIRE(retStr3 == "none");

    string retStr4 = TestUtility::testDriver("assign a; Select a pattern a (_,_\"1+2\"_)", pkb);
    REQUIRE(retStr4 == "2");

    string retStr8 = TestUtility::testDriver("assign a; Select a pattern a (_,\"1+2\")", pkb);
    REQUIRE(retStr8 == "none");

    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b pattern a (b,\"1+2+3\")", pkb);
    REQUIRE(retStr5 == "m");

    string retStr6 = TestUtility::testDriver("assign a; Select a pattern a (\"x\",_\"1+3\"_)", pkb);
    REQUIRE(retStr6 == "none");

    string retStr7 = TestUtility::testDriver("assign a; Select a pattern a (\"x\",_\"3*5\"_)", pkb);
    REQUIRE(retStr7 == "4");

    string retStr9 = TestUtility::testDriver("assign a; Select a pattern a (\"k\",_\"(y+4)\"_)", pkb);
    REQUIRE(retStr9 == "1");

    string retStr10 = TestUtility::testDriver("assign a; Select a pattern a (\"k\",_\"(y+4\"_)", pkb);
    REQUIRE(retStr10 == "SyntaxError");
}