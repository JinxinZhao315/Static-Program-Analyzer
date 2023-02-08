//
// Created by Jinxin Zhao on 5/2/23.
//

#include "PKB.h"
#include "QPS/PQLEvaluator.h"
#include "QPS/PQLPreprocessor.h"
#include "QPS/relationship_handlers/Result.h"
#include "QPS/relationship_handlers/ResultTable.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
#include "Tokeniser.h"
#include "QPS/PQLDriver.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("tokeniser single procedure extraction successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example { }", 1);
    string result = "";
    for(string c : *tokeniser->getProcedures()) {
       result += c;
    }
    assert(result == "example");
}

TEST_CASE("tokeniser multiple procedure extraction successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example1 { }\nprocedure example2 { }", 1);
    string result = "";
    for(string c : *tokeniser->getProcedures()) {
        result += c + ", ";
    }
    assert(result == "example1, example2, ");
}

TEST_CASE("tokeniser variable extraction successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    vector<string> tokens =  tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
    string result = "";
    for(string c : *tokeniser->getVariables()) {
        result += c + ", ";
    }
    assert(result == "x, y, ");
}

TEST_CASE("tokeniser constant extraction successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
    string result = "";
    for(string c : *tokeniser->getConstants()) {
        result += c + ", ";
    }
    assert(result == "1, 2, ");
}

TEST_CASE("tokeniser statement extraction successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n read z;\n}", 1);
    string statementsResults = "";
    for (const auto& [keyword, statements] : *tokeniser->getStatements()) {
        statementsResults += to_string(keyword) + ":";
        for(int i : statements) {
            statementsResults += to_string(i);
        }
    }
    assert(statementsResults == "9:1110:1");
}

TEST_CASE("tokeniser variable extraction with double equals successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2;}", 1);
    string result = "";
    for(string c : *tokeniser->getVariables()) {
        result += c;
    }
    assert(result == "x");
}

TEST_CASE("tokeniser variable extraction with read keyword successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2; read z;}", 1);
    string result = "";
    for(string c : *tokeniser->getVariables()) {
        result += c + ", ";
    }
    assert(result == "x, z, ");
}

TEST_CASE("tokeniser variable extraction with double equals and no spaces successful test") {
    Tokeniser *tokeniser = new Tokeniser();
    std::vector<std::string> tokens = tokeniser->tokenise(" {y==2;}", 1);
    string result = "";
    for(string c : *tokeniser->getVariables()) {
        cout << c << endl;
    }
    assert(result == "");
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

TEST_CASE("Overall test") {
    // Enter source of SIMPLE code
    string filename = "../../../../Tests15/Sample_source2.txt";
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

