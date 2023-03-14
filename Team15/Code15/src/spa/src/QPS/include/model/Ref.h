#include <string>
#include "AttrRef.h"

#pragma once

class Ref {
private:
	std::string value;
	//std::string integer;
	AttrRef attrRef;
	//bool isIdent = false;
	//bool isInteger = false;
	//bool isValue = false;
	bool isAttrRef = false;
public:
	Ref();
	Ref(std::string input);
	Ref(AttrRef attrRef);
	std::string getValue();
	AttrRef getAttrRef();
	bool isRefAttrRef();
};