#include "AbstractionTable.h"

template <typename L, typename R>
AbstractionTable<L, R>::AbstractionTable() = default;

template <typename L, typename R>
void AbstractionTable<L, R>::addRhs(L lhs, R rhs) {
	auto pair = lhsToRhsMap.find(lhs);
	if (pair == lhsToRhsMap.end()) {
		lhsToFirstRhsMap[lhs] = rhs;
		lhsToRhsMap[lhs] = { rhs };
	}
	else {
		pair->second.insert(rhs);
	}
}

template <typename L, typename R>
void AbstractionTable<L, R>::addLhs(L lhs, R rhs) {
	auto pair = rhsToLhsMap.find(rhs);
	if (pair == rhsToLhsMap.end()) {
		rhsToFirstLhsMap[rhs] = lhs;
		rhsToLhsMap[rhs] = { lhs };
	}
	else {
		pair->second.insert(rhs);
	}
}

template <typename L, typename R>
void AbstractionTable<L, R>::addAbstraction(L lhs, R rhs) {
	addRhs(lhs, rhs);
	addLhs(lhs, rhs);
}

template <typename L, typename R>
void AbstractionTable<L, R>::getRhsAbstraction(L lhs) {
	auto pair = lhsToRhsMap.find(lhs);
	if (pair == lhsToRhsMap.end()) {
		return {};
	}
	return pair->second;
}

template <typename L, typename R>
void AbstractionTable<L, R>::getLhsAbstraction(R rhs) {
	auto pair = rhsToLhsMap.find(rhs);
	if (pair == rhsToLhsMap.end()) {
		return {};
	}
	return pair->second;
}

template <typename L, typename R>
void AbstractionTable<L, R>::getFirstRhsAbstraction(L lhs) {
	auto pair = lhsToFirstRhsMap.find(lhs);
	if (pair == lhsToFirstRhsMap.end()) {
		return nullptr;
	}
	return pair->second;
}

template <typename L, typename R>
void AbstractionTable<L, R>::getFirstLhsAbstraction(R rhs) {
	auto pair = rhsToFirstLhsMap.find(rhs);
	if (pair == rhsToFirstLhsMap.end()) {
		return nullptr;
	}
	return pair->second;
}

template <typename L, typename R>
bool AbstractionTable<L, R>::inRelationship(L lhs, R rhs) {
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