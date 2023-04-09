#include"qps/include/model/Clause.h"
#include"qps/include/model/SuchThatClause.h"
#include "qps/include/model/Query.h"
#include<queue>
#include <vector>
#include <unordered_map>
#include <set>
#pragma once

class QueryEvalSeqOptimizer {
public:
	QueryEvalSeqOptimizer();
	void optimizeEvalSeq(Query& query);
private:
	std::unordered_map<int, std::set<int>> constructGraph(std::vector<Clause*> clauseList);
	std::vector<std::vector<int>> seperateEvalGroup(std::vector<Clause*> clauseList,
		std::unordered_map<int, std::set<int>> clauseToClauseMap, std::vector<std::string> selectedSynName);
	std::vector<int> generateOrderedEvalGroup(std::vector<Clause*> clauseList, std::vector<int> evalGroup,
		std::unordered_map<int, std::set<int>> clauseToClauseMap);
	PriorityLevel getPriority(Clause* clause);
};