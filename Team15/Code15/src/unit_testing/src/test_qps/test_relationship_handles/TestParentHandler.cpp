#include "pkb/include/PKB.h"
#include "qps/include/PQLDriver.h"
#include "TestUtility.h"
#include "catch.hpp"


TEST_CASE("Parent Integer Underscore test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1,{2});

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(1, _)", pkb);
    REQUIRE(retStr1 == "2,4");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(1, _)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Parent(3, _)", pkb);
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent(5, _)", pkb);
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Parent* Integer Underscore test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });

    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(1, _)", pkb);
    REQUIRE(retStr1 == "2,4");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent*(1, _)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Parent*(3, _)", pkb);
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent*(5, _)", pkb);
    REQUIRE(retStr5 == "k,x,y");
}



TEST_CASE("Parent Underscore Integer test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(_, 1)", pkb);
    REQUIRE(retStr1 == "2,4");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(_, 1)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Parent(_, 2)", pkb);
    REQUIRE(retStr3 == "2,4");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent(_, 5)", pkb);
    REQUIRE(retStr5 == "none");

}


TEST_CASE("Parent* Underscore Integer test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(_, 1)", pkb);
    REQUIRE(retStr1 == "2,4");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent*(_, 1)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select b such that Parent*(_, 2)", pkb);
    REQUIRE(retStr3 == "k,x,y");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent*(_, 5)", pkb);
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Parent Integer Integer test") {
    PKB pkb;
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, {2});

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, {1});
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(2, 1)", pkb);
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(1, 2)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Parent(3, 2)", pkb);
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent(5, 2)", pkb);
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Parent* Integer Integer test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(2, 1)", pkb);
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent*(1, 2)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Parent*(3, 2)", pkb);
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent*(5, 2)", pkb);
    REQUIRE(retStr5 == "k,x,y");
}

TEST_CASE("Parent Synonym Integer test") {
    PKB pkb;
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(w, 1)", pkb);
    REQUIRE(retStr1 == "2,4");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(w, 2)", pkb);
    REQUIRE(retStr2 == "1");

    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Parent(a, 2)", pkb);
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Parent* Synonym Integer test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(a, 1)", pkb);
    REQUIRE(retStr1 == "none");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent*(w, 2)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a; while w; Select w such that Parent*(w, 1)", pkb);
    REQUIRE(retStr3 == "5");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select a such that Parent*(a, 2)", pkb);
    REQUIRE(retStr5 == "none");
}

TEST_CASE("Parent Integer Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(1, a)", pkb);
    REQUIRE(retStr1 == "2");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(2, w)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr5 = TestUtility::testDriver("assign a; while w; Select w such that Parent(5, w)", pkb);
    REQUIRE(retStr5 == "1");

    string retStr6 = TestUtility::testDriver("assign a; while w; Select a such that Parent(5, w)", pkb);
    REQUIRE(retStr6 == "2,4");
}

TEST_CASE("Parent* Integer Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(1, a)", pkb);
    REQUIRE(retStr1 == "2");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent*(5, a)", pkb);
    REQUIRE(retStr2 == "2");

    string retStr3 = TestUtility::testDriver("assign a; while w; Select w such that Parent*(1, w)", pkb);
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a;  while w; Select w such that Parent*(5, w)", pkb);
    REQUIRE(retStr5 == "1");
}

TEST_CASE("Parent Synonym Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent(w, a)", pkb);
    REQUIRE(retStr1 == "2");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent(a, w)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr5 = TestUtility::testDriver("assign a; while w1, w2; Select w1 such that Parent(w1, w2)", pkb);
    REQUIRE(retStr5 == "5");

    string retStr6 = TestUtility::testDriver("assign a; while w1, w2; Select w2 such that Parent(w1, w2)", pkb);
    REQUIRE(retStr6 == "1");

    string retStr7 = TestUtility::testDriver("assign a; read r; while w1, w2; Select r such that Parent(r, w1)", pkb);
    REQUIRE(retStr7 == "none");
}

TEST_CASE("Parent* Synonym Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });

    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select a such that Parent*(w, a)", pkb);
    REQUIRE(retStr1 == "2");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select w  such that Parent*(w, a)", pkb);
    REQUIRE(retStr2 == "1,5");

    string retStr3 = TestUtility::testDriver("assign a;  while w1, w2; Select w2 such that Parent*(w1, w2)", pkb);
    REQUIRE(retStr3 == "1");


    string retStr5 = TestUtility::testDriver("assign a;   while w1, w2; Select w2 such that Parent*(w2, w1)", pkb);
    REQUIRE(retStr5 == "5");
}

TEST_CASE("Parent Synonym Underscore test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });

    string retStr1 = TestUtility::testDriver("assign a; while w; Select w such that Parent(w, _)", pkb);
    REQUIRE(retStr1 == "1,5");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent(a, _)", pkb);
    REQUIRE(retStr2 == "none");

    string retStr7 = TestUtility::testDriver("assign a; read r; while w1, w2; Select r such that Parent(r, _)", pkb);
    REQUIRE(retStr7 == "none");
}

TEST_CASE("Parent* Synonym Underscore test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });

    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select w such that Parent*(w, _)", pkb);
    REQUIRE(retStr1 == "1,5");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent*(a, _)", pkb);
    REQUIRE(retStr2 == "none");

}

TEST_CASE("Parent Underscore Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select w such that Parent(_, w)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent(_, a)", pkb);
    REQUIRE(retStr2 == "2");

    string retStr7 = TestUtility::testDriver("assign a; read r; while w1, w2; Select r such that Parent(_, a)", pkb);
    REQUIRE(retStr7 == "3");
}

TEST_CASE("Parent* Underscore Synonym test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });

    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, { 1 });
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);
    */

    string retStr1 = TestUtility::testDriver("assign a; while w; Select w such that Parent*(_, w)", pkb);
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent*(_, a)", pkb);
    REQUIRE(retStr2 == "2");

}

TEST_CASE("Parent/Parent* Underscore Underscore test") {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 1, 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    pkb.addAllParent({ {1, {2}}, {5, {1}} });
    pkb.addAllParentStar({ {1, {2}}, {5, {1, 2} } });
    //do not add one by one to pkb
    /*
    pkb.addStmt(::WHILE, 1);
    pkb.addStmt(KeywordsEnum::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, { 2 });

    pkb.addStmt(::READ, 3);
    pkb.addStmt(::ASSIGN, 4);
    pkb.addStmt(::WHILE, 5);
    pkb.addParent(5, {1});
    */

    PKB pkbEmpty;
    //pkbEmpty.addStmt("call", 1);
    //pkbEmpty.addStmt("print", 2);
    

    string retStr1 = TestUtility::testDriver("assign a; while w; Select w such that Parent(_, _)", pkb);
    REQUIRE(retStr1 == "1,5");

    string retStr2 = TestUtility::testDriver("assign a; while w; Select a  such that Parent(_, _)", pkb);
    REQUIRE(retStr2 == "2,4");

    string retStr7 = TestUtility::testDriver("assign a; read r; while w1, w2; Select r such that Parent(_, _)", pkb);
    REQUIRE(retStr7 == "3");

    string retStr8 = TestUtility::testDriver("assign a; read r; while w1, w2; call c; Select c such that Parent(_, _)", pkbEmpty);
    REQUIRE(retStr8 == "none");

    string retStr9 = TestUtility::testDriver("assign a; read r; while w1, w2; call c; Select r such that Parent(_, _)", pkbEmpty);
    REQUIRE(retStr9 == "none");
}

