#include "PreProcessedResults.h"
#include "PQLRefConsistentLogic.h"
#include <memory>

#pragma once

class PQLRefConsistentCheck {
public:
	PQLRefConsistentCheck();

	~PQLRefConsistentCheck();

	bool checkPQLRefConsistent(PreProcessedResults preProcessedResults);

	bool checkSynonym();
};