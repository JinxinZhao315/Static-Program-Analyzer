#include "QPS/include/tokenizer/QueryTokenizer.h"

QueryTokenizer::QueryTokenizer() {
    this->syntaxChecker = PQLSyntaxChecker();
}

std::pair<std::string, std::string> QueryTokenizer::tokenizeQuery(std::string input) {
	size_t lastSemicolon = input.find_last_of(';');
	//no declaration, can be "Select BOOLEAN"
	if (lastSemicolon == std::string::npos) {
		return std::make_pair("", input);
	}
	else {
		std::string declaration = Utility::trim(input.substr(0, lastSemicolon + 1), Utility::WHITESPACES);
		std::string remainingQuery = Utility::trim(input.substr(lastSemicolon + 1), Utility::WHITESPACES);
		//synonymTable = tokenizeDeclaration(declaration);
		return std::make_pair(declaration, remainingQuery);
	}
}

std::multimap<std::string, std::string> QueryTokenizer::tokenizeDeclaration(std::string declaration) {
    size_t semicolonPos = declaration.find(";");
    std::multimap<std::string, std::string> varTable;
    while (semicolonPos != std::string::npos) {
        size_t whiteSpacePos = declaration.find_first_of(Utility::WHITESPACES);
        std::string designEntity = declaration.substr(0, whiteSpacePos);

        bool isDeValid = syntaxChecker.validateDesignEntity(designEntity);

        if (!isDeValid) {
            throw PQLSyntaxError("PQL syntax error: invalid design entity in declaration");
        }
        std::string synonymStr = Utility::trim(declaration.substr(whiteSpacePos, semicolonPos - whiteSpacePos),
                                               Utility::WHITESPACES);
        std::vector<std::string> synonymVector = tokenizeCsv(synonymStr);

        for (std::string synon: synonymVector) {
            bool isSynonValid = syntaxChecker.validateSynonym(synon);
            if (!isSynonValid) {
                throw PQLSyntaxError("PQL syntax error: invalid synonym");
            }
            varTable.insert({synon, designEntity});
        }

        declaration = Utility::trim(declaration.substr((semicolonPos + 1)), Utility::WHITESPACES);
        semicolonPos = declaration.find(";");
    }
	return varTable;
}

void QueryTokenizer::tokenizeClauses(std::string input,
                                     std::multimap<std::string, std::string> varTable,
                                     SelectClause& selectClause,
                                     std::vector<SuchThatClause>& suchThatClauseVec,
                                     std::vector<PatternClause>& patternClauseVec,
									 std::vector<WithClause>& withClauseVec) {
	std::string keyword = extractKeyword(input);
	if (keyword != "Select") {
		throw PQLSyntaxError("PQL syntax error: No 'select' keyword");
	}
	tokenizeSelectClause(input, varTable, selectClause);
	std::string prevClauseType;
	while (input.length() != 0) {
		keyword = extractKeyword(input);
		if (keyword == "such") {
            if (extractKeyword(input) != "that") {
                throw PQLSyntaxError("PQL syntax error: No 'that' nextKey");
            }
			tokenizeSuchThatClause(input, suchThatClauseVec);
            prevClauseType = "such";
		}
		else if (keyword == "pattern") {
			tokenizePatternClause(input, varTable, patternClauseVec);
            prevClauseType = "pattern";
		} else if (keyword == "with") {
			tokenizeWithClause(input, withClauseVec, varTable);
			prevClauseType = "with";
		}
		else if (keyword == "and") {
            // Possible syntax after "and":
            // (with) s1.stmt# = 1
            // (pattern) a(_, "y")
            // (such that) Follows(a1, a3)
            std::string nextKeyword = peekKeyword(input, Utility::WHITESPACES);

            if (nextKeyword == "such" || nextKeyword == "pattern" || nextKeyword == "with") {
                throw PQLSyntaxError("PQL syntax error: Invalid use of and");
            }

            if (prevClauseType == "such") {
                tokenizeSuchThatClause(input, suchThatClauseVec);
            } else if (prevClauseType == "with") {
                tokenizeWithClause(input, withClauseVec, varTable);
            } else { // prevClauseType == "pattern"
                nextKeyword = peekKeyword(input, "(");
                if (nextKeyword == "" || Utility::getReferenceType(nextKeyword) != Utility::SYNONYM) {
                    throw PQLSyntaxError("PQL syntax error: Invalid use of and after pattern keyword");
                }
                if (std::find(relationships.begin(), relationships.end(), nextKeyword) != relationships.end()) {
                    throw PQLSyntaxError("PQL syntax error: Invalid use of and after pattern keyword");
                }
                tokenizePatternClause(input, varTable, patternClauseVec);
            }
        }
		else {
			throw PQLSyntaxError("PQL syntax error: Unknown keyword");
		}
	}
}

