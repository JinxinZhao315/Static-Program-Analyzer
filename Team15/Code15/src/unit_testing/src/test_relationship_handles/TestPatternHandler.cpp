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
    string retStr = testPattern("assign a; Select a pattern a (_,_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "1");
}

TEST_CASE("PatternHandler a(_,UNDERSCORED_EXPR) test filled pkb 1") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    vector<string> rhs = {"x", "y", "+"};
    set<vector<string>> rhsSet = {rhs};
    pkb.addPattern(1, "k", rhsSet);

    string retStr = testPattern("assign a; Select a pattern a (_,_\"x\"_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "1");
}

TEST_CASE("PatternHandler a(_,UNDERSCORED_EXPR) test filled pkb 2") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::ASSIGN, 1);
    vector<string> rhs = {"x", "y", "+"};
    set<vector<string>> rhsSet = {rhs};
    pkb.addPattern(1, "k", rhsSet);

    string retStr = testPattern("assign a; Select a pattern a (_,_\"t\"_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "None");
}

TEST_CASE("PatternHandler a(SYNONYM,_) test filled pkb 1") {
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

    // Line 1: k = x + y
    // Line 2: m = 1 + 2

    string retStr = testPattern("assign a; variable b; Select a pattern a (b,_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "1,2");
}

TEST_CASE("PatternHandler a(SYNONYM,_) test filled pkb 2") {
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

    // Line 1: k = x + y
    // Line 2: m = 1 + 2

    string retStr = testPattern("assign a; variable b; Select b pattern a (b,_)", pkb);
    cout << retStr << endl;
    REQUIRE(retStr == "k,m");
}