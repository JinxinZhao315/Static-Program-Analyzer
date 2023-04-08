#include "../../include/evaluator/WithHandler.h"

WithHandler::WithHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result WithHandler::evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
	int& synEvalPosition, std::vector<std::string>evalSynList) {
	Result result;
	std::vector<std::string> synList = resultTable.getSynList();
	if (withClause.isFirstArgAttrRef() && !withClause.isSecondArgAttrRef()) {
		std::string secondConstValue = withClause.getSecondArgConstValue();
		std::string firstSynName = withClause.getFirstArgAttrRef().getSynName();
		std::string firstSynType = withClause.getFirstArgAttrRef().getSynType();
		resultTable.resultTableCheckAndAdd(firstSynName, pkb, firstSynType);
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), firstSynName);
		int firstSynIndex = it - synList.begin();
		int tupleNum = resultTable.getTupleNum();
		ResultTable tempTable(resultTable.getSynList());
		for (int tupleIndex = 0; tupleIndex < tupleNum; tupleIndex++) {
			std::vector<std::string> tuple = resultTable.getTuple(tupleIndex);
			std::string firstAttrRefValue = Utility::getAttrRefValue(tuple[firstSynIndex], withClause.getFirstArgAttrRef(), pkb);
			if (firstAttrRefValue == secondConstValue) {
				tempTable.insertTuple({ tuple });
			}
		}
		
		if (tempTable.isTableEmpty()) {
			result.setResultTrue(false);
			return result;
		}
		removeUselessSyns({firstSynName}, resultTable, evalSynList, synEvalPosition);
		resultTable = tempTable;
		
	}
	else if (withClause.isFirstArgAttrRef() && withClause.isSecondArgAttrRef()){
		std::string firstSynName = withClause.getFirstArgAttrRef().getSynName();
		std::string firstSynType = withClause.getFirstArgAttrRef().getSynType();
		std::string secondSynName = withClause.getSecondArgAttrRef().getSynName();
		std::string secondSynType = withClause.getSecondArgAttrRef().getSynType();
		resultTable.resultTableCheckAndAdd(firstSynName, pkb, firstSynType);
		resultTable.resultTableCheckAndAdd(secondSynName, pkb, secondSynType);
		std::vector<std::string>::iterator firstIt = std::find(synList.begin(), synList.end(), firstSynName);
		std::vector<std::string>::iterator secondIt = std::find(synList.begin(), synList.end(), secondSynName);
		int firstSynIndex = firstIt - synList.begin();
		int secondSynIndex = secondIt - synList.begin();
		ResultTable tempTable(resultTable.getSynList());
		for (int tupleIndex = 0; tupleIndex < resultTable.getTupleNum(); tupleIndex++) {
			std::vector<std::string> tuple = resultTable.getTuple(tupleIndex);
			std::string firstAttrRefValue = Utility::getAttrRefValue(tuple[firstSynIndex], withClause.getFirstArgAttrRef(), pkb);
			std::string secondAttrRefValue = Utility::getAttrRefValue(tuple[secondSynIndex], withClause.getSecondArgAttrRef(), pkb);
			if (firstAttrRefValue == secondAttrRefValue) {
				tempTable.insertTuple(tuple);
			}
		}

		if (tempTable.isTableEmpty()) {
			result.setResultTrue(false);
			return result;
		}
		removeUselessSyns({ firstSynName, secondSynName }, resultTable, evalSynList, synEvalPosition);
		resultTable = tempTable;
	}
	else {
		throw PQLSemanticError("The left arg of with clause should not be const value!");
	}
	return result;
}