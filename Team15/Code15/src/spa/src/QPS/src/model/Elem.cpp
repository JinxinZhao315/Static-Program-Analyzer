#include "../../include/model/Elem.h"

Elem::Elem() {

}

Elem::Elem(std::string synName) {
	this->isSynonym = true;
	this->synName = synName;
}

Elem::Elem(AttrRef attrRef) {
	this->isSynonym = false;
	this->attrRef = attrRef;
}

bool Elem::isElemSynonym() {
	return this->isSynonym;
}

std::string Elem::getSynName() {
	if (this->isSynonym) {
		return synName;
	}
	else {
		return attrRef.getSynName();
	}
}

std::string Elem::getAttrName() {
	if (this->isSynonym) {
		return "";
	}
	else {
		return attrRef.getAttrName();
	}
}

std::string Elem::getAttrSynType() {
	return this->attrRef.getSynType();
}

AttrRef Elem::getAttrRef() {
	return this->attrRef;
}