void QueryTokenizer::tokenizeWithClause(std::string& input, std::vector<WithClause>& withClauseVec, std::multimap<std::string, std::string> varTable) {
	std::size_t equalSignIndex = input.find_first_of('=');
	if (equalSignIndex == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid with clause, no \"=\" sign");
	}
	std::string firstArgStr = Utility::trim(input.substr(0, equalSignIndex), Utility::WHITESPACES);
	Ref firstArg = tokenizeRef(firstArgStr, varTable);
	input = Utility::trim(input.substr(equalSignIndex + 1), Utility::WHITESPACES);

	std::size_t secondArgEndIndex = input.find_first_of(Utility::WHITESPACES);
	std::string secondArgStr = "";
	//this with clause is the last clause
	if (secondArgEndIndex == std::string::npos) {
		secondArgStr = input;
		input = "";
	}
	else {
		secondArgStr = input.substr(0, secondArgEndIndex);
		input = Utility::trim(input.substr(secondArgEndIndex + 1), Utility::WHITESPACES);
	}
	Ref secondArg = tokenizeRef(secondArgStr, varTable);


	withClauseVec.push_back(WithClause(firstArg, secondArg));
}

void QueryTokenizer::tokenizeSelectClause(std::string& input, std::multimap<std::string, std::string> varTable, 
	SelectClause& selectClause) {
	std::size_t elemEndIndex = input.find_first_of(Utility::WHITESPACES);
	std::vector<std::string> elemStrList;
	//multi clause
	if (input.size() > 0 && input[0] == '<') {
		size_t rightAnglePos = input.find_first_of(">");
		if (rightAnglePos == std::string::npos) {
			throw PQLSyntaxError("PQL syntax error: Invalid multi-element list format in select clause");
		}
		elemStrList = tokenizeCsv(input.substr(1, rightAnglePos - 1));
		input = Utility::trim(input.substr(rightAnglePos + 1), Utility::WHITESPACES);
	}
	//single clause, no whitespace on the left, so no other clauses except Select single element
	else if (elemEndIndex == std::string::npos) {
		//if (!syntaxChecker.validateSynonym(input)) {
		//	throw PQLSyntaxError("PQL syntax error: Invalid synonym");
		//};
		elemStrList.push_back(input);
		input = "";
	}
	//single clause, but other restriction after the select clause
	else {
		std::string elem = input.substr(0, elemEndIndex);
		//if (!syntaxChecker.validateSynonym(synonym)) {
		//	throw PQLSyntaxError("PQL syntax error: Invalid synonym");
		//};
		elemStrList.push_back(elem);
		input = Utility::trim(input.substr(elemEndIndex + 1), Utility::WHITESPACES);
	}
	std::vector<Elem> elemList;
	for (std::string elemStr : elemStrList) {
		if (syntaxChecker.validateAttrRef(elemStr)) {
			std::size_t periodIndex = elemStr.find_first_of(".");
			std::string synName = elemStr.substr(0, periodIndex);
			std::string attrName = elemStr.substr(periodIndex + 1);
			Elem elem(AttrRef(synName, varTable.find(synName)->second, attrName));
			elemList.push_back(elem);
		}
		else if (syntaxChecker.validateSynonym(elemStr)) {
			Elem elem(elemStr);
			elemList.push_back(elem);
		}
		else {
			throw PQLSyntaxError("PQL syntax error: Invalid element format in Select Clause");
		}
	}
	
	selectClause = SelectClause(elemList);
}

void QueryTokenizer::tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauseVec) {
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t nextComma = input.find_first_of(",");
	std::size_t nextRightPar = input.find_first_of(")");

	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	std::string relationship = Utility::trim(input.substr(0, nextLeftPar), Utility::WHITESPACES);
	std::string leftArg = Utility::trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar - 1), Utility::WHITESPACES);
	std::string rightArg = Utility::trim(input.substr(nextComma + 1, nextRightPar - nextComma - 1), Utility::WHITESPACES);
	if (!syntaxChecker.validateRelationship(relationship, leftArg, rightArg)) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that relationship");
	}
	input = input.substr(nextRightPar + 1);
	suchThatClauseVec.push_back(SuchThatClause(relationship, leftArg, rightArg));
}

