#include"Utility.h"

std::string Utility::extractKeyword(std::string input) {
	std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid keyword");
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	return keyword;
}

std::string Utility::trim(std::string input) {
	std::size_t firstCharIndex = input.find_first_not_of(" \t\n");
	std::size_t lastCharIndex = input.find_last_not_of(" \t\n");
	if (firstCharIndex == std::string::npos) {
		return "";
	}
	else {
		return input.substr(firstCharIndex, lastCharIndex - firstCharIndex + 1);
	}
}

std::string Utility::getPrimitiveType(std::string input) {
	if (std::regex_match(input, std::regex(synonymFormat))) {
		return "synonym";
	}
	else if (std::regex_match(input, std::regex(integerFormat))) {
		return "integer";
	}
	else if (std::regex_match(input, std::regex(quotedIdentFormat))) {
		return "quotedIdent";
	}
	else if (std::regex_match(input, std::regex(underscoredExpr))) {
		return "underscoredExpr";
	}
	else if (std::regex_match(input, std::regex(expr))) {
		return "expr";
	}
	else if (std::regex_match(input, std::regex(underscore))) {
		return "underscore";
	}
	else {
		return "Invalid";
	}
}