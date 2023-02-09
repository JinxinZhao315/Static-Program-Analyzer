#include<utility>
#include<string>
#include"QPS/Query.h"
#include"QPS/QueryTokenizer.h"
#include"QPS/SelectClause.h"
#include"QPS/SuchThatClause.h"
#include"PatternClause.h"
#include "PQLSemanticCheck.h"
#include "exceptions/PQLSemanticError.h"

#pragma once

class PQLPreprocessor {
public:
	PQLPreprocessor();
	Query preprocess(std::string input);
private:
    QueryTokenizer tokenizer;
    PQLSemanticCheck semanticChecker;
};