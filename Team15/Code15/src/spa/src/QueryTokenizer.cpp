#include "QueryTokenizer.h"	
#include <memory>
#pragma once

void QueryTokenizer::tokenizeQuery(std::string queryString) {
	size_t lastSemicolon = queryString.find_last_of(';');
	std::multimap<std::string, std::string> varTable;
	//std::shared_ptr<SelectClause> selectClause_ptr = std::make_shared<SelectClause>();
	SelectClause selectClause;
	std::vector<SuchThatClause> suchThatClauses;
	std::vector<PatternClause> patternClauses;
	if (lastSemicolon == std::string::npos) {
		//tokenize select

	}
	else {
		std::string declaration = trim(queryString.substr(0, lastSemicolon));
		std::string remainingQuery = trim(queryString.substr(lastSemicolon + 1));
		//varTable = tokenizeDeclaration(declaration);
		tokenizeClauses(remainingQuery, selectClause, suchThatClauses, patternClauses);
	}
}

//std::multimap<std::string, std::string> QueryTokenizer::tokenizeDeclaration(std::string input) {
//	
//}

void QueryTokenizer::tokenizeClauses(std::string input, SelectClause& selectClause,
	std::vector<SuchThatClause>& suchThatClauses, std::vector<PatternClause>& patternClauses) {
	PQLSyntaxChecker syntaxChecker;
	std::string keyword = extractKeyword(input);
	if (keyword != "Select") {
		throw - 1;
	}
	tokenizeSelectClause(input, selectClause, syntaxChecker);
	while (input.length() != 0) {
		keyword = extractKeyword(input);
		if (keyword == "such") {
			tokenizeSuchThatClause(input, suchThatClauses, syntaxChecker);
		}
		else if (keyword == "pattern") {
			tokenizePatternClause(input, patternClauses, syntaxChecker);
		}
		else {
			throw - 1;
		}
	}
}

void QueryTokenizer::tokenizeSelectClause(std::string& input, SelectClause& selectClause, PQLSyntaxChecker syntaxChecker) {
	std::size_t synonymEndIndex = input.find_first_of(" \t\n");
	std::string synonym = input.substr(0, synonymEndIndex + 1);
	if (!syntaxChecker.validateSynonym(synonym)) {
		throw - 1;
	}
	//selectClause = new SelectClause(synonym, "synonym");
	input = trim(input.substr(synonymEndIndex + 1));
	return;
}

void QueryTokenizer::tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauses, PQLSyntaxChecker syntaxChecker) {
	/*std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw - 1;
	}*/
	std::string keyword = extractKeyword(input);
	if (keyword != "that") {
		throw - 1;
	}
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t nextComma = input.find_first_of(",");
	std::size_t nextRightPar = input.find_first_of(")");

	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw - 1;
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw - 1;
	}
	std::string relationship = trim(input.substr(0, nextLeftPar));
	std::string leftArg = trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar));
	//std::string leftArgType = getType(leftArg);
	std::string rightArg = trim(input.substr(nextComma + 1, nextRightPar - nextComma));
	//std::string rightArgType = getType(rightArg);
	if (!syntaxChecker.validateRelationship(relationship, leftArg, rightArg)) {
		throw - 1;
	}
	suchThatClauses.push_back(SuchThatClause(relationship, leftArg, "integer", rightArg, "integer"));
	return;
}

std::string QueryTokenizer::getType(std::string& input) {
	return "string example";
}

void QueryTokenizer::tokenizePatternClause(std::string& input, std::vector<PatternClause>& patternClauses, PQLSyntaxChecker syntaxChecker) {
	std::string keyword = extractKeyword(input);
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t nextComma = input.find_first_of(",");
	std::size_t nextRightPar = input.find_first_of(")");
	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw - 1;
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw - 1;
	}
	std::string relationship = trim(input.substr(0, nextLeftPar));
	std::string leftArg = trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar));
	std::string rightArg = trim(input.substr(nextComma + 1, nextRightPar - nextComma));
	if (!syntaxChecker.validatePattern(keyword, leftArg, rightArg)) {
		throw - 1;
	}
	patternClauses.push_back(PatternClause("assign", keyword, "integer",
		leftArg, "integer", rightArg));
}

std::string QueryTokenizer::extractKeyword(std::string& input) {
	std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw - 1;
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	input = trim(input.substr(nextWhiteSpace));
	return keyword;
}

std::string QueryTokenizer::trim(std::string input) {
	std::size_t firstCharIndex = input.find_first_not_of(" \t\n");
	std::size_t lastCharIndex = input.find_last_not_of(" \t\n");
	if (firstCharIndex == std::string::npos) {
		return "";
	}
	else {
		return input.substr(firstCharIndex, lastCharIndex - firstCharIndex + 1);
	}
}