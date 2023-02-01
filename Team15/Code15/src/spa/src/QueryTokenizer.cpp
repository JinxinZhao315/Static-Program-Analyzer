#include "QueryTokenizer.h"	


void QueryTokenizer::tokenizeQuery(std::string queryString) {
	size_t lastSemicolon = queryString.find_last_of(';');
	std::multimap<std::string, std::string> varTable;
	//std::shared_ptr<SelectClause> selectClause_ptr = std::make_shared<SelectClause>();
	SelectClause selectClause;
	std::vector<SuchThatClause> suchThatClauses;
	std::vector<PatternClause> patternClauses;
	if (lastSemicolon == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: No synonym declaration");
	}
	else {
		std::string declaration = trim(queryString.substr(0, lastSemicolon));
		std::string remainingQuery = trim(queryString.substr(lastSemicolon + 1));
		//varTable = tokenizeDeclaration(declaration);
		tokenizeClauses(remainingQuery, selectClause, suchThatClauses, patternClauses);
	}
}

std::multimap<std::string, std::string> QueryTokenizer::tokenizeDeclaration(std::string declaration) {
    size_t semicolonPos = declaration.find(";");
    std::multimap<std::string, std::string> varTable;
    while (semicolonPos != std::string::npos) {
        size_t whiteSpacePos = declaration.find_first_of(" \t\n");
        std::string designEntity = declaration.substr(0, whiteSpacePos);

        bool isDeValid = syntaxChecker.validateDesignEntity(designEntity);

        if (!isDeValid) {
            throw PQLSyntaxError("PQL syntax error: invalid design entity in declaration");
        }
        std::string synonymStr = trim(declaration.substr(whiteSpacePos, semicolonPos - whiteSpacePos));
        std::vector<std::string> synonymVector = tokenizeCsv(synonymStr);

        for (std::string synon: synonymVector) {
            bool isSynonValid = syntaxChecker.validateSynonym(synon);
            if (!isSynonValid) {
                throw PQLSyntaxError("PQL syntax error: invalid synonym");
            }
            varTable.insert({designEntity, synon});
        }

        declaration = trim(declaration.substr((semicolonPos + 1)));
        semicolonPos = declaration.find(";");

        return varTable;
    }
}

void QueryTokenizer::tokenizeClauses(std::string input, SelectClause& selectClause,
	std::vector<SuchThatClause>& suchThatClauses, std::vector<PatternClause>& patternClauses) {

	std::string keyword = extractKeyword(input);
	if (keyword != "Select") {
		throw PQLSyntaxError("PQL syntax error: No 'select' keyword");
	}
	tokenizeSelectClause(input, selectClause);
	while (input.length() != 0) {
		keyword = extractKeyword(input);
		if (keyword == "such") {
			tokenizeSuchThatClause(input, suchThatClauses);
		}
		else if (keyword == "pattern") {
			tokenizePatternClause(input, patternClauses);
		}
		else {
			throw PQLSyntaxError("PQL syntax error: Unknown keyword");
		}
	}
}

void QueryTokenizer::tokenizeSelectClause(std::string& input, SelectClause& selectClause) {
	std::size_t synonymEndIndex = input.find_first_of(" \t\n");
	std::string synonym = input.substr(0, synonymEndIndex + 1);
	if (!syntaxChecker.validateSynonym(synonym)) {
		throw PQLSyntaxError("PQL syntax error: Invalid synonym");
	}
	//selectClause = new SelectClause(synonym, "synonym");
	input = trim(input.substr(synonymEndIndex + 1));
	return;
}

void QueryTokenizer::tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauses) {
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
	suchThatClauses.push_back(SuchThatClause(relationship, leftArg, "integer", rightArg, "integer"));
	return;
}

std::string QueryTokenizer::getType(std::string& input) {
	return "string example";
}

void QueryTokenizer::tokenizePatternClause(std::string& input, std::vector<PatternClause>& patternClauses) {
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
	patternClauses.push_back(PatternClause("assign", keyword, "integer",
		leftArg, "integer", rightArg));
}

std::string QueryTokenizer::extractKeyword(std::string& input) {
	std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid keyword");
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	input = trim(input.substr(nextWhiteSpace));
	return keyword;
}

std::string QueryTokenizer::trim(std::string input) {
    std::string trimmed = input;
    std::size_t firstWhitespace = trimmed.find_first_not_of(" \t\n");
    // trim left
	if (firstWhitespace != std::string::npos) {
		trimmed = trimmed.substr(firstWhitespace);
	}
    // trim right
    std::size_t lastWhitespace = trimmed.find_last_not_of(" \t\n");
    if (lastWhitespace != std::string::npos) {
        trimmed = trimmed.substr(0, lastWhitespace + 1);
    }
    return trimmed;
}

std::vector<std::string> QueryTokenizer::tokenizeCsv(std::string csv) {
    std::vector<std::string> ret;
    std::string remainder = csv;
    size_t commaIndex = remainder.find(",");
    while (commaIndex != std::string::npos) {
        std::string str = trim(remainder.substr(0, commaIndex));
        ret.push_back(str);
        remainder = trim(remainder.substr((commaIndex + 1)));
        commaIndex = remainder.find(",");
    }

    if (remainder.empty()) {
        throw PQLSyntaxError("PQL syntax error: comma list is empty or end with comma");
    }
    ret.push_back(remainder);
    return ret;
}