#pragma once

#include <set>

using namespace std;

class WhileTable {
public:
	WhileTable();

	void addWhileNumber(int whileNumber);

	void addAllWhileNumbers(std::set<int> whileNumbers);

	std::set<int> getAllWhileNumbers();

private:
	std::set<int> whileTable;
};