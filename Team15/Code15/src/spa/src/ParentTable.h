#pragma once

#include <unordered_map>

using namespace std;

class ParentTable {
public:
	ParentTable();

	void addParentChild(int parent, int child);

	int getChild(int parent);

	int getParent(int child);

	bool inRelationship(int parentNumber, int childNumber);

	bool isEmpty();

	void addChild(int parent, int child);

	void addParent(int parent, int child);

private:
	std::unordered_map<int, int> parentToChildMap;
	std::unordered_map<int, int> childToParentMap;
};
