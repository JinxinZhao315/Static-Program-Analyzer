#include "QPS/include/tokenizer/QueryTokenizer.h"

QueryTokenizer::QueryTokenizer() {
    this->syntaxChecker = PQLSyntaxChecker();
}

std::pair<std::string, std::string> QueryTokenizer::tokenizeQuery(std::string input) {
	size_t lastSemicolon = input.find_last_of(Utility::segmentationChar);
	//no declaration, can be "Select BOOLEAN"
	if (lastSemicolon == std::string::npos) {
		return std::make_pair(Utility::empty, input);
	}
	else {
		std::string declaration = Utility::trim(input.substr(0, lastSemicolon + 1), Utility::whiteSpaces);
		std::string remainingQuery = Utility::trim(input.substr(lastSemicolon + 1), Utility::whiteSpaces);
		return std::make_pair(declaration, remainingQuery);
	}
}

std::multimap<std::string, std::string> QueryTokenizer::tokenizeDeclaration(std::string declaration) {
    size_t semicolonPos = declaration.find(Utility::segmentation);
    std::multimap<std::string, std::string> varTable;
    while (semicolonPos != std::string::npos) {
        size_t whiteSpacePos = declaration.find_first_of(Utility::whiteSpaces);
        std::string designEntity = declaration.substr(0, whiteSpacePos);

        bool isDeValid = syntaxChecker.validateDesignEntity(designEntity);

        if (!isDeValid) {
            throw PQLSyntaxError("PQL syntax error: invalid design entity in declaration");
        }
        std::string synonymStr = Utility::trim(declaration.substr(whiteSpacePos, semicolonPos - whiteSpacePos),
                                               Utility::whiteSpaces);
        std::vector<std::string> synonymVector = tokenizeCsv(synonymStr);

        for (std::string synon: synonymVector) {
            bool isSynonValid = syntaxChecker.validateSynonym(synon);
            if (!isSynonValid) {
                throw PQLSyntaxError("PQL syntax error: invalid synonym");
            }
            varTable.insert({synon, designEntity});
        }

        declaration = Utility::trim(declaration.substr((semicolonPos + 1)), Utility::whiteSpaces);
        semicolonPos = declaration.find(Utility::segmentation);
    }
	return varTable;
}

