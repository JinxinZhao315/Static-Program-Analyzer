#include"utility.h"

std::string extractKeyword(std::string input) {
	std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
	if (nextWhiteSpace == std::string::npos) {
		throw PQLSyntaxError("PQL syntax error: Invalid keyword");
	}
	std::string keyword = input.substr(0, nextWhiteSpace);
	return keyword;
}

std::string trim(std::string input) {
	std::size_t firstCharIndex = input.find_first_not_of(" \t\n");
	std::size_t lastCharIndex = input.find_last_not_of(" \t\n");
	if (firstCharIndex == std::string::npos) {
		return "";
	}
	else {
		return input.substr(firstCharIndex, lastCharIndex - firstCharIndex + 1);
	}
}