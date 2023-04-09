#include "qps/include/model/Query.h"
#include "common/include/utils/Utility.h"

#pragma once
class PQLOneSynonymCheck {
public:
	PQLOneSynonymCheck();

	~PQLOneSynonymCheck();

	bool checkPQLOneSynonym(Query query);
};