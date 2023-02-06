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
#include "Tokeniser.h"
#include "PQLDriver.h"

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

TEST_CASE("Overall test") {
    // Enter source of SIMPLE code
    string filename = "Team15/Tests15/Sample_source.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;

    }

    // Tokeniser process
    map<int, vector<string>> parsed = processFile(file);
    map<int, int> nesting_level = generateNestingLevel(parsed);
    map<int, int> follows = generateFollowsRS(nesting_level);
    map<int, set<int>> follows_star = generateFollowsStarRS(nesting_level);
    map<string, vector<vector<string>>> assigns = generateAssignmentRS(parsed);

    file.close();

    // TODO: add PKB calls
    PKB pkb = PKB();
    // TODO: add PQL calls
    string queryStr = "stmt s; Select s such that Follows(_,_)";
    PQLDriver pqlDriver = PQLDriver(pkb);
}
