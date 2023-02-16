#pragma once

#include <set>

using namespace std;

class ReadTable {
public:
	ReadTable();

	void addReadNumber(int readNumber);

	std::set<int> getAllReadNumbers();

private:
	std::set<int> readTable;
};