#pragma once

#include <set>

using namespace std;

class ReadTable {
public:
	ReadTable();

	void addReadNumber(int readNumber);
	
	void addAllReadNumbers(std::set<int> readNumbers);

	std::set<int> getAllReadNumbers();

private:
	std::set<int> readTable;
};