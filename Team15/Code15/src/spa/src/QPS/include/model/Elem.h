#include "AttrRef.h"
#pragma once

class Elem {
private:
	std::string synName;
	AttrRef attrRef;
	bool isSynonym;
public:
	Elem();
	Elem(std::string synName);
	Elem(AttrRef attrRef);
	bool isElemSynonym();

	std::string getSynName();

	std::string getAttrName();

	std::string getAttrSynType();

	AttrRef getAttrRef();
};