void QueryTokenizer::tokenizePatternClause(std::string& input,
                                           std::multimap<std::string, std::string> varTable,
                                           std::vector<PatternClause>& patternClauseVec) {
	std::size_t nextLeftPar = input.find_first_of("(");
	std::size_t firstComma = input.find_first_of(",");
    std::size_t secondComma = input.find_first_of(",", firstComma + 1);
	std::size_t nextRightPar = input.find_first_of(")");
	if (nextLeftPar == std::string::npos || firstComma == std::string::npos || nextRightPar == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
	if (nextRightPar <= firstComma + 1 || firstComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
    std::string synonym = Utility::trim(input.substr(0, nextLeftPar), Utility::WHITESPACES);
    std::string synonymType = varTable.find(synonym)->second;

    std::string firstArg;
    std::string secondArg;
    std::string thirdArg = "";

    if (synonymType == "if") {
        // 3 arguments case
        if (secondComma == std::string::npos || secondComma > nextRightPar) {
            throw PQLSyntaxError("PQL syntax error: Only 1 comma in pattern clause if type");
        }
        firstArg = Utility::trim(input.substr(nextLeftPar + 1, firstComma - nextLeftPar - 1),
                                             Utility::WHITESPACES);
        secondArg = Utility::trim(input.substr(firstComma + 1, secondComma - firstComma - 1),
                                              Utility::WHITESPACES);
        thirdArg = Utility::trim(input.substr(secondComma + 1, nextRightPar - secondComma - 1),
                                              Utility::WHITESPACES);
    } else {
        // 2 arguments case
        if (! (synonymType == "assign" || synonymType == "while")) {
            throw PQLSemanticError("PQL Semantic error: pattern clause synonym type is not assign, while or if");
        }

        if (secondComma < nextRightPar) {
            throw PQLSyntaxError("PQL syntax error: Too many commas in pattern clause assign and while type");
        }

        firstArg = Utility::trim(input.substr(nextLeftPar + 1, firstComma - nextLeftPar - 1),
                                             Utility::WHITESPACES);
        secondArg = Utility::trim(input.substr(firstComma + 1, nextRightPar - firstComma - 1),
                                              Utility::WHITESPACES);
    }

    if (!syntaxChecker.validatePattern(synonym, synonymType, firstArg, secondArg, thirdArg)) {
        throw PQLSyntaxError("PQL syntax error: Invalid pattern clause if syntax");
    }
    input = input.substr(nextRightPar + 1);
    patternClauseVec.push_back(PatternClause(synonym, firstArg, secondArg, thirdArg));
}

std::string QueryTokenizer::extractKeyword(std::string& input) {
	input = Utility::trim(input, Utility::WHITESPACES);
    std::size_t nextWhiteSpace = input.find_first_of(Utility::WHITESPACES);
	if (nextWhiteSpace == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid keyword");
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	input = Utility::trim(input.substr(nextWhiteSpace), Utility::WHITESPACES);
	return keyword;
}

std::string QueryTokenizer::peekKeyword(std::string input, std::string delimiter) {
    input = Utility::trim(input, Utility::WHITESPACES);
    std::size_t nextDelimiter = input.find_first_of(delimiter);
    if (nextDelimiter == std::string::npos) {
        return "";
    }
    std::string keyword = Utility::trim(input.substr(0, nextDelimiter), Utility::WHITESPACES);
    return keyword;
}

std::vector<std::string> QueryTokenizer::tokenizeCsv(std::string csv) {
    std::vector<std::string> ret;
    std::string remainder = csv;
    size_t commaIndex = remainder.find(",");
    while (commaIndex != std::string::npos) {
        std::string str = Utility::trim(remainder.substr(0, commaIndex), Utility::WHITESPACES);
        ret.push_back(str);
        remainder = Utility::trim(remainder.substr((commaIndex + 1)), Utility::WHITESPACES);
        commaIndex = remainder.find(",");
    }

    if (remainder.empty()) {
        throw PQLSyntaxError("PQL syntax error: comma list is empty or end with comma");
    }
    ret.push_back(remainder);
    return ret;
}

Ref QueryTokenizer::tokenizeRef(std::string input, std::multimap<std::string, std::string> varTable) {
	std::string type = Utility::getReferenceType(input);
	if (type == Utility::QUOTED_IDENT) {
		input = Utility::trim_double_quotes(input);
		return Ref(input, true);
	}
	else if (type == Utility::INTEGER) {
		input = Utility::trim_double_quotes(input);
		return Ref(input, false);
	}
	else if (syntaxChecker.validateAttrRef(input)) {
		std::size_t periodIndex = input.find_first_of(".");
		std::string synName = input.substr(0, periodIndex);
		std::string synType = varTable.find(synName)->second;
		std::string attrName = input.substr(periodIndex + 1);
		return Ref(AttrRef(synName, synType, attrName));
	}
	else {
		throw PQLSyntaxError("PQL syntax error: Invalid with clause, second arg format incorrect");
	}
}