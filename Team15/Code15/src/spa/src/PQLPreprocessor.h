#include<utility>
#include<string>
#include"Query.h"
#include"QueryTokenizer.h"
#include"SelectClause.h"
#include"SuchThatClause.h"
#include"PatternClause.h"

#pragma once

class PQLPreprocessor {
public:
	Query preprocess(std::string input);
	/*bool validateRelationship(std::string relationship, std::string leftArg, std::string rightArg);
	bool validateStmtRef(std::string input);
	bool validateEntRef(std::string input);
	bool validatePattern(std::string assign, std::string leftArg, std::string rightArg);
	bool validateExprSpec(std::string input);*/
private:

};