#pragma once

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename L, typename R>
class AbstractionTable {
public:
	AbstractionTable();

	void addAbstraction(L lhs, R rhs);

	void getRhsAbstraction(L lhs);

	void getLhsAbstraction(R rhs);

	void getFirstRhsAbstraction(L lhs);

	void getFirstLhsAbstraction(R rhs);

	bool inRelationship(L lhs, R rhs);

	void addRhs(L lhs, R rhs);

	void addLhs(L lhs, R rhs);

private:
	unordered_map<L, unordered_set<R>> lhsToRhsMap;
	unordered_map<R, unordered_set<L>> rhsToLhsMap;
	unordered_map<L, R> lhsToFirstRhsMap;
	unordered_map<R, L> rhsToFirstLhsMap;
};