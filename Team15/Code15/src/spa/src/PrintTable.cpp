#include "PrintTable.h"

PrintTable::PrintTable() = default;

void PrintTable::addPrintNumber(int printNumber) {
	printTable.insert(printNumber);
}

std::set<int> PrintTable::getAllPrintNumbers() {
	return printTable;
}