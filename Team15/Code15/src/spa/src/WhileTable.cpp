#include "WhileTable.h"

WhileTable::WhileTable() = default;

void WhileTable::addWhileNumber(int whileNumber) {
	whileTable.insert(whileNumber);
}

std::set<int> WhileTable::getAllWhileNumbers() {
	return whileTable;
}