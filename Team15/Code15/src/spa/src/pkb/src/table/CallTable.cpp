#include "pkb/include/table/CallTable.h"

CallTable::CallTable() = default;

void CallTable::addCallNumber(int callNumber) {
	callTable.insert(callNumber);
}

void CallTable::addAllCallNumbers(std::set<int> callNumbers) {
	callTable = callNumbers;
}

std::set<int> CallTable::getAllCallNumbers() {
	return callTable;
}