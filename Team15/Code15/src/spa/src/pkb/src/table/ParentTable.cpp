#include "pkb/include/table/ParentTable.h"

ParentTable::ParentTable() = default;

void ParentTable::addParentChildren(int parent, std::set<int> children) {
	addChildren(parent, children);
	addParent(parent, children);
}

void ParentTable::addAllParentChildren(std::unordered_map<int, std::set<int>> parentToChildren) {
	parentToChildrenMap = parentToChildren;
	flip(parentToChildren);
}

std::set<int> ParentTable::getChildren(int parent) {
	auto pair = parentToChildrenMap.find(parent);
	if (pair == parentToChildrenMap.end()) {
		return {};
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
	auto pair = childToParentMap.find(childNumber);
	if (pair == childToParentMap.end()) {
		return false;
	}
	int parent = pair->second;
	if (parent == parentNumber) {
		return true;
	}
	return false;
}

bool ParentTable::isEmpty() {
	return parentToChildrenMap.empty() && childToParentMap.empty();
}

void ParentTable::addChildren(int parent, std::set<int> children) {
	auto pair = parentToChildrenMap.find(parent);
	if (pair == parentToChildrenMap.end()) {
		parentToChildrenMap[parent] = children;
	}
	else {
		pair->second.insert(children.begin(), children.end());
	}
}

void ParentTable::addParent(int parent, std::set<int> children) {
	for (int child : children) {
		auto pair = childToParentMap.find(child);
		if (pair == childToParentMap.end()) {
			childToParentMap[child] = parent;
		}
	}
}

void ParentTable::flip(std::unordered_map<int, std::set<int>> parentToChildren) {
	for (const auto& [parent, children] : parentToChildren) {
		for (int child : children) {
			childToParentMap[child] = parent;
		}
	}
}