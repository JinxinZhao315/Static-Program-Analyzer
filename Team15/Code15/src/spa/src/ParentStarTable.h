#pragma once

#include <unordered_map>
#include <set>

using namespace std;

class ParentStarTable {
public:
	ParentStarTable();

	void addParentStar(int parent, std::set<int> children);

	void addAllParentStar(std::unordered_map<int, std::set<int>> parentToChildren);

	std::set<int> getChildren(int parent);

	std::set<int> getParents(int child);

	bool inRelationship(int parentNumber, int childrenNumber);

	bool isEmpty();

	void addChildren(int parent, std::set<int> children);

	void addParents(int parent, std::set<int> children);

	void flipParentToChildren(std::unordered_map<int, std::set<int>> parentToChildren);

private:
	std::unordered_map<int, std::set<int>> parentToChildrenMap;
	std::unordered_map<int, std::set<int>> childToParentsMap;
};