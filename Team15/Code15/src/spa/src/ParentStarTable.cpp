#include "ParentStarTable.h"

ParentStarTable::ParentStarTable() = default;

void ParentStarTable::addParentStar(int parent, set<int> children) {
	addChildren(parent, children);
	addParents(parent, children);
}

std::set<int> ParentStarTable::getChildren(int parent) {
	auto pair = parentToChildrenMap.find(parent);
	if (pair == parentToChildrenMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> ParentStarTable::getParents(int children) {
	auto pair = childToParentsMap.find(children);
	if (pair == childToParentsMap.end()) {
		return {};
	}
	return pair->second;
}

bool ParentStarTable::inRelationship(int parentNumber, int childrenNumber) {
	auto pair = parentToChildrenMap.find(parentNumber);
	if (pair == parentToChildrenMap.end()) {
		return false;
	}
	auto children = pair->second;
	auto child = children.find(childrenNumber);
	if (child == children.end()) {
		return false;
	}
	return true;
}

bool ParentStarTable::isEmpty() {
	return parentToChildrenMap.empty() && childToParentsMap.empty();
}

void ParentStarTable::addChildren(int parent, std::set<int> children) {
	auto pair = parentToChildrenMap.find(parent);
	if (pair == parentToChildrenMap.end()) {
		parentToChildrenMap[parent] = children;
	}
	else {
		pair->second.insert(children.begin(), children.end());
	}
}

void ParentStarTable::addParents(int parent, set<int> children) {
	std::set<int>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		auto pair = childToParentsMap.find(*child);
		if (pair == childToParentsMap.end()) {
			childToParentsMap[*child] = { parent };
		}
		else {
			pair->second.insert(parent);
		}
	}
}