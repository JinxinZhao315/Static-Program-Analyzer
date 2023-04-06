#include<utility>
#include<string>
#include<queue>
#include"QPS/include/model/Query.h"
#include"QueryTokenizer.h"
#include"QPS/include/model/SelectClause.h"
#include"QPS/include/model/SuchThatClause.h"
#include"QPS/include/model/PatternClause.h"
#include"QPS/include/model/WithClause.h"
#include "PQLSemanticCheck.h"
#include "exceptions/PQLSemanticError.h"
#include "QPS/include/tokenizer/QueryEvalSeqOptimizer.h"

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