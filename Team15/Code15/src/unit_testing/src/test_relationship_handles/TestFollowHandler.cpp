//#include "PKB.h"
//#include "PQLEvaluator.h"
//#include "PQLPreprocessor.h"
//#include "relationship_handlers/Result.h"
//#include "relationship_handlers/ResultTable.h"
//#include "relationship_handlers/FollowsHandler.h"
//#include "relationship_handlers/SelectHandler.h"
//#include "PKBStub.h"
//#include <assert.h>
//#include "catch.hpp"
//
//using namespace std;
//
//TEST_CASE("PQLEvaluator test 1") {
//    try {
//        ResultTable resultTable = ResultTable();
//        SelectClause selectClause("a");
//
//        std::set<std::string> constSet{ "10", "11", "12", "13" };
//        std::set<std::string> varNameSet{ "x", "y", "z" };
//        std::set<int> stmtNumberByType{ "1", "2", "3" };
//        std::set<int> stmtNums{ "1", "2", "3" };
//        PKBStub pkb = PKBStub(constSet, varNameSet, stmtNumberByType, stmtNums);
//
//        SelectHandler selectHandler = SelectHandler(pkb);
//        std::string selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name
//
//       
//
//    }
//    catch (exception e) {
//        std::cout << "exception occured!";
//    }
//}