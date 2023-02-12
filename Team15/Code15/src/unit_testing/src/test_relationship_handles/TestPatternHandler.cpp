#include "PKB.h"
#include "QPS/include/evaluator/PatternHandler.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"

#include "catch.hpp"

string testPattern(string queryStr);

string testPattern(string queryStr, PKB& pkb) {
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator = PQLEvaluator(pkb);
    Query query = preprocessor.preprocess(queryStr);
    string retStr = evaluator.evaluate(query);
    return retStr;
}


TEST_CASE("PatternHandler a(_,_) test empty pkb") {
    PKB pkb;
    string retStr = testPattern("assign a; Select a pattern a (_,_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "None");
}

TEST_CASE("PatternHandler a(_,_) test filled pkb") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    vector<string> rhs = {"x", "y", "+"};
    set<vector<string>> rhsSet = {rhs};
    pkb.addPattern(1, "k", rhsSet);

    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);
    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;

    string retStr = testPattern("assign a; Select a pattern a (_,_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "1,2");
}

TEST_CASE("PatternHandler a(_,UNDERSCORED_EXPR) test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    vector<string> rhs = {"x", "y", "+"};
    set<vector<string>> rhsSet = {rhs};
    pkb.addPattern(1, "k", rhsSet);

    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    // Line1: k = x + y
    // Line 2: m = 1 + 2;

    string retStr1 = testPattern("assign a; Select a pattern a (_,_\"x\"_)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testPattern("assign a; Select a pattern a (_,_\"t\"_)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr3 = testPattern("assign a; Select a pattern a (_,_\"2\"_)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "2");
}


TEST_CASE("PatternHandler a(SYNONYM,_/UNDERSCORED_EXPR) test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);

    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addVar("t");


    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;

    string retStr1 = testPattern("assign a; variable b; Select a pattern a (b,_)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testPattern("assign a; variable b; Select b pattern a (b,_)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "k,m");

    string retStr3 = testPattern("assign a; variable b; Select a pattern a (b,_\"1\"_)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "2");

    string retStr4 = testPattern("assign a; variable b; Select a pattern a (b,_\"y\"_)", pkb);
    cout << retStr4 << endl;
    REQUIRE(retStr4 == "1");

    string retStr5 = testPattern("assign a; variable b; Select b pattern a (b,_\"y\"_)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "k");
}

TEST_CASE("PatternHandler a(QUOTED_IDENT,_/UNDERSCORED_EXPR) test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    vector<string> rhs1 = {"x", "y", "+"};
    set<vector<string>> rhsSet1 = {rhs1};
    pkb.addPattern(1, "k", rhsSet1);

    pkb.addVar("m");
    vector<string> rhs2 = {"1", "2", "+"};
    set<vector<string>> rhsSet2 = {rhs2};
    pkb.addPattern(2, "m", rhsSet2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addVar("t");


    // Line 1: k = x + y;
    // Line 2: m = 1 + 2;
    // Line 3: read t;

    string retStr1 = testPattern("assign a; Select a pattern a (\"k\",_)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testPattern("assign a; Select a pattern a (\"t\",_)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr3 = testPattern("assign a; variable b; Select b pattern a (\"k\", _)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "k,m,t,x,y");

    string retStr4 = testPattern("assign a; Select a pattern a (\"k\",_\"y\"_)", pkb);
    cout << retStr4 << endl;
    REQUIRE(retStr4 == "1");

    string retStr5 = testPattern("assign a; Select a pattern a (\"m\",_\"1\"_)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "2");
}