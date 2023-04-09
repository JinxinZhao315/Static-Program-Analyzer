#include "qps/include/tokenizer/PQLOneSynonymCheck.h"
#include "qps/include/tokenizer/PQLRefConsistentCheck.h"
#include <memory>

#pragma once

class PQLSemanticCheck {
public:
	PQLSemanticCheck();

	~PQLSemanticCheck();

	std::pair<bool,std::string> checkSemantics(Query query);
};
