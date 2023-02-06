#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/SelectHandler.h"
#include "PKBStub.h"
<<<<<<< HEAD
#include <assert.h>
=======
#include "Tokens.h"
#include "Query.h"
#include "PQLPreprocessor.h"

>>>>>>> 5883de26194d355c3237dd12bb677375b7d89349
#include "catch.hpp"

using namespace std;

<<<<<<< HEAD
TEST_CASE("PQLPreprocessor query object test 3") {
    try {
        PQLPreprocessor preprocessor;
        Query query = Query();

        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,_)");

        std::multimap<std::string, std::string> varTable = query.getVarTable();
        string type = varTable.find("s1")->second;
        assert(type == "stmt");
        std::cout << "var table correct" << std::endl;

        SelectClause selectClause = query.getSelectClause();
        string varName = selectClause.getVarName();
        assert(varName == "s1");
        std::cout << "select correct" << std::endl;

        vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
        for (SuchThatClause cl : suchThatClauseVec) {
            string relationship = cl.getRelationShip();
            string leftArg = cl.getLeftArg();
            string rightArg = cl.getRightArg();
            assert(relationship == "Follows");
            std::cout << "relationship correct" << std::endl;
            assert(leftArg == "_");
            std::cout << "leftArg correct" << std::endl;
            assert(rightArg == "_");
            std::cout << "rightArg correct" << std::endl;
        }
        std::cout << "syntax correct" << std::endl;
    }
    catch (PQLSyntaxError e) {
        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
    }
}

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
//    }
//    catch (PQLSyntaxError e) {
//        std::cout << "syntax should be correct, but syntax checker give error!" << std::endl;
//    }
//}
//
//    }
//    catch (exception e) {
//        std::cout << "exception occured!";
//    }
//}
=======
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
        std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), query.getVarTable(), resultTable);// update resultTable and return the synonym name

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
>>>>>>> 5883de26194d355c3237dd12bb677375b7d89349
