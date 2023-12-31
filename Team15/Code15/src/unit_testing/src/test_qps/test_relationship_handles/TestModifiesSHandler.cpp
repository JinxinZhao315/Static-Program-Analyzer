#include "pkb/include/PKB.h"
#include "qps/include/evaluator/PQLEvaluator.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/ResultTable.h"
#include "qps/include/evaluator/ClauseHandler.h"
#include "TestUtility.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("ModifiesS Integer Underscore test") {
    PKB pkb;
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    pkb.addAllModifiesStmt({ {1, set1} });

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
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    set<string> set3({ "x" });
    pkb.addAllModifiesStmt({ {1, set1}, {3, set3} });

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
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    set<string> set3({ "x" });
    pkb.addAllModifiesStmt({ {1, set1}, {3, set3} });

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

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    set<string> set3({ "x" });
    pkb.addAllModifiesStmt({ {1, set1}, {3, set3} });

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, b)", pkb);
    
    REQUIRE(retStr1 == "1");

    string retStr2 = TestUtility::testDriver("assign a; variable b; read r; Select r  such that Modifies(r, b)", pkb);
    
    REQUIRE(retStr2 == "3");

    string retStr3 = TestUtility::testDriver("assign a; variable b; call c; Select c such that Modifies(c, b)", pkb);
    
    REQUIRE(retStr3 == "none");

}


TEST_CASE("ModifiesS Statement IdentString test") {
    PKB pkb;
    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    set<string> set3({ "x" });
    pkb.addAllModifiesStmt({ {1, set1}, {3, set3} });

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

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x", "y", "k" });

    set<string> set1({ "k" });
    set<string> set2({ "y" });
    set<string> set3({ "x" });
    pkb.addAllModifiesStmt({ {1, set1}, {2, set2}, {3, set3} });

    string retStr1 = TestUtility::testDriver("assign a; variable b; Select a such that Modifies(a, _)", pkb);
    
    REQUIRE(retStr1 == "1,2");

    string retStr2 = TestUtility::testDriver("assign a; variable b; read r; Select r  such that Modifies(r, _)", pkb);
    
    REQUIRE(retStr2 == "3");

    string retStr3 = TestUtility::testDriver("assign a; variable b; call c; Select c such that Modifies(c, _)", pkb);
    
    REQUIRE(retStr3 == "none");


    string retStr5 = TestUtility::testDriver("assign a; variable b; Select b such that Modifies(a, _)", pkb);
    
    REQUIRE(retStr5 == "k,x,y");
}

