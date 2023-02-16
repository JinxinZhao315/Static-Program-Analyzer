#pragma once

#include <set>

using namespace std;

class CallTable {
public:
	CallTable();

	void addCallNumber(int callNumber);

	std::set<int> getAllCallNumbers();

private:
	std::set<int> callTable;
};