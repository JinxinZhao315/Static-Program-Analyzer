#pragma once

#include <set>

using namespace std;

class WhileTable {
public:
	WhileTable();

	void addWhileNumber(int whileNumber);

	std::set<int> getAllWhileNumbers();

private:
	std::set<int> whileTable;
};