#include <string>

#pragma once

class AttrRef {
private:
	std::string synName;
	std::string synType;
	std::string attrName;
public:
	AttrRef();
	AttrRef(std::string synName, std::string synType, std::string attrName);

	std::string getSynName();
	std::string getSynType();

	std::string getAttrName();
};