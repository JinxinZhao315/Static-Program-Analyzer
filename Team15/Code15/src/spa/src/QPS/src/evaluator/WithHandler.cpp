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
	else if (!withClause.getFirstArg().isRefAttrRef() && withClause.getFirstArg().isRefAttrRef()) {
		std::string leftValue = withClause.getFirstArg().getValue();
		std::string rightSynName = withClause.getSecondArg().getAttrRef().getSynName();
		std::string rightSynType = withClause.getSecondArg().getAttrRef().getSynType();
		resultTableCheckAndAdd(rightSynName, resultTable, rightSynType);
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), rightSynName);
		int rightSynIndex = it - synList.begin();

		for (int col = 0; col < resultTable.getColNum(); col++) {
			std::string rightValue = resultTable.getAttrRefValue(rightSynIndex, col, withClause.getSecondArg().getAttrRef(), pkb);
			if (leftValue != rightValue) {
				resultTable.deleteTuple(col);
			}
		}
	}
	else if (withClause.getFirstArg().isRefAttrRef() && !withClause.getFirstArg().isRefAttrRef()) {
		std::string rightValue = withClause.getSecondArg().getValue();
		std::string leftSynName = withClause.getFirstArg().getAttrRef().getSynName();
		std::string leftSynType = withClause.getFirstArg().getAttrRef().getSynType();
		resultTableCheckAndAdd(leftSynName, resultTable, leftSynType);
		std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), leftSynName);
		int leftSynIndex = it - synList.begin();

		for (int col = 0; col < resultTable.getColNum(); col++) {
			std::string leftValue = resultTable.getAttrRefValue(leftSynIndex, col, withClause.getFirstArg().getAttrRef(), pkb);
			if (leftValue != rightValue) {
				resultTable.deleteTuple(col);
			}
		}
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
		for (int col = 0; col < resultTable.getColNum(); col++) {
			std::string leftValue = resultTable.getAttrRefValue(leftSynIndex, col, withClause.getFirstArg().getAttrRef(), pkb);
			std::string rightValue = resultTable.getAttrRefValue(rightSynIndex, col, withClause.getSecondArg().getAttrRef(), pkb);
			if (leftValue != rightValue) {
				resultTable.deleteTuple(col);
			}
		}
	}
	return result;
}