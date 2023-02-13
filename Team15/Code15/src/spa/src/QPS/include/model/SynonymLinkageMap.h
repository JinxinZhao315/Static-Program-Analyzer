#pragma once
#include <unordered_map>
#include <string>
#include <set>

class SynonymLinkageMap {
private:
	
public:
	std::unordered_map<std::string, std::set<std::string>> linkageMap;
	SynonymLinkageMap();
	/*SynonymLinkageMap(std::string key,
		std::unordered_map<std::string, std::set<std::string>> linkageMap);*/
	bool isEmpty();
	void insertLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance);
	void deleteLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance);
	std::unordered_map <std::string, std::set<std::string>> getLinkageMap();
	bool isEmptyLinkageSet(std::string synonymName);
};