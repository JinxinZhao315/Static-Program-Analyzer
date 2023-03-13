#include "../../include/model/Ref.h"

#pragma once

Ref::Ref() {}
Ref::Ref(std::string input) {
	this->value = input;
	this->isAttrRef = false;
}

Ref::Ref(AttrRef input) {
	this->isAttrRef = true;
	this->attrRef = input;
}

//std::string Ref::getIdent() {
//	return this->ident;
//}
//
//std::string Ref::getInteger() {
//	return this->integer;
//}

std::string Ref::getValue() {
	return this->value;
}

AttrRef Ref::getAttrRef() {
	return this->attrRef;
}

AttrRef Ref::isRefAttrRef() {
	return this->isAttrRef();  
}