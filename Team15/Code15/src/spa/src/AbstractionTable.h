#pragma once

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename L, typename R>
class AbstractionTable {
public:
	inline AbstractionTable() = default;

	inline void AbstractionTable::addAbstraction(L lhs, R rhs) {
		addRhs(lhs, rhs);
		addLhs(lhs, rhs);
	}

	inline void AbstractionTable::getRhsAbstraction(L lhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline void AbstractionTable::getLhsAbstraction(R rhs) {
		auto pair = rhsToLhsMap.find(rhs);
		if (pair == rhsToLhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline void AbstractionTable::getFirstRhsAbstraction(L lhs) {
		auto pair = lhsToFirstRhsMap.find(lhs);
		if (pair == lhsToFirstRhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline void AbstractionTable::getFirstLhsAbstraction(R rhs) {
		auto pair = rhsToFirstLhsMap.find(rhs);
		if (pair == rhsToFirstLhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline bool AbstractionTable::inRelationship(L lhs, R rhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			return false;
		}
		auto rhsAbstraction = pair->second;
		auto rhsAbstractionValue = rhsAbstraction.find(rhs);
		if (rhsAbstractionValue == rhsAbstraction.end()) {
			return false;
		}
		return true;
	}

private:
	unordered_map<L, unordered_set<R>> lhsToRhsMap;
	unordered_map<R, unordered_set<L>> rhsToLhsMap;
	unordered_map<L, R> lhsToFirstRhsMap;
	unordered_map<R, L> rhsToFirstLhsMap;

	inline void AbstractionTable::addRhs(L lhs, R rhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			lhsToFirstRhsMap[lhs] = rhs;
			lhsToRhsMap[lhs] = { rhs };
		}
		else {
			pair->second.insert(rhs);
		}
	}

	inline void AbstractionTable::addLhs(L lhs, R rhs) {
		auto pair = rhsToLhsMap.find(rhs);
		if (pair == rhsToLhsMap.end()) {
			rhsToFirstLhsMap[rhs] = lhs;
			rhsToLhsMap[rhs] = { lhs };
		}
		else {
			pair->second.insert(rhs);
		}
	}
};
