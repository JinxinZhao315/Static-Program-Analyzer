#include <string>
#include "AttrRef.h"

#pragma once

class Ref {
private:
	std::string identValue;
	std::string integerValue;
	AttrRef attrRef;
	bool isIdent = false;
	bool isInteger = false;
	bool isAttrRef = false;
public:
	Ref();
	Ref(std::string value, bool isIdent);
	Ref(AttrRef attrRef);

	std::string getIdentValue();
	std::string getIntegerValue();
	AttrRef getAttrRef();

	bool isRefAttrRef();
	bool isRefIdent();
	bool isRefInteger();
};