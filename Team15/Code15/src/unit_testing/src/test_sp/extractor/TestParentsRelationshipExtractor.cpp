#include "catch.hpp"
#include "Constants.hpp"
#include "sp/include/extractor/ParentsRelationshipExtractor.h"

TEST_CASE("extractParentsRelationship_noNesting_noParents") {
    auto [result, result2] = extractParentsRelationship(mainProgram);
    unordered_map<int, set<int>> expectedParents;
    unordered_map<int, set<int>> expectedParentsStar;
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}

TEST_CASE("extractParentsRelationship_withWhileLoop") {
    auto [result, result2] = extractParentsRelationship(whileLoop);
    unordered_map<int, set<int>> expectedParents = {{5, {6,7,8,9}}};
    unordered_map<int, set<int>> expectedParentsStar = {{5, {6,7,8,9}}};
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}

TEST_CASE("extractParentsRelationship_withWhileLoopStatementBeforeAndAfter") {
    auto [result, result2] = extractParentsRelationship(whileLoop2);
    unordered_map<int, set<int>> expectedParents = {{5, {6,7,8,9}}};
    unordered_map<int, set<int>> expectedParentsStar = {{5, {6,7,8,9}}};
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}

TEST_CASE("extractParentsRelationship_withIfElse") {
    auto [result, result2] = extractParentsRelationship(ifElse);
    unordered_map<int, set<int>> expectedParents = {{19, {20,21,22}}};
    unordered_map<int, set<int>> expectedParentsStar = {{19, {20,21,22}}};
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}

TEST_CASE("extractParentsRelationship_withIfElseStatementBeforeAndAfter") {
    auto [result, result2] = extractParentsRelationship(ifElse2);
    unordered_map<int, set<int>> expectedParents = {{19, {20,21,22}}};
    unordered_map<int, set<int>> expectedParentsStar = {{19, {20,21,22}}};
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}

TEST_CASE("extractParentsRelationship_superNested") {
    auto [result, result2] = extractParentsRelationship(superNested);
    unordered_map<int, set<int>> expectedParents = {{4, {5,14}}, {5,{6}}, {6, {7,13}},
                    {7, {8,9,10}}, {10, {11,12}}};
    unordered_map<int, set<int>> expectedParentsStar = {{4,{5,6,7,8,9,10,11,12,13,14}},
        {5,{6,7,8,9,10,11,12,13}},{6,{7,8,9,10,11,12,13}},{7,{8,9,10,11,12}},{10,{11,12}}};
    REQUIRE(result == expectedParents);
    REQUIRE(result2 == expectedParentsStar);
}