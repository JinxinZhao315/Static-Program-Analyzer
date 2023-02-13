#include "PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "Tokeniser.h"
#include "QPS/include/PQLDriver.h"

#include "catch.hpp"

using namespace std;

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
    string queryStr = "constant c; Select c";
    PQLDriver pqlDriver = PQLDriver(pkb);
    string result = pqlDriver.processPQL(queryStr);
    cout << "result:" << result << endl;
    REQUIRE(result == "2,3,5");
}