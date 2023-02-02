#include "Query.h"
#include "PQLRefConsistentLogic.h"
#include <memory>

#pragma once

class PQLRefConsistentCheck {
public:
	PQLRefConsistentCheck();

	~PQLRefConsistentCheck();

	bool checkPQLRefConsistent(Query query);

	bool checkSynonym();

	std::string PQLRefConsistentCheck::getPrimitiveType(std::string varName);
};