#include "Query.h"
#include "Utility.h"

#pragma once
class PQLOneSynonymCheck {
public:
	PQLOneSynonymCheck();

	~PQLOneSynonymCheck();

	bool checkPQLOneSynonym(Query query);
};