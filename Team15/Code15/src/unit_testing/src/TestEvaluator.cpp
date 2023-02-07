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

TEST_CASE("Tokeniser test 1") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example { }", 1);
    for(string c : *tokeniser->getProcedures()) {
       cout << c << endl;
    }
}

TEST_CASE("Tokeniser test 2") {
    Tokeniser *tokeniser = new Tokeniser();
    vector<string> tokens =  tokeniser->tokenise("procedure example { x = 1; y = 2; }", 1);
    for(string c : *tokeniser->getVariables()) {
        cout << c << endl;
    }
}

TEST_CASE("Tokeniser test 3") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example { x = 1; y = 2; }", 1);
    for(string c : *tokeniser->getConstants()) {
        cout << c << endl;
    }
}

TEST_CASE("Tokeniser test 4") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example { x = 1; y = 2; read z;}", 1);
    for (const auto& [keyword, statements] : *tokeniser->getStatements()) {
        for(int i : statements) {
            cout << keyword << i << endl;
        }
    }
}

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

TEST_CASE("Tokeniser test 5") {
    Tokeniser *tokeniser = new Tokeniser();
    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2; read z;}", 1);
    for(string s : tokens) {
        cout << s << endl;
    }
    for(string c : *tokeniser->getVariables()) {
        cout << c << endl;
    }
    std::vector<std::string> correct_res;
    correct_res.push_back("x");
//    assert(tokens == correct_res);
}

TEST_CASE("Tokeniser test 6") {
    Tokeniser *tokeniser = new Tokeniser();
    std::vector<std::string> tokens = tokeniser->tokenise(" {y==2;}", 1);
    for(string s : tokens) {
        cout << s << endl;
    }
    for(string c : *tokeniser->getVariables()) {
        cout << c << endl;
    }
    std::vector<std::string> correct_res;
    correct_res.push_back("x");
//    assert(tokens == correct_res);
}

TEST_CASE("Evaluator test 1") {
    PKB pkb;
    pkb.addFollows(4, 5);
    pkb.addFollows(2, 3);
    pkb.addStmt(Tokens::READ, 1);
    pkb.addStmt(Tokens::READ, 2);
    pkb.addStmt(Tokens::READ, 3);
    pkb.addStmt(Tokens::READ, 4);
    pkb.addStmt(Tokens::READ, 5);
    PQLEvaluator evaluator = PQLEvaluator(pkb);
    PQLPreprocessor preprocessor;
    std::string queryStr = "read s1; Select s1 such that Follows(_,3)";
    Query query = preprocessor.preprocess(queryStr);

    // Call evaluator
    std::string results = evaluator.evaluate(query);
    REQUIRE(results == "1,2,3,4,5");
}

TEST_CASE("Overall test") {
    // Enter source of SIMPLE code
    string filename = "../../../../../../Tests15/Sample_source2.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
    }

    Tokeniser* tokeniser = new Tokeniser();
    // Tokeniser process
    
    map<int, vector<string>> parsed = tokeniser->processFile(file);
    map<int, int> nesting_level = tokeniser->generateNestingLevel(parsed);
    map<int, int> follows = tokeniser->generateFollowsRS(nesting_level);
    map<int, set<int>> follows_star = tokeniser->generateFollowsStarRS(nesting_level);
    map<string, vector<vector<string>>> assigns = tokeniser->generateAssignmentRS(parsed);
    std::set<std::string> *procedures = tokeniser->getProcedures();
    std::vector<std::string> *constants = tokeniser->getConstants();
    std::set<std::string> *variables = tokeniser->getVariables();

    std::map<Tokens::Keyword, std::vector<int>> *statements = tokeniser->getStatements();

    file.close();

    // TODO: add PKB calls
    PKB pkb = PKB();
    for (string p : *procedures) {
        pkb.addProc(p);
    }
    for (string c : *constants) {
        pkb.addConst(c);
    }
    for (string v : *variables) {
        pkb.addVar(v);
    }
    for (auto pair : *statements) {
        for (int s : pair.second) {
            pkb.addStmt(pair.first, s);
        }
    }
    for (auto pair : follows) {
        pkb.addFollows(pair.first, pair.second);
    }
    for (auto pair : follows_star) {
        pkb.addFollowsStar(pair.first, pair.second);
    }
    // TODO: add PQL calls
    string queryStr = "stmt s; Select s";
    PQLDriver pqlDriver = PQLDriver(pkb);
    string result = pqlDriver.processPQL(queryStr);
    cout << "result:" << result << endl;
    //assert(result == "1,2");
}

