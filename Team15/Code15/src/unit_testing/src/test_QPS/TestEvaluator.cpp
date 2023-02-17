#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "source_processor/include/tokeniser/Tokeniser.h"
#include "QPS/include/PQLDriver.h"

#include "catch.hpp"

using namespace std;

//TEST_CASE("tokeniser single procedure extraction successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    tokeniser->tokenise("procedure example { }", 1);
//    string result = "";
//    for (string c : *tokeniser->getProcedures())
//    {
//        result += c;
//    }
//    assert(result == "example");
//}
//
//TEST_CASE("tokeniser multiple procedure extraction successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    tokeniser->tokenise("procedure example1 { }\nprocedure example2 { }", 1);
//    string result = "";
//    for (string c : *tokeniser->getProcedures())
//    {
//        result += c + ", ";
//    }
//    assert(result == "example1, example2, ");
//}
//
//TEST_CASE("tokeniser variable extraction successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    vector<string> tokens = tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
//    string result = "";
//    for (string c : *tokeniser->getVariables())
//    {
//        result += c + ", ";
//    }
//    assert(result == "x, y, ");
//}
//
//TEST_CASE("tokeniser constant extraction successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
//    string result = "";
//    for (string c : *tokeniser->getConstants())
//    {
//        result += c + ", ";
//    }
//    assert(result == "1, 2, ");
//}
//
//TEST_CASE("tokeniser statement extraction successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n read z;\n}", 1);
//    string statementsResults = "";
//    for (const auto &[keyword, statements] : *tokeniser->getStatements())
//    {
//        statementsResults += to_string(keyword) + ":";
//        for (int i : statements)
//        {
//            statementsResults += to_string(i);
//        }
//    }
//    assert(statementsResults == "9:1110:1");
//}
//
//TEST_CASE("tokeniser variable extraction with double equals successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2;}", 1);
//    string result = "";
//    for (string c : *tokeniser->getVariables())
//    {
//        result += c;
//    }
//    assert(result == "x");
//}
//
//TEST_CASE("tokeniser variable extraction with read keyword successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2; read z;}", 1);
//    string result = "";
//    for (string c : *tokeniser->getVariables())
//    {
//        result += c + ", ";
//    }
//    assert(result == "x, z, ");
//}
//
//TEST_CASE("tokeniser variable extraction with double equals and no spaces successful test")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    std::vector<std::string> tokens = tokeniser->tokenise(" {y==2;}", 1);
//    string result = "";
//    for (string c : *tokeniser->getVariables())
//    {
//        cout << c << endl;
//    }
//    assert(result == "");
//}
//
//TEST_CASE("PQLEvaluator test 1")
//{
//    try
//    {
//        PQLPreprocessor preprocessor;
//        PKB pkb;
//        PQLEvaluator evaluator = PQLEvaluator(pkb);
//
//        Query query = Query();
//        query = preprocessor.preprocess("stmt s1; Select s1 such that Follows(_,_)");
//
//        string retStr = evaluator.evaluate(query);
//        // To pass this set, set isFollowEmpty in FollowsHandler to true
//        assert(retStr == "None");
//    }
//    catch (exception e)
//    {
//        std::cout << "exception occured!";
//    }
//}
//
//
//TEST_CASE("Tokeniser test 5")
//{
//
//    Tokeniser *tokeniser = new Tokeniser();
//    std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2; read z;}", 1);
//    for (string s : tokens)
//    {
//        cout << s << endl;
//    }
//    for (string c : *tokeniser->getVariables())
//    {
//        cout << c << endl;
//    }
//    std::vector<std::string> correct_res;
//    correct_res.push_back("x");
//    //    assert(tokens == correct_res);
//}
//
//TEST_CASE("Tokeniser test 6")
//{
//    Tokeniser *tokeniser = new Tokeniser();
//    std::vector<std::string> tokens = tokeniser->tokenise(" {y==2;}", 1);
//    for (string s : tokens)
//    {
//        cout << s << endl;
//    }
//    for (string c : *tokeniser->getVariables())
//    {
//        cout << c << endl;
//    }
//    std::vector<std::string> correct_res;
//    correct_res.push_back("x");
//    //    assert(tokens == correct_res);
//}
//
//TEST_CASE("Evaluator test 1")
//{
//    PKB pkb;
//    pkb.addFollows(4, 5);
//    pkb.addFollows(2, 3);
//    pkb.addStmt(Tokens::READ, 1);
//    pkb.addStmt(Tokens::READ, 2);
//    pkb.addStmt(Tokens::READ, 3);
//    pkb.addStmt(Tokens::READ, 4);
//    pkb.addStmt(Tokens::READ, 5);
//    PQLEvaluator evaluator = PQLEvaluator(pkb);
//    PQLPreprocessor preprocessor;
//    std::string queryStr = "read s1; Select s1 such that Follows(_,3)";
//    Query query = preprocessor.preprocess(queryStr);
//
//    // Call evaluator
//    std::string results = evaluator.evaluate(query);
//    REQUIRE(results == "1,2,3,4,5");
//}
