#include "QPS/include/tokenizer/PQLOneSynonymCheck.h"
#include "QPS/include/tokenizer/PQLRefConsistentCheck.h"
#include <memory>

#pragma once

class PQLSemanticCheck {
public:
	PQLSemanticCheck();

	~PQLSemanticCheck();

	std::pair<bool,std::string> checkSemantics(Query query);
};
