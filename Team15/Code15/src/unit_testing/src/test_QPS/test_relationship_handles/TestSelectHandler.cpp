#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/evaluator/SelectHandler.h"
#include "PKBStub.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Select Handler test 1") {
    SelectClause selectClause("r");
    std::multimap<std::string, std::string> varTable;
    ResultTable resultTable = ResultTable();

    varTable.insert(pair<std::string, std::string>("a1", "="));
    varTable.insert(pair<std::string, std::string>("a2", "="));
    varTable.insert(pair<std::string, std::string>("r", "read"));
    varTable.insert(pair<std::string, std::string>("i", "if"));
    varTable.insert(pair<std::string, std::string>("w", "while"));
    varTable.insert(pair<std::string, std::string>("c", "constant"));
    varTable.insert(pair<std::string, std::string>("ca", "call"));
    varTable.insert(pair<std::string, std::string>("p", "procedure"));

    PKB pkb;
  
    pkb.addProc("p");
    pkb.addStmt("=", 1);
    pkb.addStmt("=", 2);
    pkb.addStmt("read", 3);
    pkb.addStmt("read", 7);
    pkb.addStmt("read", 8);
    pkb.addStmt("if", 4);
    pkb.addStmt("while", 5);
    pkb.addStmt("call", 6);
    pkb.addVar("x");
    pkb.addVar("y");
    pkb.addVar("z");
    pkb.addConst("10");
    pkb.addConst("11");
    pkb.addConst("12");
    pkb.addConst("13");

    SelectHandler selectHandler = SelectHandler(pkb);
    std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

    set<std::string> retSet = resultTable.getStringSetFromKey(selectedVarName);
    REQUIRE(selectedVarName == "r");
    REQUIRE(retSet.size() == 3);
    REQUIRE(retSet.count("3") == 1);
    REQUIRE(retSet.count("7") == 1);
    REQUIRE(retSet.count("8") == 1);
}

TEST_CASE("Select Handler test 2") {

        PQLPreprocessor preprocessor;
        string queryStr = "constant c; Select c";
        Query query = Query();
        query = preprocessor.preprocess(queryStr);
        SelectClause selectClause = query.getSelectClause();

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        ResultTable resultTable = ResultTable();

        PKB pkb;

        pkb.addConst("10");
        pkb.addConst("11");
        pkb.addConst("12");
        pkb.addConst("13");

        SelectHandler selectHandler = SelectHandler(pkb);
        std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

        set<std::string> retSet = resultTable.getStringSetFromKey(selectedVarName);
        REQUIRE(selectedVarName == "c");
        REQUIRE(retSet.size() == 4);
        REQUIRE(retSet.count("10") == 1);
        REQUIRE(retSet.count("11") == 1);
        REQUIRE(retSet.count("12") == 1);
        REQUIRE(retSet.count("13") == 1);

}