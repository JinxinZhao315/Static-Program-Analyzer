#include "../../include/evaluator/WithHandler.h"

WithHandler::WithHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result WithHandler::evalWith(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	Result result;
	std::vector<std::string> synList = resultTable.getSynList();
	if (!withClause.getFirstArg().isRefAttrRef() && !withClause.getSecondArg().isRefAttrRef()) {
		if (withClause.getFirstArg().getValue() != withClause.getSecondArg().getValue()) {
			result.setResultTrue(false);
			return result;
		}
	}
	else if (!withClause.getFirstArg().isRefAttrRef() && withClause.getSecondArg().isRefAttrRef()) {
		//obtain value from with clause
		std::string leftValue = withClause.getFirstArg().getValue();
		std::string rightSynName = withClause.getSecondArg().getAttrRef().getSynName();
		std::string rightSynType = withClause.getSecondArg().getAttrRef().getSynType();
		//add syn to resultTable if not added
		resultTableCheckAndAdd(rightSynName, resultTable, rightSynType);
		//find the index of this syn in resultTable
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), rightSynName);
		int rightSynIndex = it - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ rightSynName });
		//tempResultTable only takes in the syn value that fulfill the requirement
		for (int col = 0; col < tupleNum; col++) {
			std::string rightValue = resultTable.getAttrRefValue(rightSynIndex, col, withClause.getSecondArg().getAttrRef(), pkb);
			if (leftValue == rightValue) {
				tempResultTable.insertTuple({ rightValue });
			}
		}
		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	else if (withClause.getFirstArg().isRefAttrRef() && !withClause.getSecondArg().isRefAttrRef()) {
		std::string rightValue = withClause.getSecondArg().getValue();
		std::string leftSynName = withClause.getFirstArg().getAttrRef().getSynName();
		std::string leftSynType = withClause.getFirstArg().getAttrRef().getSynType();
		resultTableCheckAndAdd(leftSynName, resultTable, leftSynType);
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), leftSynName);
		int leftSynIndex = it - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ leftSynName });
		for (int col = 0; col < tupleNum; col++) {
			std::string leftValue = resultTable.getAttrRefValue(leftSynIndex, col, withClause.getFirstArg().getAttrRef(), pkb);
			if (leftValue == rightValue) {
				tempResultTable.insertTuple({ leftValue });
			}
		}
		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	else {
		std::string leftSynName = withClause.getFirstArg().getAttrRef().getSynName();
		std::string leftSynType = withClause.getFirstArg().getAttrRef().getSynType();
		std::string rightSynName = withClause.getSecondArg().getAttrRef().getSynName();
		std::string rightSynType = withClause.getSecondArg().getAttrRef().getSynType();
		resultTableCheckAndAdd(leftSynName, resultTable, leftSynType);
		resultTableCheckAndAdd(rightSynName, resultTable, rightSynType);
		std::vector<std::string>::iterator leftIt = std::find(synList.begin(), synList.end(), leftSynName);
		std::vector<std::string>::iterator rightIt = std::find(synList.begin(), synList.end(), rightSynName);
		int leftSynIndex = leftIt - synList.begin();
		int rightSynIndex = rightIt - synList.begin();
		int tupleNum = resultTable.getColNum();
		ResultTable tempResultTable({ leftSynName, rightSynName });
		for (int col = 0; col < tupleNum; col++) {
			std::string leftValue = resultTable.getAttrRefValue(leftSynIndex, col, withClause.getFirstArg().getAttrRef(), pkb);
			std::string rightValue = resultTable.getAttrRefValue(rightSynIndex, col, withClause.getSecondArg().getAttrRef(), pkb);
			if (leftValue == rightValue) {
				tempResultTable.insertTuple({ leftValue, rightValue });
			}
		}

		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
		}
		result.setClauseResult(tempResultTable);
	}
	return result;
}