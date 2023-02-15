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

TEST_CASE("Parent* Synonym Integer test") {
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

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(a, 1)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "None");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent*(w, 2)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a; while w; Select w such that Parent*(w, 1)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "5");


    string retStr5 = testParent("assign a; variable b; Select a such that Parent*(a, 2)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("Parent Integer Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select a such that Parent(1, a)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(2, w)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr5 = testParent("assign a; while w; Select w such that Parent(5, w)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "1");

    string retStr6 = testParent("assign a; while w; Select a such that Parent(5, w)", pkb);
    cout << retStr6 << endl;
    REQUIRE(retStr6 == "2,4");
}

TEST_CASE("Parent* Integer Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(1, a)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent*(5, a)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "2");

    string retStr3 = testParent("assign a; while w; Select w such that Parent*(1, w)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testParent("assign a;  while w; Select w such that Parent*(5, w)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "1");
}

TEST_CASE("Parent Synonym Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select a such that Parent(w, a)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent(a, w)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr5 = testParent("assign a; while w1, w2; Select w1 such that Parent(w1, w2)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "5");

    string retStr6 = testParent("assign a; while w1, w2; Select w2 such that Parent(w1, w2)", pkb);
    cout << retStr6 << endl;
    REQUIRE(retStr6 == "1");

    string retStr7 = testParent("assign a; read r; while w1, w2; Select r such that Parent(r, w1)", pkb);
    cout << retStr7 << endl;
    REQUIRE(retStr7 == "None");
}

TEST_CASE("Parent* Synonym Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select a such that Parent*(w, a)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "2");

    string retStr2 = testParent("assign a; while w; Select w  such that Parent*(w, a)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "1,5");

    string retStr3 = testParent("assign a;  while w1, w2; Select w2 such that Parent*(w1, w2)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "1");


    string retStr5 = testParent("assign a;   while w1, w2; Select w2 such that Parent*(w2, w1)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "5");
}

TEST_CASE("Parent Synonym Underscore test") {
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

    string retStr1 = testParent("assign a; while w; Select w such that Parent(w, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,5");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent(a, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr7 = testParent("assign a; read r; while w1, w2; Select r such that Parent(r, _)", pkb);
    cout << retStr7 << endl;
    REQUIRE(retStr7 == "None");
}

TEST_CASE("Parent* Synonym Underscore test") {
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

    string retStr1 = testParent("assign a; while w; Select w such that Parent*(w, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,5");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent*(a, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

}

TEST_CASE("Parent Underscore Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select w such that Parent(_, w)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent(_, a)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "2");

    string retStr7 = testParent("assign a; read r; while w1, w2; Select r such that Parent(_, a)", pkb);
    cout << retStr7 << endl;
    REQUIRE(retStr7 == "3");
}

TEST_CASE("Parent* Underscore Synonym test") {
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

    string retStr1 = testParent("assign a; while w; Select w such that Parent*(_, w)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent*(_, a)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "2");

}

TEST_CASE("Parent/Parent* Underscore Underscore test") {
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

    PKB pkbEmpty;
    pkbEmpty.addStmt(Tokens::Keyword::CALL, 1);
    pkbEmpty.addStmt(Tokens::Keyword::PRINT, 2);

    string retStr1 = testParent("assign a; while w; Select w such that Parent(_, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,5");

    string retStr2 = testParent("assign a; while w; Select a  such that Parent(_, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "2,4");

    string retStr7 = testParent("assign a; read r; while w1, w2; Select r such that Parent(_, _)", pkb);
    cout << retStr7 << endl;
    REQUIRE(retStr7 == "3");

    string retStr8 = testParent("assign a; read r; while w1, w2; call c; Select c such that Parent(_, _)", pkbEmpty);
    cout << retStr8 << endl;
    REQUIRE(retStr8 == "None");

    string retStr9 = testParent("assign a; read r; while w1, w2; call c; Select r such that Parent(_, _)", pkbEmpty);
    cout << retStr9 << endl;
    REQUIRE(retStr9 == "None");
}
