#pragma once

#include <set>
#include <unordered_map>

using namespace std;

class ParentTable {
public:
	ParentTable();

	void addParentChildren(int parent, std::set<int> children);

	void addAllParentChildren(std::unordered_map<int, std::set<int>> parentToChildren);

	std::set<int> getChildren(int parent);

	int getParent(int child);

	bool inRelationship(int parentNumber, int childNumber);

	bool isEmpty();

	void addChildren(int parent, std::set<int> children);

	void addParent(int parent, std::set<int> children);

	void flip(std::unordered_map<int, std::set<int>> parentToChildren);

private:
	std::unordered_map<int, std::set<int>> parentToChildrenMap;
	std::unordered_map<int, int> childToParentMap;
};
