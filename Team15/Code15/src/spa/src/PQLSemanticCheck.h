#include "PQLOneSynonymCheck.h"
#include "PQLRefConsistentCheck.h"
#include <memory>

#pragma once

class PQLSemanticCheck {
public:
	PQLSemanticCheck();

	~PQLSemanticCheck();

	bool checkSemantics(Query query);

	bool checkSynonym();
};
