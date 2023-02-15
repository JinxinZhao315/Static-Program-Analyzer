#pragma once
#include <unordered_map>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include "Utility.h"

class SynonymLinkageMap {
private:
	std::unordered_map<std::string, std::set<std::string>> linkageMap;
public:
	SynonymLinkageMap();
	SynonymLinkageMap(std::unordered_map<std::string, std::set<std::string>> linkageMap);
	/*SynonymLinkageMap(std::string key,
		std::unordered_map<std::string, std::set<std::string>> linkageMap);*/
	bool isEmpty();
	bool isEmptyLinkageSet(std::string linkedSynonymName);
	bool containsKey(std::string linkedSynonymName);
	void SynonymLinkageMap::insertLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance);
	void SynonymLinkageMap::deleteLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance);
	std::unordered_map <std::string, std::set<std::string>>& getLinkageMap();
};