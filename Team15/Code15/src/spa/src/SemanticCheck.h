#include "PreProcessedResults.h"

#pragma once

class SemanticCheck {
public:
	SemanticCheck();

	~SemanticCheck();

	bool checkSemantics(PreProcessedResults preProcessedResults);
};
