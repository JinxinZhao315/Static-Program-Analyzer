#include "qps/include/model/Query.h"
#include "PQLRefConsistentLogic.h"
#include "common/include/utils/Utility.h"
#include <memory>

#pragma once

class PQLRefConsistentCheck {
public:
	PQLRefConsistentCheck();

	~PQLRefConsistentCheck();

	bool checkPQLRefConsistent(Query query);
};