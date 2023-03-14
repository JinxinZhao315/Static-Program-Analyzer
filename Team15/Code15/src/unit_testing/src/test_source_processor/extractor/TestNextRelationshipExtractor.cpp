#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/NextRelationshipExtractor.h"

TEST_CASE("extractNextRelationship_ifWithNestedIfElseAndElseWithNestedWhile") {
    CFGNode* node1 = new CFGNode(1);
    CFGNode* node2 = new CFGNode(2);
    CFGNode* node3 = new CFGNode(3);
    CFGNode* node4 = new CFGNode(4);
    CFGNode* node5 = new CFGNode(5);
    CFGNode* node6 = new CFGNode(6);

    node1->addNext(node2);
    node1->addNext(node5);
    node2->addNext(node3);
    node2->addNext(node4);
    node5->addNext(node6);
    node6->addNext(node5);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2, 5}},
            {2, {3, 4}},
            {5, {6}},
            {6, {5}}
    };
    REQUIRE(extractedNext == expectedNext);
}