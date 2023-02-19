#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

TEST_CASE("extractFollowsRelationship_noNesting") {
    auto [result, result2] = extractFollowsRelationship(mainProgram);
    unordered_map<int, int> expectedFollows = {{1,2}, {2,3}};
    unordered_map<int, set<int>> expectedFollowsStar = {{1, {2, 3}}, {2, {3}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withWhileLoop") {
    auto [result, result2] = extractFollowsRelationship(whileLoop);
    unordered_map<int, int> expectedFollows = {{6,7}, {7,8}, {8,9}};
    unordered_map<int, set<int>> expectedFollowsStar = {{6, {7,8,9}}, {7, {8,9}}, {8, {9}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withWhileLoopStatementBeforeAndAfter") {
    auto [result, result2] = extractFollowsRelationship(whileLoop2);
    unordered_map<int, int> expectedFollows = {{4,5}, {6,7}, {7,8}, {8,9}, {5, 10}};
    unordered_map<int, set<int>> expectedFollowsStar = {{4, {5,10}}, {5, {10}}, {6, {7,8,9}}, {7, {8,9}}, {8, {9}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withIfElse") {
    auto [result, result2] = extractFollowsRelationship(ifElse);
    unordered_map<int, int> expectedFollows = {{21,22}};
    unordered_map<int, set<int>> expectedFollowsStar = {{21, {22}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withIfElseStatementBeforeAndAfter") {
    auto [result, result2] = extractFollowsRelationship(ifElse2);
    unordered_map<int, int> expectedFollows = {{18,19}, {19,23}, {21,22}};
    unordered_map<int, set<int>> expectedFollowsStar = {{18, {19,23}}, {19, {23}}, {21, {22}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_withBothWhileAndIf") {
    auto [result, result2] = extractFollowsRelationship(computeCentroid);
    unordered_map<int, int> expectedFollows = {{1,2}, {2,3}, {3,4}, {4,5}, {6,7}, {7,8},
                                               {8,9}, {5,10}, {10,14}, {12,13}};
    unordered_map<int, set<int>> expectedFollowsStar = {{1,{2,3,4,5,10,14}},{2,{3,4,5,10,14}},{3,{4,5,10,14}},
        {4,{5,10,14}},{5,{10,14}},{6,{7,8,9}},{7,{8,9}},{8,{9}},{10,{14}},{12,{13}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}

TEST_CASE("extractFollowsRelationship_superNested") {
    auto [result, result2] = extractFollowsRelationship(superNested);
    unordered_map<int, int> expectedFollows = {{1,2},{2,3},{3,4},{5,14},{8,9}};
    unordered_map<int, set<int>> expectedFollowsStar = {{1,{2,3,4}},{2,{3,4}},{3,{4}},{5,{14}},{8,{9}}};
    REQUIRE(result == expectedFollows);
    REQUIRE(result2 == expectedFollowsStar);
}