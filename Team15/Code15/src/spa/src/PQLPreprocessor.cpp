#include"PQLPreprocessor.h"

Query PQLPreprocessor::preprocess(std::string input) {
	QueryTokenizer queryTokenizer;
	std::pair<std::string, std::string> declarationClausePair = queryTokenizer.tokenizeQuery(input);
	//queryTokenizer.tokenizeDeclaration(declarationClausePair.first);
	SelectClause selectClause = queryTokenizer.tokenizeSelectClause(input);


	SelectClause selectClause = queryTokenizer.tokenizeSelectClause(input);
	SelectClause selectClause = queryTokenizer.tokenizeSelectClause(input);
}