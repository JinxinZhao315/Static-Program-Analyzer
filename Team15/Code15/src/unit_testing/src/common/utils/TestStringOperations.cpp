#include "catch.hpp"
#include "source_processor/include/extractor/Extractor.h"

TEST_CASE("convertToPostfix_emptyTokenStringInput_shouldReturnEmptyString") {
    vector<string> tokens;
    set<string> variables;
    auto result = convertToPostfix(tokens, variables);
    REQUIRE(result.empty());
}

TEST_CASE("convertToPostfix_singleVariableInput_shouldReturnVariable") {
    vector<string> tokens = {"x"};
    set<string> variables = {"x"};
    auto result = convertToPostfix(tokens, variables);
    REQUIRE(result == tokens);
}

TEST_CASE("convertToPostfix_singleInteger_shouldReturnNumber") {
    vector<string> tokens = {"100"};
    set<string> variables;
    auto result = convertToPostfix(tokens, variables);
    REQUIRE(result == tokens);
}

TEST_CASE("convertToPostfix_addOperation_shouldReturnPostfix") {
    vector<string> tokens = {"x", "+", "y"};
    set<string> variables = {"x", "y"};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"x", "y", "+"};
    REQUIRE(result == expected);
}

TEST_CASE("convertToPostfix_complicatedExpression_shouldReturnPostfix") {
    vector<string> tokens = {"(", "x", "+", "y", ")", "*", "z", "/", "3"};
    set<string> variables = {"x", "y", "z"};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"x", "y", "+", "z", "*", "3", "/",};
    REQUIRE(result == expected);
}

TEST_CASE("convertToPostfix_evenMoreComplicatedExpression_shouldReturnPostfix") {
    vector<string> tokens = {"(", "14", "+", "6", "*", "2", "-", "18", "/", "4", ")", "^", "12", "/", "3"};
    set<string> variables = {};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"14", "6", "2", "*", "+", "18", "4", "/", "-", "12", "^", "3", "/"};
    REQUIRE(result == expected);
}

TEST_CASE("convertToPostfix_similarVarNames_shouldReturnPostfix") {
    vector<string> tokens = {"a", "*", "(", "b", "-", "ab", ")", "/", "a", "+", "b"};
    set<string> variables = {"a", "b", "ab"};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"a", "b", "ab", "-", "*", "a", "/", "b", "+"};
    REQUIRE(result == expected);
}

//TEST_CASE("convertToPostfix_simpleExpressionWithSimilarVarName_shouldReturnPostfix") {
//    vector<string> tokens = {"x", "+", "y", "+", "z", "+", "xy", "+", "yz"};
//    set<string> variables = {"x", "y", "z", "xy", "yz", "+", "+", "+", "+"};
//}

TEST_CASE("convertToPostfix_incrementVarByOne_shouldReturnPostfix") {
    vector<string> tokens = {"x", "+", "1"};
    set<string> variables = {"x"};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"x", "1", "+"};
    REQUIRE(result == expected);
}

TEST_CASE("convertToPostfix_addVar_shouldReturnPostfix") {
    vector<string> tokens = {"x", "+", "x"};
    set<string> variables = {"x"};
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"x", "x", "+"};
    REQUIRE(result == expected);
}
