#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/NextRelationshipExtractor.h"

TEST_CASE("extractNextRelationship_ifNoElseNoLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);

    node1->addNext(node2);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifNoElseWithLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);

    node1->addNext(node2);
    node2->addNext(node3);
    node2->addNext(node4);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3, 4}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifAndElseNoLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);

    node1->addNext(node2);
    node1->addNext(node3);
    node2->addNext(node3);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2, 3}},
            {2, {3}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifAndElseWithLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);

    node1->addNext(node2);
    node2->addNext(node3);
    node2->addNext(node4);
    node3->addNext(node5);
    node4->addNext(node5);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3, 4}},
            {3, {5}},
            {4, {5}},
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_whileNoLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);

    node1->addNext(node2);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_whileWithLinesBeforeAndAfter") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);

    node1->addNext(node2);
    node2->addNext(node3);
    node2->addNext(node4);
    node3->addNext(node2);
    node3->addNext(node4);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3, 4}},
            {3, {2, 4}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_whileNestedInWhile") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);
    auto* node6 = new CFGNode(6);

    node1->addNext(node2);
    node2->addNext(node3);
    node2->addNext(node6);
    node3->addNext(node4);
    node3->addNext(node5);
    node4->addNext(node3);
    node4->addNext(node5);
    node5->addNext(node2);
    node5->addNext(node6);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3, 6}},
            {3, {4, 5}},
            {4, {3, 5}},
            {5, {2, 6}},
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifWithElseNestedInWhile") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);
    auto* node6 = new CFGNode(6);
    auto* node7 = new CFGNode(7);

    node1->addNext(node2);
    node2->addNext(node3);
    node2->addNext(node7);
    node3->addNext(node4);
    node3->addNext(node5);
    node4->addNext(node6);
    node5->addNext(node6);
    node6->addNext(node2);
    node6->addNext(node7);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2}},
            {2, {3, 7}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {2, 7}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifWithElseWhileNestedInEachBranch") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);

    node1->addNext(node2);
    node1->addNext(node4);
    node2->addNext(node3);
    node3->addNext(node2);
    node4->addNext(node5);
    node5->addNext(node4);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2, 4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_whileWithNestedIfWithElse") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);
    auto* node6 = new CFGNode(6);
    auto* node7 = new CFGNode(7);

    node1->addNext(node2);
    node1->addNext(node7);
    node2->addNext(node3);
    node3->addNext(node4);
    node3->addNext(node5);
    node4->addNext(node6);
    node5->addNext(node6);
    node6->addNext(node1);
    node6->addNext(node7);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2, 7}},
            {2, {3}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {1, 7}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifWithElseEachBranchHasNestedWhileWithNestedIfWithElse") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);
    auto* node6 = new CFGNode(6);
    auto* node7 = new CFGNode(7);
    auto* node8 = new CFGNode(8);
    auto* node9 = new CFGNode(9);

    node1->addNext(node2);
    node1->addNext(node6);
    node2->addNext(node3);
    node3->addNext(node4);
    node3->addNext(node5);
    node4->addNext(node2);
    node5->addNext(node2);
    node6->addNext(node7);
    node7->addNext(node8);
    node7->addNext(node9);
    node8->addNext(node6);
    node9->addNext(node6);

    vector<CFGNode*> rootNodes = {node1};
    auto extractedNext = extractNextRS(rootNodes);
    unordered_map<int, set<int>> expectedNext = {
            {1, {2, 6}},
            {2, {3}},
            {3, {4, 5}},
            {4, {2}},
            {5, {2}},
            {6, {7}},
            {7, {8, 9}},
            {8, {6}},
            {9, {6}}
    };
    REQUIRE(extractedNext == expectedNext);
}

TEST_CASE("extractNextRelationship_ifWithNestedIfElseAndElseWithNestedWhile") {
    auto* node1 = new CFGNode(1);
    auto* node2 = new CFGNode(2);
    auto* node3 = new CFGNode(3);
    auto* node4 = new CFGNode(4);
    auto* node5 = new CFGNode(5);
    auto* node6 = new CFGNode(6);

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
