#include "pkb/include/PKB.h"
#include "qps/include/PQLDriver.h"
#include "TestUtility.h"
#include "catch.hpp"

using namespace std;

string testWith(string queryStr);

string testWith(string queryStr) {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 2 })));
    stmts.insert(make_pair(KeywordsEnum::IF, set<int>({ 3 })));
    stmts.insert(make_pair(KeywordsEnum::PRINT, set<int>({ 4 })));
    stmts.insert(make_pair(KeywordsEnum::CALL, set<int>({ 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 6 })));
    pkb.addAllStmts(stmts);

    pkb.addAllWithCall({ {5, "foo"} });
    pkb.addAllWithPrint({ {4, "x"} });
    pkb.addAllWithRead({ {6, "x"} });
    pkb.addAllCalls({ {"main", {"foo"}} });
    pkb.addAllVars({ "x" });
    pkb.addAllConsts({ "1", "2" });
    pkb.addAllProcs({ "main", "foo" });
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;

    /*
    procedure main{
        x = x + 1;--------------------1
        while (x > 1){----------------2
            if (x < 2) {--------------3
                print x;--------------4
            } else {
                call foo;-------------5
            }
        }
    }
    procedure foo{
        read x;-----------------------6
    }
    procedure: main, foo
    variable: x
    constant: 1, 2
    assign: 1
    while: 2
    if: 3
    print: 4
    call: 5
    read: 6
    */
}

TEST_CASE("With procedure positive test") {
    string retStr1 = testWith("procedure p1; Select p1 with p1.procName=\"main\"");
    REQUIRE(retStr1 == "main");

    string retStr2 = testWith("procedure p1, p2; Select p1 with p1.procName=p2.procName");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "foo,main");
}

TEST_CASE("With call positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("call c1; Select c1 with c1.stmt#=5");
    REQUIRE(retStr1 == "5");

    string retStr2 = testWith("call c1; Select c1 with c1.procName=\"foo\"");
    REQUIRE(retStr2 == "5");
}

TEST_CASE("With variable positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("variable v; Select v with v.varName=\"x\"");
    REQUIRE(retStr1 == "x");

    string retStr2 = testWith("variable v1, v2; Select v1 with v1.varName=v2.varName");
    REQUIRE(retStr2 == "x");
}

TEST_CASE("With read positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("read r; Select r with r.varName=\"x\"");
    REQUIRE(retStr1 == "6");

    string retStr2 = testWith("read r; Select r with r.stmt#=6");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "6");
}

TEST_CASE("With print positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("print pri; Select pri with pri.varName=\"x\"");
    REQUIRE(retStr1 == "4");

    string retStr2 = testWith("print pri; Select pri with pri.stmt#=4");
    //cout << retStr1 << endl;
    REQUIRE(retStr2 == "4");
}

TEST_CASE("With const positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("constant c; Select c with c.value=2");
    REQUIRE(retStr1 == "2");
    string retStr2 = testWith("constant c; Select c with c.value=10");
    REQUIRE(retStr2 == "none");
}

TEST_CASE("With stmt positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("stmt s; Select s with s.stmt#=1");
    REQUIRE(retStr1 == "1");
    string retStr2 = testWith("stmt s; Select s with s.stmt#=7");
    REQUIRE(retStr2 == "none");
}
TEST_CASE("With while positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("while w; Select w with w.stmt#=2");
    REQUIRE(retStr1 == "2");

    string retStr2 = testWith("while w; Select w with w.stmt#=1");
    REQUIRE(retStr2 == "none");
}
TEST_CASE("With if positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("if i; Select i with i.stmt#=3");
    REQUIRE(retStr1 == "3");

    string retStr2 = testWith("if i; Select i with i.stmt#=4");
    REQUIRE(retStr2 == "none");
}
TEST_CASE("With assign positive test") {
    PKB pkb;
    PQLDriver driver = PQLDriver(pkb);

    string retStr1 = testWith("assign a; Select a with a.stmt#=1");
    REQUIRE(retStr1 == "1");

    string retStr2 = testWith("assign a; Select a with a.stmt# = 7");
    REQUIRE(retStr2 == "none");
}