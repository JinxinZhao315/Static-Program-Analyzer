#include "../../include/model/AttrRef.h"

AttrRef::AttrRef() {

}

AttrRef::AttrRef(std::string synName, std::string synType, std::string attrName) {
	this->synName = synName;
	this->synType = synType;
	this->attrName = attrName;
}

std::string AttrRef::getSynName() {
	return this->synName;
}

std::string AttrRef::getSynType() {
	return this->synType;
}

std::string AttrRef::getAttrName() {
	return this->attrName;
}