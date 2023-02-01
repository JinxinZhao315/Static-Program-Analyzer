#include "PreProcessedResults.h"

#pragma once
class PQLOneSynonymCheck {
public:
	PQLOneSynonymCheck();

	~PQLOneSynonymCheck();

	bool checkPQLOneSynonym(PreProcessedResults preProcessedResults);

	bool checkSynonym();
};