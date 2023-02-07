//#include "relationship_handlers/ClauseHandler.h"
//#include "relationship_handlers/Result.h"
//#include <set>
//#include "catch.hpp"
//
//#include <memory> 
//#include "PKB.h"
//
//using namespace std;
//
//PKB pkb = new PKB();
//shared_ptr<ClauseHandler> clauseHandlerPtr = make_shared<ClauseHandler>(pkb);
//ResultTable resultTable = new ResultTable();
//
//TEST_CASE("EmptyTable EmptyResult test") {
//    try {
//        Result emptyResult = new Result();
//
//        //Result() : isTrue(true),
//        //    isLeftArgAvailable(false), isRightArgAvailable(false) {}
//        //Result(bool isTrue, std::string leftArgName, std::set<std::string> leftArgValue) :
//        //    isTrue(true), leftArgName(leftArgName), leftArgValue(leftArgValue), isLeftArgAvailable(true) {}
//        //Result(bool isTrue,
//        //    std::string leftArgName, std::set<std::string> leftArgValue,
//        //    std::string rightArgName, std::set<std::string> rightArgValue) :
//       
//        clauseHandlerPtr->combineResult(resultTable, emptyResult);
//        REQUIRE(resultTable.sizeOfResultTable == 0);
//
//        set<string> set;
//        set.emplace("2");
//        set.emplace("6");
//
//        emptyResult.setLeftArg("a", set);
//
//        clauseHandlerPtr->combineResult(resultTable, emptyResult);
//
//        REQUIRE(resultTable.sizeOfResultTable == 0);
//    }
//    catch (exception e) {
//        std::cout << "EmptyTable EmptyResult test exception occured!";
//    }
//}