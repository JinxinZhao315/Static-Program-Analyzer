#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/SelectHandler.h"
#include "PKBStub.h"
#include "Tokens.h"
#include "Query.h"
#include "PQLPreprocessor.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Follows Handler test 1") {
    try {
        ResultTable resultTable = ResultTable();
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,5)");
        /*Query query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(5,_)");
        Query query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(1, 2)");
        Query query = preprocessor.preprocess("stmt s1; stmt s2; Select s1 such that Follows(s1,s2)");*/


        SelectHandler selectHandler = SelectHandler(pkb);
        multimap<string, string> varTable = query.getVarTable();
        std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);// update resultTable and return the synonym name

        assert(selectedVarName == "r");
        std::set<std::string> result = resultTable.getValueFromKey("r");
        for (auto s : result) {
            std::cout << s << "\n" << endl;
        }

        std::cout << "select handler successful" << std::endl;
    }
    catch (exception e) {
        std::cout << "exception occured!";
    }
}