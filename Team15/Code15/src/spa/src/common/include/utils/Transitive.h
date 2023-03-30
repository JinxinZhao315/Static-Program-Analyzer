#pragma once
#include "unordered_map"
#include <set>
#include <stack>
#include <iostream>

using namespace std;

template <typename Key, typename Value>
void generateTransitiveRelationship(const unordered_map<Key, Value>& inputRS, unordered_map<Key, set<Key>>& outputStarRS) {
    for (const auto& [src, dests] : inputRS) {
        set<Key> visited{src};
        stack<Key> toVisit;
        toVisit.push(src);

        while (!toVisit.empty()) {
            Key curr = toVisit.top();
            toVisit.pop();

            set<Key> nextDests;
            if constexpr (is_same_v<Value, set<Key>>) {
                if (inputRS.count(curr) > 0) {
                    nextDests = inputRS.at(curr);
                }
            } else if constexpr (is_same_v<Value, Key>) {
                if (inputRS.count(curr) > 0) {
                    nextDests.insert(inputRS.at(curr));
                }
            } else {
                cout << "Error: Unsupported type for Value";
            }

            for (const auto& nextDest : nextDests) {
                if (visited.find(nextDest) == visited.end()) {
                    visited.insert(nextDest);
                    toVisit.push(nextDest);
                    outputStarRS[src].insert(nextDest);
                }
            }
        }
    }
}
