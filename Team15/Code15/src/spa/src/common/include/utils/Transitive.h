#pragma once
#include "unordered_map"
#include <set>
#include <stack>
#include <iostream>

using namespace std;

/**
 * @param canContainItself parameter to specify if a key can also appear in the value (true only for next star relationships)
 */
template <typename Key, typename Value>
void generateTransitiveRelationship(const unordered_map<Key, Value>& inputRS, unordered_map<Key, set<Key>>& outputStarRS, bool canContainItself) {
    for (const auto& [start, nextNode] : inputRS) {
        set<Key> visited;
        if (!canContainItself) {
            visited.insert(start);
        }
        stack<Key> toVisit;
        toVisit.push(start);

        while (!toVisit.empty()) {
            Key curr = toVisit.top();
            toVisit.pop();

            set<Key> nextNodes;
            if constexpr (is_same_v<Value, set<Key>>) {
                if (inputRS.count(curr) > 0) {
                    nextNodes = inputRS.at(curr);
                }
            } else if constexpr (is_same_v<Value, Key>) {
                if (inputRS.count(curr) > 0) {
                    nextNodes.insert(inputRS.at(curr));
                }
            } else {
                cout << "Error: Unsupported type for Value";
            }

            for (const auto& nextDest : nextNodes) {
                if (visited.find(nextDest) == visited.end()) {
                    visited.insert(nextDest);
                    toVisit.push(nextDest);
                    if (canContainItself || start != nextDest) {
                        outputStarRS[start].insert(nextDest);
                    }
                }
            }
        }
    }
}

