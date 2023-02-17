#include "pkb/include/table/PrintTable.h"

PrintTable::PrintTable() = default;

void PrintTable::addPrintNumber(int printNumber) {
	printTable.insert(printNumber);
}

void PrintTable::addAllPrintNumbers(std::set<int> printNumbers) {
	printTable = printNumbers;
}

std::set<int> PrintTable::getAllPrintNumbers() {
	return printTable;
}