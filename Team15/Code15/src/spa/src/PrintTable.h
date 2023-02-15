#pragma once

#include <set>

using namespace std;

class PrintTable {
public:
	PrintTable();

	void addPrintNumber(int printNumber);

	std::set<int> getAllPrintNumbers();

private:
	std::set<int> printTable;
};