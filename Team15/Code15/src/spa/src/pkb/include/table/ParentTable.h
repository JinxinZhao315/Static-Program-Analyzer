#pragma once

#include <unordered_map>

using namespace std;

class ParentTable {
public:
	ParentTable();

	void addParentChild(int parent, int child);

	void addAllParentChilds(std::unordered_map<int, int> parentToChild);

	int getChild(int parent);

	int getParent(int child);

	bool inRelationship(int parentNumber, int childNumber);

	bool isEmpty();

	void addChild(int parent, int child);

	void addParent(int parent, int child);

	void flipParentToChild(std::unordered_map<int, int> parentToChild);

private:
	std::unordered_map<int, int> parentToChildMap;
	std::unordered_map<int, int> childToParentMap;
};
