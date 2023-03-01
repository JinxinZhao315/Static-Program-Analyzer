//#include "catch.hpp"
//#include "Constants.hpp"
//#include "source_processor/include/extractor/UsesRelationshipExtractor.h"
// TODO: rewrite test cases
//TEST_CASE("extractUsesRS_noUsesInAllCalls") {
//    set<string> variables;
//    auto result = extractUsesRS(onlyCallStatements, variables);
//    unordered_map<int, set<string>> expected;
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_noUsesInAssignment") {
//    set<string> variables = {"flag"};
//    auto result = extractUsesRS(mainProgram, variables);
//    unordered_map<int, set<string>> expected;
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_singleUsesSingleVar") {
//    set<string> variables = {"count"};
//    auto result = extractUsesRS(singleAssignmentSelfIncrement, variables);
//    unordered_map<int, set<string>> expected = {
//            {6, {"count"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_singleUsesTwoVar") {
//    set<string> variables = {"cenX", "x"};
//    auto result = extractUsesRS(singleAssignmentAddVariable, variables);
//    unordered_map<int, set<string>> expected = {
//            {7, {"cenX", "x"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_ifElse") {
//    set<string> variables = {"count", "flag", "cenX", "cenY"};
//    auto result = extractUsesRS(ifElse, variables);
//    unordered_map<int, set<string>> expected = {
//            {19, {"count", "cenX", "cenY"}},
//            {21, {"cenX", "count"}},
//            {22, {"cenY", "count"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_ifElseStmtBeforeAndAfter") {
//    set<string> variables = {"count", "flag", "cenX", "cenY"};
//    auto result = extractUsesRS(ifElse2, variables);
//    unordered_map<int, set<string>> expected = {
//            {19, {"count", "cenX", "cenY"}},
//            {21, {"cenX", "count"}},
//            {22, {"cenY", "count"}},
//            {23, {"cenX", "cenY"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_while") {
//    set<string> variables = {"x", "y", "count", "flag", "cenX", "cenY"};
//    auto result = extractUsesRS(whileLoop, variables);
//    unordered_map<int, set<string>> expected = {
//            {5, {"x", "y", "count", "cenX", "cenY"}},
//            {6, {"count"}},
//            {7, {"cenX", "x"}},
//            {8, {"cenY", "y"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_whileStmtBeforeAndAfter") {
//    set<string> variables = {"x", "y", "count", "cenX", "cenY"};
//    auto result = extractUsesRS(whileLoop2, variables);
//    unordered_map<int, set<string>> expected = {
//            {5, {"x", "y", "count", "cenX", "cenY"}},
//            {6, {"count"}},
//            {7, {"cenX", "x"}},
//            {8, {"cenY", "y"}}
//    };
//    REQUIRE(result == expected);
//}
//
//TEST_CASE("extractUsesRS_complexProcedure") {
//    set<string> variables = {"x", "y", "count", "flag", "cenX", "cenY", "normSq"};
//    auto result = extractUsesRS(computeCentroid, variables);
//    unordered_map<int, set<string>> expected = {
//            {5, {"x", "y", "count", "cenX", "cenY"}},
//            {6, {"count"}},
//            {7, {"cenX", "x"}},
//            {8, {"cenY", "y"}},
//            {10, {"count", "cenX", "cenY"}},
//            {12, {"cenX", "count"}},
//            {13, {"cenY", "count"}},
//            {14,{"cenX", "cenY"}}
//    };
//    REQUIRE(result == expected);
//}
