#include "pkb/include/table/WhileTable.h"

WhileTable::WhileTable() = default;

void WhileTable::addWhileNumber(int whileNumber) {
	whileTable.insert(whileNumber);
}

void WhileTable::addAllWhileNumbers(std::set<int> whileNumbers) {
	whileTable = whileNumbers;
}

std::set<int> WhileTable::getAllWhileNumbers() {
	return whileTable;
}