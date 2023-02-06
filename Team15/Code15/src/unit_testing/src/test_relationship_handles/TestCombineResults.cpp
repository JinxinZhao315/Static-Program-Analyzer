#include "relationship_handlers/ClauseHandler.h"
#include "relationship_handlers/Result.h"
#include <set>
#include "catch.hpp"
#include <assert.h>
#include <memory> 
#include "PKB.h"

using namespace std;



TEST_CASE("EmptyTable EmptyResult test") {
    try {
        PKB pkb = PKB();
        shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
        ResultTable resultTable = ResultTable();
        Result emptyResult = Result();

        clauseHandlerPtr->combineResult(resultTable, emptyResult);
        REQUIRE(resultTable.sizeOfResultTable() == 0);
    }
    catch (exception e) {
        std::cout << "EmptyTable EmptyResult test exception occured!";
    }
}
TEST_CASE("Result with leftArg test") {
    try {
        PKB pkb = PKB();
        shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
        ResultTable resultTable = ResultTable();
        Result result = Result();

        set<string> set;
        set.emplace("2");
        set.emplace("6");

        result.setLeftArg("a", set);

        clauseHandlerPtr->combineResult(resultTable, result);

        REQUIRE(resultTable.sizeOfResultTable() == 1);
        REQUIRE(resultTable.getValueFromKey("a") == set);
    }
    catch (exception e) {
        std::cout << "Result with leftArg test exception occured!";
    }
}

TEST_CASE("Result with bothArg test") {
    try {
        PKB pkb = PKB();
        shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
        ResultTable resultTable = ResultTable();
        Result result = Result();

        set<string> leftSet;
        leftSet.emplace("2");
        leftSet.emplace("6");

        set<string> rightSet;
        rightSet.emplace("23");
        rightSet.emplace("63");

        result.setLeftArg("a", leftSet);
        result.setRightArg("b", rightSet);

        clauseHandlerPtr->combineResult(resultTable, result);

        REQUIRE(resultTable.sizeOfResultTable() == 2);
        REQUIRE(resultTable.getValueFromKey("a") == leftSet);
        REQUIRE(resultTable.getValueFromKey("b") == rightSet);
    }
    catch (exception e) {
        std::cout << "Result with bothArg test exception occured!";
    }
}

TEST_CASE("Result with intersection test") {
    try {
        PKB pkb = PKB();
        shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
        ResultTable resultTable = ResultTable();
        Result result = Result();

        set<string> leftSet;
        leftSet.emplace("2");
        leftSet.emplace("6");

        set<string> rightSet;
        rightSet.emplace("23");
        rightSet.emplace("63");

        result.setLeftArg("a", leftSet);
        result.setRightArg("b", rightSet);

        clauseHandlerPtr->combineResult(resultTable, result);

        Result newResult = Result();
        set<string> newLeftSet;
        newLeftSet.emplace("2");

        set<string> newRightSet;
        newRightSet.emplace("23");

        newResult.setLeftArg("a", newLeftSet);
        newResult.setRightArg("b", newRightSet);

        clauseHandlerPtr->combineResult(resultTable, newResult);

        REQUIRE(resultTable.sizeOfResultTable() == 2);
        REQUIRE(resultTable.getValueFromKey("a") == newLeftSet);
        REQUIRE(resultTable.getValueFromKey("b") == newRightSet);
    }
    catch (exception e) {
        std::cout << "Result with intersection test exception occured!";
    }
}

TEST_CASE("Result with empty intersection test") {
    try {
        PKB pkb = PKB();
        shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
        ResultTable resultTable = ResultTable();
        Result result = Result();

        set<string> leftSet;
        leftSet.emplace("2");
        leftSet.emplace("6");

        set<string> rightSet;
        rightSet.emplace("23");
        rightSet.emplace("63");

        result.setLeftArg("a", leftSet);
        result.setRightArg("b", rightSet);

        clauseHandlerPtr->combineResult(resultTable, result);

        Result newResult = Result();
        set<string> newLeftSet;

        set<string> newRightSet;

        newResult.setLeftArg("a", newLeftSet);
        newResult.setRightArg("b", newRightSet);

        clauseHandlerPtr->combineResult(resultTable, newResult);

        REQUIRE(resultTable.sizeOfResultTable() == 2);
        REQUIRE(resultTable.getValueFromKey("a") == newLeftSet);
        REQUIRE(resultTable.getValueFromKey("b") == newRightSet);
    }
    catch (exception e) {
        std::cout << "Result with empty intersection test exception occured!";
    }
}

