#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/evaluator/ModifiesSHandler.h"
#include "TestUtility.h"


#include "catch.hpp"

using namespace std;

TEST_CASE("ModifiesS Integer Underscore test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });
    
    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(1, _)", pkb);
    
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; Select b  such that Modifies(1, _)", pkb);
    
    REQUIRE(retStr2 == "k,x,y");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(2, _)", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(2, _)", pkb);
    
    REQUIRE(retStr5 == "none");
}

TEST_CASE("ModifiesS Integer IdentString test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(1, \"k\")", pkb);
    
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; Select b  such that Modifies(1, \"x\")", pkb);
    
    REQUIRE(retStr2 == "none");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(2, \"x\")", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(3, \"x\")", pkb);
    
    REQUIRE(retStr5 == "k,x,y");
}

TEST_CASE("ModifiesS Integer Variable test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(1, b)", pkb);
    
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; Select b  such that Modifies(1, b)", pkb);
    
    REQUIRE(retStr2 == "k");

    //Assume one synonmy empty then all empty(not the case waiting for change)
    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(2, b)", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(3, b)", pkb);
    
    REQUIRE(retStr5 == "x");
}



TEST_CASE("ModifiesS Statement Variable test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, b)", pkb);
    
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable b; read r; Select r  such that Modifies(r, b)", pkb);
    
    REQUIRE(retStr2 == "3");

    string retStr3 = TestUtility::testDriver("assign a; variable b; call c; Select c such that Modifies(c, b)", pkb);
    
    REQUIRE(retStr3 == "none");

}


TEST_CASE("ModifiesS Statement IdentString test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("k");

    set<string> set1({ "k" });

    pkb.addModifiesStmt(1, set1);

    pkb.addStmt("read", 3);

    set<string> set3({ "x" });

    pkb.addModifiesStmt(3, set3);

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, \"k\")", pkb);
    
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable b; read r; Select r  such that Modifies(r, \"x\")", pkb);
    
    REQUIRE(retStr2 == "3");

    string retStr3 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, \"d\")", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(a, \"x\")", pkb);
    
    REQUIRE(retStr5 == "none");
}

TEST_CASE("ModifiesS Statement Underscore test") {
    PKB pkb;
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);

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


    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, _)", pkb);
    
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; read r; Select r  such that Modifies(r, _)", pkb);
    
    REQUIRE(retStr2 == "3");

    string retStr3 = TestUtility::testDriver("assign a; variable b; call c; Select c such that Modifies(c, _)", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(a, _)", pkb);
    
    REQUIRE(retStr5 == "k,x,y");
}

