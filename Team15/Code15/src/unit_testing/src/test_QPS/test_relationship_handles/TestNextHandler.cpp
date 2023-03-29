#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"
#include "TestUtility.h"
#include "catch.hpp"

using namespace std;


string testNext(string queryStr);

string testNext(string queryStr) {
    PKB pkb;
    pkb.addAllProcs({ "main", "proc1", "proc2", "proc3","proc4" });
    pkb.addAllStmts({ {KeywordsEnum::WHILE,{1}}, {KeywordsEnum::IF,{2}},{KeywordsEnum::ASSIGN,{3,4}},{KeywordsEnum::READ ,{5}} });
    pkb.addAllNext({ {1,{2, 5}}, {2, {3, 4}}, {3, {1}}, {4,{1}}, {5,{}} });
    pkb.addAllNextStar({ { 1,{1,2,3,4,5} }, { 2, {1,2,3,4,5} }, {3,{1,2,3,4,5}}, {4,{1,2,3,4,5}}, {5, {}}
        });
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;
}

TEST_CASE("Next/Next* empty pkb") {
    PKB pkb;
    string retStr = TestUtility::testDriver("assign a; Select a such that Next(1, 3)", pkb);
    REQUIRE(retStr == "none");

    string retStr1 = TestUtility::testDriver("assign a; Select a such that Next(a,_)", pkb);
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("variable v; stmt p; Select v such that Next*(1,_)", pkb);
    //cout << retStr2 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable v; stmt p; Select a such that Next*(_,a)", pkb);
    //cout << retStr3 << endl;
    REQUIRE(retStr3 == "none");
}

TEST_CASE("Next/Next* (Integer, Integer)") {

    string retStr1 = testNext("stmt a; Select a such that Next(1, 2)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4,5");

    string retStr6 = testNext("stmt a; Select a such that Next(1, 1)");
    //cout << retStr1 << endl;
    REQUIRE(retStr6 == "none");

    string retStr2 = testNext("stmt p; Select p such that Next(1, 3)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testNext("stmt p; Select p such that Next*(1, 5)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p; Select p such that Next*(2, 1)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4,5");

    string retStr5 = testNext("stmt p; Select p such that Next*(4, 4)");
    //cout << retStr2 << endl;
    REQUIRE(retStr5 == "1,2,3,4,5");
}

TEST_CASE("Next/Next* (Integer, _)") {

    string retStr1 = testNext("stmt a; Select a such that Next(1, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4,5");

    string retStr2 = testNext("stmt p; Select p such that Next(5, _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testNext("stmt p; Select p such that Next*(3, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p; Select p such that Next*(5, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Next/Next* (Integer, Stmt)") {

    string retStr1 = testNext("stmt a; Select a such that Next(1, a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,5");

    string retStr2 = testNext("stmt p; Select p such that Next(5, p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr3 = testNext("stmt p; Select p such that Next*(2, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p; Select p such that Next*(4, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4,5");
}

TEST_CASE("Next/Next* semantic error test") {

    string retStr1 = testNext("assign a; Select a such that Next(a, \"x\")");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "SyntaxError");

    string retStr2 = testNext("variable v; Select v such that Next(_, v)");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "SemanticError");
}

TEST_CASE("Next/Next* (Stmt, Integer)") {
    string retStr1 = testNext("stmt a; Select a such that Next(a, 3)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "2");

    string retStr2 = testNext("stmt p; Select p such that Next(p, 1)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "3,4");

    string retStr3 = testNext("stmt p; Select p such that Next*(p, 3)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4");

    string retStr4 = testNext("stmt p; Select p such that Next*(p, 5)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4");
}

TEST_CASE("Next/Next* (Stmt, Stmt)") {
    string retStr1 = testNext("stmt a,b; Select a such that Next(a, b)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4");

    string retStr2 = testNext("stmt p; Select p such that Next(p, p)");
    //cout << retStr3 << endl;
    REQUIRE(retStr2 == "none");

    string retStr5 = testNext("stmt p,q; Select q such that Next(p, q)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "1,2,3,4,5");

    string retStr3 = testNext("stmt p,q; Select q such that Next*(p, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p; Select p such that Next*(p, p)");
    REQUIRE(retStr4 == "none");
}

TEST_CASE("Next/Next* (Stmt, _)") {
    string retStr1 = testNext("stmt a,b; Select a such that Next(a, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4");

    string retStr5 = testNext("stmt p,q; Select q such that Next(p, _)");
    //cout << retStr3 << endl;
    REQUIRE(retStr5 == "1,2,3,4,5");

    string retStr3 = testNext("stmt p,q; Select q such that Next*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p; Select p such that Next*(p, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4");
}

TEST_CASE("Next/Next* (_, _)") {

    string retStr1 = testNext("stmt a; Select a such that Next(_, _)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4,5");

    string retStr3 = testNext("stmt p; Select p such that Next*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p,q; Select q such that Next*(_, _)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4,5");
}

TEST_CASE("Next/Next* (_, Stmt)") {

    string retStr1 = testNext("stmt a; Select a such that Next(_, a)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4,5");

    string retStr3 = testNext("stmt p; Select p such that Next*(_, p)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p,q; Select p such that Next*(_, q)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4,5");
}

TEST_CASE("Next/Next* (_, Integer)") {

    string retStr1 = testNext("stmt a; Select a such that Next(_, 1)");
    //cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2,3,4,5");

    string retStr3 = testNext("stmt p; Select p such that Next*(_, 3)");
    //cout << retStr2 << endl;
    REQUIRE(retStr3 == "1,2,3,4,5");

    string retStr4 = testNext("stmt p,q; Select p such that Next*(_, 5)");
    //cout << retStr2 << endl;
    REQUIRE(retStr4 == "1,2,3,4,5");
}