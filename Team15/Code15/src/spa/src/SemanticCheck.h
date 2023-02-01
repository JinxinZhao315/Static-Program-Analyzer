#include "Query.h"

#pragma once

class SemanticCheck {
public:
	SemanticCheck();

	~SemanticCheck();

	bool checkSemantics(Query query);
};
