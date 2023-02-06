#pragma once

#include <stdio.h>
#include <iostream>
#include <map>
#include <set>

using namespace std;

template <typename L, typename R>
class AbstractionTable {
public:
	inline AbstractionTable() = default;

	inline void addAbstraction(L lhs, R rhs) {
		addRhs(lhs, rhs);
		addLhs(lhs, rhs);
	}

	inline std::set<R> getRhsAbstraction(L lhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<L> getLhsAbstraction(R rhs) {
		auto pair = rhsToLhsMap.find(rhs);
		if (pair == rhsToLhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline R getFirstRhsAbstraction(L lhs) {
		auto pair = lhsToFirstRhsMap.find(lhs);
		if (pair == lhsToFirstRhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline L getFirstLhsAbstraction(R rhs) {
		auto pair = rhsToFirstLhsMap.find(rhs);
		if (pair == rhsToFirstLhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline bool inRelationship(L lhs, R rhs) {
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
	std::map<L, std::set<R>> lhsToRhsMap;
	std::map<R, std::set<L>> rhsToLhsMap;
	std::map<L, R> lhsToFirstRhsMap;
	std::map<R, L> rhsToFirstLhsMap;

	inline void addRhs(L lhs, R rhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			lhsToFirstRhsMap[lhs] = rhs;
			lhsToRhsMap[lhs] = { rhs };
		}
		else {
			pair->second.insert(rhs);
		}
	}

	inline void addLhs(L lhs, R rhs) {
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
