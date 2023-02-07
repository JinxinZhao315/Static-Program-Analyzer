#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/SelectHandler.h"
#include "PKBStub.h"
#include "source_processor/include/parser/Tokens.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Select Handler test 1") {
    try {
        std::cout << "hello" << std::endl;
        SelectClause selectClause("r");
        std::multimap<std::string, std::string> varTable;
        ResultTable resultTable = ResultTable();

        varTable.insert(pair<std::string, std::string>("a1", "assign"));
        varTable.insert(pair<std::string, std::string>("a2", "assign"));
        varTable.insert(pair<std::string, std::string>("r", "read"));
        varTable.insert(pair<std::string, std::string>("i", "if"));
        varTable.insert(pair<std::string, std::string>("w", "while"));
        varTable.insert(pair<std::string, std::string>("c", "constant"));
        varTable.insert(pair<std::string, std::string>("ca", "call"));
        varTable.insert(pair<std::string, std::string>("p", "procedure"));

        //std::set<std::string> constSet{ "10", "11", "12", "13" };
        //std::set<std::string> varNameSet{ "x", "y", "z" };
        //std::set<int> stmtNumberByType{ 1, 2, 3 };
        //std::set<int> stmtNums{ 1, 2, 3 };

        //PKB pkb = PKBStub(constSet, varNameSet, stmtNumberByType, stmtNums);
        PKB pkb;
  
        pkb.addProc("p");
        pkb.addStmt(Tokens::ASSIGN, 1);
        pkb.addStmt(Tokens::ASSIGN, 2);
        pkb.addStmt(Tokens::READ, 3);
        pkb.addStmt(Tokens::READ, 7);
        pkb.addStmt(Tokens::READ, 8);
        pkb.addStmt(Tokens::IF, 4);
        pkb.addStmt(Tokens::WHILE, 5);
        pkb.addStmt(Tokens::CALL, 6);
        pkb.addVar("x");
        pkb.addVar("y");
        pkb.addVar("z");
        pkb.addConst("10");
        pkb.addConst("11");
        pkb.addConst("12");
        pkb.addConst("13");

        SelectHandler selectHandler = SelectHandler(pkb);
        std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

        assert(selectedVarName == "r");
        std::set<std::string> result = resultTable.getValueFromKey("r");

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}

TEST_CASE("Select Handler test 2") {

        PQLPreprocessor preprocessor;
        std::cout << "hello" << std::endl;
        string queryStr = "constant c; Select c";
        Query query = Query();
        query = preprocessor.preprocess(queryStr);
        SelectClause selectClause = query.getSelectClause();

        std::multimap<std::string, std::string> varTable = query.getVarTable();
        ResultTable resultTable = ResultTable();

        //std::set<std::string> constSet{ "10", "11", "12", "13" };
        //std::set<std::string> varNameSet{ "x", "y", "z" };
        //std::set<int> stmtNumberByType{ 1, 2, 3 };
        //std::set<int> stmtNums{ 1, 2, 3 };

        //PKB pkb = PKBStub(constSet, varNameSet, stmtNumberByType, stmtNums);
        PKB pkb;

        pkb.addConst("10");
        pkb.addConst("11");
        pkb.addConst("12");
        pkb.addConst("13");

        SelectHandler selectHandler = SelectHandler(pkb);
        std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

        assert(selectedVarName == "c");
        std::set<std::string> result = resultTable.getValueFromKey("c");
        std::cout << "results:" << endl;
        for (auto s: result) {
            std::cout << s  << endl;
        }

        std::cout << "select handler successful" << std::endl;

}