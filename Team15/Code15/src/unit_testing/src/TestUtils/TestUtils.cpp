#include "TestUtils.h"

void printNodes(const unordered_map<int, set<int>>& myMap) {
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": [";
        for (const auto& v : value) {
            std::cout << v << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void compareCFG(const unordered_map<int, set<int>>& result, const unordered_map<int, set<int>>& expected) {
    if (result != expected) {
        cout << "Result: " << endl;
        printNodes(result);
        cout << "Expected: " << endl;
        printNodes(expected);
    }
    REQUIRE(result == expected);
}
