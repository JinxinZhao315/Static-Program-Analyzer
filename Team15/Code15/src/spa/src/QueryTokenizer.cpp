#include "QueryTokenizer.h"	


std::pair<std::string, std::string> QueryTokenizer::tokenizeQuery(std::string input) {
	size_t lastSemicolon = input.find_last_of(';');
	if (lastSemicolon == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: No synonym declaration");
	}
	else {
		std::string declaration = trim(input.substr(0, lastSemicolon));
		std::string remainingQuery = trim(input.substr(lastSemicolon + 1));
		//varTable = tokenizeDeclaration(declaration);
		return std::make_pair(declaration, remainingQuery);
	}
}

//std::multimap<std::string, std::string> QueryTokenizer::tokenizeDeclaration(std::string input) {
//	
//}


//void QueryTokenizer::tokenizeClauses(std::string input, SelectClause& selectClause,
//	std::vector<SuchThatClause>& suchThatClauses, std::vector<PatternClause>& patternClauses) {
//	PQLSyntaxChecker syntaxChecker;
//	std::string keyword = extractKeyword(input);
//	if (keyword != "Select") {
//		throw PQLSyntaxError("PQL syntax error: No 'select' keyword");
//	}
//	tokenizeSelectClause(input, selectClause, syntaxChecker);
//	while (input.length() != 0) {
//		keyword = extractKeyword(input);
//		if (keyword == "such") {
//			tokenizeSuchThatClause(input, suchThatClauses, syntaxChecker);
//		}
//		else if (keyword == "pattern") {
//			tokenizePatternClause(input, patternClauses, syntaxChecker);
//		}
//		else {
//			throw PQLSyntaxError("PQL syntax error: Unknown keyword");
//		}
//	}
//}

SelectClause QueryTokenizer::tokenizeSelectClause(std::string input, PQLSyntaxChecker syntaxChecker) {
	std::size_t synonymEndIndex = input.find_first_of(" \t\n");
	std::string synonym;
	if (synonymEndIndex == std::string::npos) {
		synonym = input;
	} else {
		synonym = input.substr(0, synonymEndIndex + 1);
	}
	if (!syntaxChecker.validateSynonym(synonym) == false) {
		throw PQLSyntaxError("PQL syntax error: Invalid synonym");
	};
	return SelectClause(synonym, "entity");
}

SuchThatClause QueryTokenizer::tokenizeSuchThatClause(std::string input, PQLSyntaxChecker syntaxChecker) {
	/*std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw - 1;
	}*/
	std::string keyword = extractKeyword(input);
	if (keyword != "that") {
		throw PQLSyntaxError("PQL syntax error: No 'that' keyword");
	}
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t nextComma = input.find_first_of(",");
	std::size_t nextRightPar = input.find_first_of(")");

	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	std::string relationship = trim(input.substr(0, nextLeftPar));
	std::string leftArg = trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar));
	//std::string leftArgType = getType(leftArg);
	std::string rightArg = trim(input.substr(nextComma + 1, nextRightPar - nextComma));
	//std::string rightArgType = getType(rightArg);
	if (!syntaxChecker.validateRelationship(relationship, leftArg, rightArg)) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that relationship");
	}
	return SuchThatClause(relationship, "integer", leftArg, "integer", rightArg);
}

std::string QueryTokenizer::getType(std::string& input) {
	return "string example";
}

PatternClause QueryTokenizer::tokenizePatternClause(std::string input, PQLSyntaxChecker syntaxChecker) {
	std::string keyword = extractKeyword(input);
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t nextComma = input.find_first_of(",");
	std::size_t nextRightPar = input.find_first_of(")");
	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
	std::string relationship = trim(input.substr(0, nextLeftPar));
	std::string leftArg = trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar));
	std::string rightArg = trim(input.substr(nextComma + 1, nextRightPar - nextComma));
	if (!syntaxChecker.validatePattern(keyword, leftArg, rightArg)) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
	return PatternClause("assign", keyword, "integer", leftArg, "integer", rightArg);
}