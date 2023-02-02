#pragma once

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename Lhs, typename Rhs>
class AbstractionTable {
public:
	AbstractionTable() = default;

	void addAbstraction(const Lhs& lhs, const Rhs& rhs) {
		addRhs(lhs, rhs);
		addLhs(lhs, rhs);
	}

	void getRhsAbstraction(const Lhs& lhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	void getLhsAbstraction(const Rhs& rhs) {
		auto pair = rhsToLhsMap.find(rhs);
		if (pair == rhsToLhsMap.end()) {
			return {};
		}
		return pair->second;
	}

	void getFirstRhsAbstraction(const Lhs& lhs) {
		auto pair = lhsToFirstRhsMap.find(lhs);
		if (pair == lhsToFirstRhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	void getFirstLhsAbstraction(const Rhs& rhs) {
		auto pair = rhsToFirstLhsMap.find(rhs);
		if (pair == rhsToFirstLhsMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	bool inRelationship(const Lhs& lhs, const Rhs& rhs) {
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
	unordered_map<Lhs, unordered_set<Rhs>> lhsToRhsMap;
	unordered_map<Rhs, unordered_set<Lhs>> rhsToLhsMap;
	unordered_map<Lhs, Rhs> lhsToFirstRhsMap;
	unordered_map<Rhs, Lhs> rhsToFirstLhsMap;

    void addRhs(const Lhs& lhs, const Rhs& rhs) {
		auto pair = lhsToRhsMap.find(lhs);
		if (pair == lhsToRhsMap.end()) {
			lhsToFirstRhsMap[lhs] = rhs;
			lhsToRhsMap[lhs] = { rhs };
		}
		else {
			pair->second.insert(rhs);
		}
	}

	void addLhs(const Lhs& lhs, const Rhs& rhs) {
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