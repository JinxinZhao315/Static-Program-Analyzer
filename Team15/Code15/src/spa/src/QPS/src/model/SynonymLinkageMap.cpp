#include "../../include/model/SynonymLinkageMap.h"

SynonymLinkageMap::SynonymLinkageMap() {}

bool SynonymLinkageMap::isEmpty() {
	return linkageMap.size() == 0;
}

bool SynonymLinkageMap::isEmptyLinkageSet(std::string synonymName) {
	return linkageMap.find(synonymName) == linkageMap.end() || linkageMap.find(synonymName)->second.size() == 0;
}

void SynonymLinkageMap::insertLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance) {
	if (linkageMap.find(linkedSynonymName) == linkageMap.end()) {
		std::set<std::string> linkedSynonymInstanceSet;
		linkedSynonymInstanceSet.insert(linkedSynonymInstance);
		linkageMap.insert(std::make_pair<>(linkedSynonymName, linkedSynonymInstanceSet));
	}
	else {
		linkageMap.find(linkedSynonymName)->second.insert(linkedSynonymInstance);
	}
}

void SynonymLinkageMap::deleteLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance) {
	if (linkageMap.find(linkedSynonymName) != linkageMap.end()) {
		linkageMap.find(linkedSynonymName)->second.erase(linkedSynonymInstance);
	}
}

std::unordered_map<std::string, std::set<std::string>> SynonymLinkageMap::getLinkageMap() {
	return this->linkageMap;
}

