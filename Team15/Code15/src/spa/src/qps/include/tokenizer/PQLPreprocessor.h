#include<utility>
#include<string>
#include<queue>
#include"qps/include/model/Query.h"
#include"QueryTokenizer.h"
#include"qps/include/model/SelectClause.h"
#include"qps/include/model/SuchThatClause.h"
#include"qps/include/model/PatternClause.h"
#include"qps/include/model/WithClause.h"
#include "PQLSemanticCheck.h"
#include "exceptions/PQLSemanticError.h"
#include "qps/include/tokenizer/QueryEvalSeqOptimizer.h"

#pragma once

class PQLPreprocessor {
public:
	PQLPreprocessor();
	Query preprocess(std::string input);
private:
    QueryTokenizer tokenizer;
    PQLSemanticCheck semanticChecker;
	std::vector<Clause> orderEvalSequence(Query query);
};