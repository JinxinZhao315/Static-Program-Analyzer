#pragma once

#include <set>

using namespace std;

class PrintTable {
public:
	PrintTable();

	void addPrintNumber(int printNumber);

	void addAllPrintNumbers(std::set<int> printNumbers);

	std::set<int> getAllPrintNumbers();

private:
	std::set<int> printTable;
};