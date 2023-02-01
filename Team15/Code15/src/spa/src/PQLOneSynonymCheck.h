#include "Query.h"

#pragma once
class PQLOneSynonymCheck {
public:
	PQLOneSynonymCheck();

	~PQLOneSynonymCheck();

	bool checkPQLOneSynonym(Query query);

	bool checkSynonym();
};