void QueryTokenizer::tokenizeClauses(std::string input,
                                     std::multimap<std::string, std::string> varTable,
									 SelectClause*& selectClause,
                                     std::vector<SuchThatClause*>& suchThatClauseVec,
                                     std::vector<PatternClause*>& patternClauseVec,
									 std::vector<WithClause*>& withClauseVec) {
	std::string keyword = extractKeyword(input);
	if (keyword != SELECT) {
		throw PQLSyntaxError("PQL syntax error: No 'select' keyword");
	}
	tokenizeSelectClause(input, varTable, selectClause);
	std::string prevClauseType;
	while (input.length() != 0) {
		keyword = extractKeyword(input);
		if (keyword == SUCH) {
            if (extractKeyword(input) != THAT) {
                throw PQLSyntaxError("PQL syntax error: No 'that' nextKey");
            }
			tokenizeSuchThatClause(input, suchThatClauseVec);
            prevClauseType = SUCH;
		}
		else if (keyword == PATTERN) {
			tokenizePatternClause(input, varTable, patternClauseVec);
            prevClauseType = PATTERN;
		} else if (keyword == WITH) {
			tokenizeWithClause(input, withClauseVec, varTable);
			prevClauseType = WITH;
		}
		else if (keyword == AND) {
            std::string nextKeyword = peekKeyword(input, Utility::whiteSpaces);

            if (nextKeyword == SUCH || nextKeyword == PATTERN || nextKeyword == WITH) {
                throw PQLSyntaxError("PQL syntax error: Invalid use of and");
            }

            if (prevClauseType == SUCH) {
                tokenizeSuchThatClause(input, suchThatClauseVec);
            } else if (prevClauseType == WITH) {
                tokenizeWithClause(input, withClauseVec, varTable);
            } else {
                nextKeyword = peekKeyword(input, Utility::leftRoundBracket);
				if (nextKeyword.empty()) {
					throw PQLSyntaxError("PQL syntax error: Invalid use of and after pattern keyword");
				}
				ReferenceType refType = Utility::getEnumReferenceType(nextKeyword);
				switch (refType)
				{
				case SYNONYM:
					break;
				default:
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

void QueryTokenizer::tokenizeWithClause(std::string& input, std::vector<WithClause*>& withClauseVec, std::multimap<std::string, std::string> varTable) {
	std::size_t equalSignIndex = input.find_first_of(Utility::equalSign);
	if (equalSignIndex == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid with clause, no \"=\" sign");
	}
	std::string firstArgStr = Utility::trim(input.substr(0, equalSignIndex), Utility::whiteSpaces);
	Ref firstArg = tokenizeRef(firstArgStr, varTable);
	input = Utility::trim(input.substr(equalSignIndex + 1), Utility::whiteSpaces);

	std::size_t secondArgEndIndex = input.find_first_of(Utility::whiteSpaces);
	std::string secondArgStr = Utility::empty;
	//this with clause is the last clause
	if (secondArgEndIndex == std::string::npos) {
		secondArgStr = input;
		input = Utility::empty;
	}
	else {
		secondArgStr = input.substr(0, secondArgEndIndex);
		input = Utility::trim(input.substr(secondArgEndIndex + 1), Utility::whiteSpaces);
	}
	Ref secondArg = tokenizeRef(secondArgStr, varTable);


	withClauseVec.push_back(new WithClause(firstArg, secondArg));
}

void QueryTokenizer::tokenizeSelectClause(std::string& input, std::multimap<std::string, std::string> varTable, 
	SelectClause*& selectClause) {
	std::size_t elemEndIndex = input.find_first_of(Utility::whiteSpaces);
	std::vector<std::string> elemStrList;
	//multi clause
	if (input.size() > 0 && input[0] == Utility::leftArrowBracketChar) {
		size_t rightAnglePos = input.find_first_of(Utility::rightArrowBracket);
		if (rightAnglePos == std::string::npos) {
			throw PQLSyntaxError("PQL syntax error: Invalid multi-element list format in select clause");
		}
		elemStrList = tokenizeCsv(input.substr(1, rightAnglePos - 1));
		input = Utility::trim(input.substr(rightAnglePos + 1), Utility::whiteSpaces);
	}
	//single clause, no whitespace on the left, so no other clauses except Select single element
	else if (elemEndIndex == std::string::npos) {
		elemStrList.push_back(input);
		input = Utility::empty;
	}
	//single clause, but other restriction after the select clause
	else {
		std::string elem = input.substr(0, elemEndIndex);
		elemStrList.push_back(elem);
		input = Utility::trim(input.substr(elemEndIndex + 1), Utility::whiteSpaces);
	}
	std::vector<Elem*> elemList;
	for (std::string elemStr : elemStrList) {
		if (syntaxChecker.validateAttrRef(elemStr)) {
			std::size_t periodIndex = elemStr.find_first_of(Utility::ending);
			std::string synName = elemStr.substr(0, periodIndex);
			std::string attrName = elemStr.substr(periodIndex + 1);
			std::string synType;
			if (varTable.find(synName) == varTable.end()) {
				synType = Utility::ending;
			}
			else {
				synType = varTable.find(synName)->second;
			}
			Elem* elem = new Elem(AttrRef(synName, synType, attrName));
			elemList.push_back(elem);
		}
		else if (syntaxChecker.validateSynonym(elemStr)) {
			Elem* elem = new Elem(elemStr);
			elemList.push_back(elem);
		}
		else {
			throw PQLSyntaxError("PQL syntax error: Invalid element format in Select Clause");
		}
	}
	
	selectClause = new SelectClause(elemList);
}

void QueryTokenizer::tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause*>& suchThatClauseVec) {
	std::size_t nextLeftPar = input.find_first_of(Utility::leftRoundBracket);
	std::size_t nextComma = input.find_first_of(Utility::coma);
	std::size_t nextRightPar = input.find_first_of(Utility::rightRoundBracket);

	if (nextLeftPar == std::string::npos || nextComma == std::string::npos || nextRightPar == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	if (nextRightPar <= nextComma + 1 || nextComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that clause syntax");
	}
	std::string relationship = Utility::trim(input.substr(0, nextLeftPar), Utility::whiteSpaces);
	std::string leftArg = Utility::trim(input.substr(nextLeftPar + 1, nextComma - nextLeftPar - 1), Utility::whiteSpaces);
	std::string rightArg = Utility::trim(input.substr(nextComma + 1, nextRightPar - nextComma - 1), Utility::whiteSpaces);
	if (!syntaxChecker.validateRelationship(relationship, leftArg, rightArg)) {
		throw PQLSyntaxError("PQL syntax error: Invalid such that relationship");
	}
	input = input.substr(nextRightPar + 1);
	suchThatClauseVec.push_back(new SuchThatClause(relationship, leftArg, rightArg));
}

void QueryTokenizer::tokenizePatternClause(std::string& input,
                                           std::multimap<std::string, std::string> varTable,
                                           std::vector<PatternClause*>& patternClauseVec) {
	std::size_t nextLeftPar = input.find_first_of(Utility::leftRoundBracket);
	std::size_t firstComma = input.find_first_of(Utility::coma);
    std::size_t secondComma = input.find_first_of(Utility::coma, firstComma + 1);

    if (nextLeftPar == std::string::npos || firstComma == std::string::npos) {
        throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
    }

    stack<char> stk;
    std::size_t nextRightPar = -1;
    for (size_t i = nextLeftPar; i < input.length(); i++ ) {
        if (input[i] == Utility::leftRoundBracketChar) {
            stk.push(Utility::leftRoundBracketChar);
        } else if (input[i] == Utility::rightRoundBracketChar) {
            stk.pop();
        }
        if (stk.empty()) {
            nextRightPar = i;
            break;
        }
    }

	if ( !stk.empty() || nextRightPar <= firstComma + 1 || firstComma <= nextLeftPar + 1) {
		throw PQLSyntaxError("PQL syntax error: Invalid pattern clause syntax");
	}
    std::string synonym = Utility::trim(input.substr(0, nextLeftPar), Utility::whiteSpaces);
    std::string synonymType = varTable.find(synonym)->second;

    std::string firstArg;
    std::string secondArg;
    std::string thirdArg = Utility::empty;

	DesignEntity enumDesignEntity = Utility::getDesignEntityFromString(synonymType);

    if (enumDesignEntity == IF_ENTITY) {
        // 3 arguments case
        if (secondComma == std::string::npos || secondComma > nextRightPar) {
            throw PQLSyntaxError("PQL syntax error: Only 1 comma in pattern clause if type");
        }
        firstArg = Utility::trim(input.substr(nextLeftPar + 1, firstComma - nextLeftPar - 1),
                                             Utility::whiteSpaces);
        secondArg = Utility::trim(input.substr(firstComma + 1, secondComma - firstComma - 1),
                                              Utility::whiteSpaces);
        thirdArg = Utility::trim(input.substr(secondComma + 1, nextRightPar - secondComma - 1),
                                              Utility::whiteSpaces);
    } else {
        // 2 arguments case
        if (! (enumDesignEntity == ASSIGN_ENTITY || enumDesignEntity == WHILE_ENTITY)) {
            throw PQLSemanticError("PQL Semantic error: pattern clause synonym type is not assign, while or if");
        }

        if (secondComma != std::string::npos && secondComma < nextRightPar) {
            throw PQLSyntaxError("PQL syntax error: Too many commas in pattern clause assign and while type");
        }

        firstArg = Utility::trim(input.substr(nextLeftPar + 1, firstComma - nextLeftPar - 1),
                                             Utility::whiteSpaces);
        secondArg = Utility::trim(input.substr(firstComma + 1, nextRightPar - firstComma - 1),
                                              Utility::whiteSpaces);
    }

    if (!syntaxChecker.validatePattern(synonym, synonymType, firstArg, secondArg, thirdArg)) {
        throw PQLSyntaxError("PQL syntax error: Invalid pattern clause if syntax");
    }
    input = input.substr(nextRightPar + 1);
    patternClauseVec.push_back(new PatternClause(synonym, firstArg, secondArg, thirdArg));
}

std::string QueryTokenizer::extractKeyword(std::string& input) {
	input = Utility::trim(input, Utility::whiteSpaces);
    std::size_t nextWhiteSpace = input.find_first_of(Utility::whiteSpaces);
	if (nextWhiteSpace == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid keyword");
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	input = Utility::trim(input.substr(nextWhiteSpace), Utility::whiteSpaces);
	return keyword;
}

std::string QueryTokenizer::peekKeyword(std::string input, std::string delimiter) {
    input = Utility::trim(input, Utility::whiteSpaces);
    std::size_t nextDelimiter = input.find_first_of(delimiter);
    if (nextDelimiter == std::string::npos) {
        return Utility::empty;
    }
    std::string keyword = Utility::trim(input.substr(0, nextDelimiter), Utility::whiteSpaces);
    return keyword;
}

std::vector<std::string> QueryTokenizer::tokenizeCsv(std::string csv) {
    std::vector<std::string> ret;
    std::string remainder = csv;
	size_t commaIndex = remainder.find(Utility::coma);
    while (commaIndex != std::string::npos) {
        std::string str = Utility::trim(remainder.substr(0, commaIndex), Utility::whiteSpaces);
        ret.push_back(str);
        remainder = Utility::trim(remainder.substr((commaIndex + 1)), Utility::whiteSpaces);
        commaIndex = remainder.find(Utility::coma);
    }

    if (remainder.empty()) {
        throw PQLSyntaxError("PQL syntax error: comma list is empty or end with comma");
    }
    ret.push_back(remainder);
    return ret;
}

Ref QueryTokenizer::tokenizeRef(std::string input, std::multimap<std::string, std::string> varTable) {
	ReferenceType type = Utility::getEnumReferenceType(input);
	bool isIdent;
	switch (type)
	{
	case INTEGER:
		input = Utility::trim_double_quotes(input);
		isIdent = false;
		return Ref(input, isIdent);
	case QUOTED_IDENT:
		input = Utility::trim_double_quotes(input);
		isIdent = true;
		return Ref(input, isIdent);
	default:
		break;
	}

	if (syntaxChecker.validateAttrRef(input)) {
		std::size_t periodIndex = input.find_first_of(Utility::ending);
		std::string synName = input.substr(0, periodIndex);
		std::string synType = varTable.find(synName)->second;
		std::string attrName = input.substr(periodIndex + 1);
		return Ref(AttrRef(synName, synType, attrName));
	}
	else {
		throw PQLSyntaxError("PQL syntax error: Invalid with clause, second arg format incorrect");
	}
}