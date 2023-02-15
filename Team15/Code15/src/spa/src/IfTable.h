#pragma once

#include <set>

using namespace std;

class IfTable {
public:
	IfTable();

	void addIfNumber(int ifNumber);

	std::set<int> getAllIfNumbers();

private:
	std::set<int> ifTable;
};