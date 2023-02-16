#include "CallTable.h"

CallTable::CallTable() = default;

void CallTable::addCallNumber(int callNumber) {
	callTable.insert(callNumber);
}

std::set<int> CallTable::getAllCallNumbers() {
	return callTable;
}