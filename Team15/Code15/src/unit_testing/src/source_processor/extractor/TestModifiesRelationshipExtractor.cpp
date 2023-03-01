//#include "catch.hpp"
//#include "Constants.hpp"
//#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"
// TODO: rewrite test cases
//TEST_CASE("extractModifiesRS_noModifications") {
//    auto result = extractModifiesRS(onlyCallStatements);
//    unordered_map<int, set<string>> expected;
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractModifiesRS_oneAssignment") {
//    auto result = extractModifiesRS(singleAssignmentSelfIncrement);
//    unordered_map<int, set<string>> expected = {
//            {6, {"count"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractModifiesRS_manyAssignments") {
//    auto result = extractModifiesRS(whileLoop);
//    unordered_map<int, set<string>> expected = {
//            {5, {"count", "cenX", "cenY"}},
//            {6, {"count"}},
//            {7, {"cenX"}},
//            {8, {"cenY"}},
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractModifiesRS_complicatedProgram") {
//    auto result = extractModifiesRS(computeCentroid);
//    unordered_map<int, set<string>> expected = {
//            {1, {"count"}},
//            {2, {"cenX"}},
//            {3, {"cenY"}},
//            {5, {"count", "cenX", "cenY"}},
//            {6, {"count"}},
//            {7, {"cenX"}},
//            {8, {"cenY"}},
//            {10, {"flag", "cenX", "cenY"}},
//            {11, {"flag"}},
//            {12, {"cenX"}},
//            {13, {"cenY"}},
//            {14, {"normSq"}}
//    };
//    REQUIRE(result == expected);
//}
//
//
//TEST_CASE("extractModifiesRS_twoReadStatements") {
//    auto result = extractModifiesRS(readPoint);
//    unordered_map<int, set<string>> expected = {
//            {4, {"x"}},
//            {5, {"y"}},
//    };
//    REQUIRE(result == expected);
//}