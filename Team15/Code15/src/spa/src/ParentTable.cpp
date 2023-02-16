#include "ParentTable.h"

ParentTable::ParentTable() = default;

void ParentTable::addParentChild(int parent, int child) {
	addChild(parent, child);
	addParent(parent, child);
}

void ParentTable::addAllParentChilds(std::unordered_map<int, int> parentToChild) {
	parentToChildMap = parentToChild;
	flipParentToChild(parentToChild);
}

int ParentTable::getChild(int parent) {
	auto pair = parentToChildMap.find(parent);
	if (pair == parentToChildMap.end()) {
		return -1;
	}
	return pair->second;
}

int ParentTable::getParent(int child) {
	auto pair = childToParentMap.find(child);
	if (pair == childToParentMap.end()) {
		return -1;
	}
	return pair->second;
}

bool ParentTable::inRelationship(int parentNumber, int childNumber) {
	auto pair = parentToChildMap.find(parentNumber);
	if (pair == parentToChildMap.end()) {
		return false;
	}
	auto child = pair->second;
	if (child == childNumber) {
		return true;
	}
	return false;
}

bool ParentTable::isEmpty() {
	return parentToChildMap.empty() && childToParentMap.empty();
}

void ParentTable::addChild(int parent, int child) {
	auto pair = parentToChildMap.find(parent);
	if (pair == parentToChildMap.end()) {
		parentToChildMap[parent] = child;
	}
}

void ParentTable::addParent(int parent, int child) {
	auto pair = childToParentMap.find(child);
	if (pair == childToParentMap.end()) {
		childToParentMap[child] = parent;
	}
}

void ParentTable::flipParentToChild(std::unordered_map<int, int> parentToChild) {
	for (const auto& [key, value] : parentToChild) {
		childToParentMap[value] = key;
	}
}