#include "../../include/evaluator/WithHandler.h"

WithHandler::WithHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result WithHandler::evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	Result result;
	std::vector<std::string> synList = resultTable.getSynList();
	if (!withClause.isFirstArgAttrRef() && !withClause.isSecondArgAttrRef()) {
		if (withClause.getFirstArgConstValue() != withClause.getSecondArgConstValue()) {
			result.setResultTrue(false);
			return result;
		}
	}
	else if (!withClause.isFirstArgAttrRef() && withClause.isSecondArgAttrRef()) {
		//obtain value from with clause
		std::string firstValue = withClause.getFirstArgConstValue();
		std::string secondSynName = withClause.getSecondArgAttrRef().getSynName();
		std::string secondSynType = withClause.getSecondArgAttrRef().getSynType();
		//add syn to resultTable if not added
		resultTableCheckAndAdd(secondSynName, resultTable, secondSynType);
		//find the index of this syn in resultTable
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), secondSynName);
		int secondSynIndex = it - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ secondSynName });
		//tempResultTable only takes in the syn value that fulfill the requirement
		for (int col = 0; col < tupleNum; col++) {
			std::string secondValue = resultTable.getAttrRefValue(secondSynIndex, col, withClause.getSecondArgAttrRef(), pkb);
			if (firstValue == secondValue) {
				tempResultTable.insertTuple({ secondValue });
			}
		}
		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	else if (withClause.isFirstArgAttrRef() && !withClause.isSecondArgAttrRef()) {
		std::string secondValue = withClause.getSecondArgConstValue();
		std::string firstSynName = withClause.getFirstArgAttrRef().getSynName();
		std::string firstSynType = withClause.getFirstArgAttrRef().getSynType();
		resultTableCheckAndAdd(firstSynName, resultTable, firstSynType);
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), firstSynName);
		int firstSynIndex = it - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ firstSynName });
		for (int col = 0; col < tupleNum; col++) {
			std::string firstValue = resultTable.getAttrRefValue(firstSynIndex, col, withClause.getFirstArgAttrRef(), pkb);
			if (firstValue == secondValue) {
				tempResultTable.insertTuple({ firstValue });
			}
		}
		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	else {
		std::string firstSynName = withClause.getFirstArgAttrRef().getSynName();
		std::string firstSynType = withClause.getFirstArgAttrRef().getSynType();
		std::string secondSynName = withClause.getSecondArgAttrRef().getSynName();
		std::string secondSynType = withClause.getSecondArgAttrRef().getSynType();
		resultTableCheckAndAdd(firstSynName, resultTable, firstSynType);
		resultTableCheckAndAdd(secondSynName, resultTable, secondSynType);
		std::vector<std::string>::iterator firstIt = std::find(synList.begin(), synList.end(), firstSynName);
		std::vector<std::string>::iterator secondIt = std::find(synList.begin(), synList.end(), secondSynName);
		int firstSynIndex = firstIt - synList.begin();
		int secondSynIndex = secondIt - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ firstSynName, secondSynName });
		for (int col = 0; col < tupleNum; col++) {
			std::string firstValue = resultTable.getAttrRefValue(firstSynIndex, col, withClause.getFirstArgAttrRef(), pkb);
			std::string secondValue = resultTable.getAttrRefValue(secondSynIndex, col, withClause.getSecondArgAttrRef(), pkb);
			if (firstValue == secondValue) {
				tempResultTable.insertTuple({ firstValue, secondValue });
			}
		}

		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	return result;
}