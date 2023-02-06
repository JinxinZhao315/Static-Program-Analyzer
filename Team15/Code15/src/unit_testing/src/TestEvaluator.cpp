//
// Created by Jinxin Zhao on 5/2/23.
//

#include "PKB.h"
#include "PQLEvaluator.h"
#include "PQLPreprocessor.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/FollowsHandler.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("PQLEvaluator test 1") {
    try {
        PQLPreprocessor preprocessor;
        PKB pkb;
        PQLEvaluator evaluator = PQLEvaluator(pkb);

        Query query = Query();
        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,_)");

        string retStr = evaluator.evaluate(query);
        // To pass this set, set isFollowEmpty in FollowsHandler to true
        assert(retStr == "None");
    } catch (exception e) {
        std::cout<<"exception occured!";
    }
}



