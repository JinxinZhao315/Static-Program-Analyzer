#include "PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/evaluator/ModifiesSHandler.h"


#include "catch.hpp"

using namespace std;

string testModifiesS(string queryStr);

string testModifiesS(string queryStr, PKB& pkb) {
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator = PQLEvaluator(pkb);
    Query query = preprocessor.preprocess(queryStr);
    string retStr = evaluator.evaluate(query);
    return retStr;
}


TEST_CASE("ModifiesS Integer Underscore test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });
    
    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(1, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testModifiesS("assign a; variable b; Select b  such that Modifies(1, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "k,x,y");

    string retStr3 = testModifiesS("assign a; variable b; Select a such that Modifies(2, _)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testModifiesS("assign a; variable b; Select b such that Modifies(2, _)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("ModifiesS Integer IdentString test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(1, \"k\")", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testModifiesS("assign a; variable b; Select b  such that Modifies(1, \"x\")", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "None");

    string retStr3 = testModifiesS("assign a; variable b; Select a such that Modifies(2, \"x\")", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testModifiesS("assign a; variable b; Select b such that Modifies(3, \"x\")", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "k,x,y");
}

TEST_CASE("ModifiesS Integer Variable test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(1, b)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testModifiesS("assign a; variable b; Select b  such that Modifies(1, b)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "k");

    //Assume one synonmy empty then all empty(not the case waiting for change)
    string retStr3 = testModifiesS("assign a; variable b; Select a such that Modifies(2, b)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testModifiesS("assign a; variable b; Select b such that Modifies(3, b)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "x");
}



TEST_CASE("ModifiesS Statement Variable test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(a, b)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testModifiesS("assign a; variable b; read r; Select r  such that Modifies(r, b)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "3");

    string retStr3 = testModifiesS("assign a; variable b; call c; Select c such that Modifies(c, b)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");

}


TEST_CASE("ModifiesS Statement IdentString test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(a, \"k\")", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1");

    string retStr2 = testModifiesS("assign a; variable b; read r; Select r  such that Modifies(r, \"x\")", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "3");

    string retStr3 = testModifiesS("assign a; variable b; Select a such that Modifies(a, \"d\")", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testModifiesS("assign a; variable b; Select b such that Modifies(a, \"x\")", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "None");
}

TEST_CASE("ModifiesS Statement Underscore test") {
    PKB pkb;
    pkb.addStmt("assign", 1);
    pkb.addStmt("assign", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });
    pkb.addModifiesStmt(1, set1);

    set<string> set2({ "y" });
    pkb.addModifiesStmt(2, set2);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });
    pkb.addModifiesStmt(3, set3);


    string retStr1 = testModifiesS("assign a; variable b; Select a such that Modifies(a, _)", pkb);
    cout << retStr1 << endl;
    REQUIRE(retStr1 == "1,2");

    string retStr2 = testModifiesS("assign a; variable b; read r; Select r  such that Modifies(r, _)", pkb);
    cout << retStr2 << endl;
    REQUIRE(retStr2 == "3");

    string retStr3 = testModifiesS("assign a; variable b; call c; Select c such that Modifies(c, _)", pkb);
    cout << retStr3 << endl;
    REQUIRE(retStr3 == "None");


    string retStr5 = testModifiesS("assign a; variable b; Select b such that Modifies(a, _)", pkb);
    cout << retStr5 << endl;
    REQUIRE(retStr5 == "k,x,y");
}

