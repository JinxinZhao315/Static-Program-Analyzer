#include "../../include/model/Ref.h"

#pragma once

Ref::Ref() {}
Ref::Ref(std::string input, bool isIdent) {
	if (isIdent) {
		this->identValue = input;
		this->isIdent = true;
	}
	else {
		this->integerValue = input;
		this->isInteger = true;
	}
}
Ref::Ref(AttrRef input) {
	this->isAttrRef = true;
	this->attrRef = input;
}


//getter
std::string Ref::getIdentValue() {
	return this->identValue;
}

std::string Ref::getIntegerValue() {
	return this->integerValue;
}

AttrRef Ref::getAttrRef() {
	return this->attrRef;
}


//check Ref type
bool Ref::isRefIdent() {
	return this->isIdent;
}

bool Ref::isRefInteger() {
	return this->isInteger;
}

bool Ref::isRefAttrRef() {
	return this->isAttrRef;  
}



