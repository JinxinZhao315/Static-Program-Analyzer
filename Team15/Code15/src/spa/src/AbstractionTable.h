#pragma once

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename LHS, typename RHS>
class AbstractionTable {
public:
	AbstractionTable() = default;

	void storeAbstraction(const LHS& lhs, const RHS& rhs) {
		storeRhs(lhs, rhs);
		storeLhs(lhs, rhs);
	}

	void retrieveRhsAbstraction(const LHS& lhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	void retrieveLhsAbstraction(const RHS& rhs) {
		auto pair = rhsToLhsMap.find(rhs);
		if (pair == rhsToLhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	void retrieveFirstRhsAbstraction(const LHS& lhs) {
		auto pair = lhsToFirstRhsMap.find(lhs);
		if (pair == lhsToFirstRhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	void retrieveFirstLhsAbstraction(const RHS& rhs) {
		auto pair = rhsToFirstLhsMap.find(rhs);
		if (pair == rhsToFirstLhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	bool inRelationship(const LHS& lhs, const RHS& rhs) {
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
	unordered_map<LHS, unordered_set<RHS>> lhsToRhsMap;
	unordered_map<RHS, unordered_set<LHS>> rhsToLhsMap;
	unordered_map<LHS, RHS> lhsToFirstRhsMap;
	unordered_map<RHS, LHS> rhsToFirstLhsMap;

    void storeRhs(const LHS& lhs, const RHS& rhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			lhsToFirstRhsMap[lhs] = rhs;
			lhsToRhsMap[lhs] = { rhs };
		}
		else {
			pair->second.insert(rhs);
		}
	}

	void storeLhs(const LHS& lhs, const RHS& rhs) {
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