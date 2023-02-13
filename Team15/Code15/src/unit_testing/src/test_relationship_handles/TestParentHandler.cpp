#include "PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/SelectHandler.h"
#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/evaluator/ParentHandler.h"

#include "PKBStub.h"
#include <assert.h>
#include "catch.hpp"

using namespace std;

string testParent(string queryStr);

string testParent(string queryStr, PKB& pkb) {
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator = PQLEvaluator(pkb);
    Query query = preprocessor.preprocess(queryStr);
    string retStr = evaluator.evaluate(query);
    return retStr;
}

TEST_CASE("Parent Integer Underscore test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1,2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);

    string retStr1 = testParent("assign a; while w; Select a such that Parent(1, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,4");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(1, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select a such that Parent(3, _)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent(5, _)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("Parent* Integer Underscore test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(1, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,4");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent*(1, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select a such that Parent*(3, _)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent*(5, _)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "k,x,y");
}



TEST_CASE("Parent Underscore Integer test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);

    string retStr1 = testParent("assign a; while w; Select a such that Parent(_, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,4");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(_, 1)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select a such that Parent(_, 2)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "2,4");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent(_, 5)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");

}


TEST_CASE("Parent* Underscore Integer test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(_, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,4");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent*(_, 1)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select b such that Parent*(_, 2)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "k,x,y");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent*(_, 5)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("Parent Integer Integer test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);

    string retStr1 = testParent("assign a; while w; Select a such that Parent(2, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "None");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(1, 2)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select a such that Parent(3, 2)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent(5, 2)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("Parent* Integer Integer test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);
    set<int> childSet1{ 2 };
    pkb.addParentStar(1, childSet1);
    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);
    set<int> childSet2{ 1,2 };
    pkb.addParentStar(5, childSet2);

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(2, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "None");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent*(1, 2)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; variable b; Select a such that Parent*(3, 2)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testParent("assign a; variable b; Select b such that Parent*(5, 2)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "k,x,y");
}

TEST_CASE("Parent Synonym Integer test") {
    PKB pkb;
    pkb.addStmt(Tokens::Keyword::WHILE, 1);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");
    pkb.addParent(1, 2);

    pkb.addStmt(Tokens::Keyword::READ, 3);
    pkb.addStmt(Tokens::Keyword::ASSIGN, 4);
    pkb.addStmt(Tokens::Keyword::WHILE, 5);
    pkb.addParent(5, 1);

    string retStr1 = testParent("assign a; while w; Select a such that Parent(w, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2,4");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(w, 2)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1");

    string retStr5 = testParent("assign a; variable b; Select b such that Parent(a, 2)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}
