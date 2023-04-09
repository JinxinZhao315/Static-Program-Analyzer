#include "QPS/include/tokenizer/PQLSemanticCheck.h"

PQLSemanticCheck::PQLSemanticCheck() {}

PQLSemanticCheck::~PQLSemanticCheck() {}

std::pair<bool,std::string> PQLSemanticCheck::checkSemantics(Query query) {
	PQLOneSynonymCheck* oneSynonymCheckInstance = new PQLOneSynonymCheck();
	PQLRefConsistentCheck* refConsistentCheckInstance =new PQLRefConsistentCheck();

	if (!oneSynonymCheckInstance->checkPQLOneSynonym(query)) {
		return std::make_pair(false, "PQL semantic error: synonym declared more than once");
	};
	if (!refConsistentCheckInstance->checkPQLRefConsistent(query)) {
		return std::make_pair(false, "PQL semantic error: inconsistent reference");
	};
	return std::make_pair(true, Utility::empty);
}