#include "QueryTokenizer.h"	

QueryTokenizer::QueryTokenizer() {
    this->syntaxChecker = PQLSyntaxChecker();
}

std::pair<std::string, std::string> QueryTokenizer::tokenizeQuery(std::string input) {
	size_t lastSemicolon = input.find_last_of(';');
	if (lastSemicolon == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: No synonym declaration");
	}
	else {
		std::string declaration = trim(input.substr(0, lastSemicolon + 1));
		std::string remainingQuery = trim(input.substr(lastSemicolon + 1));
		//varTable = tokenizeDeclaration(declaration);
		return std::make_pair(declaration, remainingQuery);
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
            varTable.insert({synon, designEntity});
        }

        declaration = trim(declaration.substr((semicolonPos + 1)));
        semicolonPos = declaration.find(";");
    }
	return varTable;
}

void QueryTokenizer::tokenizeClauses(std::string input, SelectClause& selectClause,
	SuchThatClause& suchThatClause, PatternClause& patternClause) {
	std::string keyword = extractKeyword(input);
	if (keyword != "Select") {
		throw PQLSyntaxError("PQL syntax error: No 'select' keyword");
	}
	tokenizeSelectClause(input, selectClause);
	while (input.length() != 0) {
		keyword = extractKeyword(input);
		if (keyword == "such") {
			tokenizeSuchThatClause(input, suchThatClause);
		}
		else if (keyword == "pattern") {
			tokenizePatternClause(input, patternClause);
		}
		else {
			throw PQLSyntaxError("PQL syntax error: Unknown keyword");
		}
	}
}

void QueryTokenizer::tokenizeSelectClause(std::string& input, SelectClause& selectClause) {
	std::size_t synonymEndIndex = input.find_first_of(" \t\n");
	std::string synonym;
	if (synonymEndIndex == std::string::npos) {
		synonym = input;
		input = "";
	} else {
		synonym = input.substr(0, synonymEndIndex);
		input = trim(input.substr(synonymEndIndex + 1));
	}
	if (!syntaxChecker.validateSynonym(synonym)) {
		throw PQLSyntaxError("PQL syntax error: Invalid synonym");
	};
	selectClause = SelectClause(synonym);
}

void QueryTokenizer::tokenizeSuchThatClause(std::string& input, SuchThatClause& suchThatClause) {
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
	std::string leftArg = trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar - 1));
	std::string rightArg = trim(input.substr(nextComma + 1, nextRightPar - nextComma - 1));
	if (!syntaxChecker.validateRelationship(relationship, leftArg, rightArg)) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that relationship");
	}
	input = input.substr(nextRightPar + 1);
	suchThatClause = SuchThatClause(relationship, leftArg, rightArg);
}



void QueryTokenizer::tokenizePatternClause(std::string& input, PatternClause& patternClause) {
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
	input = input.substr(nextRightPar);
	patternClause = PatternClause("assign", keyword, leftArg, rightArg);
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