#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/SelectHandler.h"
#include "PKBStub.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Select Handler test 1") {
    try {
        std::cout << "hello" << std::endl;
        SelectClause selectClause("a1");
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

        std::set<std::string> constSet{ "10", "11", "12", "13" };
        std::set<std::string> varNameSet{ "x", "y", "z" };
        std::set<int> stmtNumberByType{ 1, 2, 3 };
        std::set<int> stmtNums{ 1, 2, 3 };

        PKB pkb = PKBStub(constSet, varNameSet, stmtNumberByType, stmtNums);

        SelectHandler selectHandler = SelectHandler(pkb);
        std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

        std::vector<std::string> comparedResult{"x", "y", "z"};
        assert(selectedVarName == "a1");
        std::set<std::string> result = resultTable.getValueFromKey("a1");
        int i = 0;
        for (auto s : result) {
            assert(s == comparedResult[i]);
            i++;
        }
        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}