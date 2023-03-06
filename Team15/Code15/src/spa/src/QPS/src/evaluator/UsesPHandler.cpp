#include "QPS/include/evaluator/UsesPHandler.h"


UsesPHandler::UsesPHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result UsesPHandler::evalUsesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	std::string leftType = Utility::getReferenceType(leftArg);
	std::string rightType = Utility::getReferenceType(rightArg);
	Result result;

	// Find everything defined in source used by a procedure defined in source.
	if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
		//input statement line number, return all vars modified in statement line.
		//std::set<std::string> usesSet = pkb.getUsesVarsFromStmt(stoi(leftArg));
		std::set<std::string> usesSet = pkb.getUsesVarsFromProc(Utility::trim_double_quotes(leftArg));
		if (usesSet.empty()) {
			result.setResultTrue(false);
			return result;
		}
	}
	// Find ident string in source program which is used by a procedure defined in source.
	else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
		// identString of format \"x\"
		bool isUses = pkb.areInUsesProcRelationship(Utility::trim_double_quotes(leftArg), Utility::trim_double_quotes(rightArg));
		if (!isUses) {
			result.setResultTrue(false);
			return result;
		}
	}
	//Find variable v defined in QPS which is used by given procedure defined in source. 
	else if (leftType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
		std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given procedure uses historical variables in source.
			bool isUses = pkb.areInUsesProcRelationship(Utility::trim_double_quotes(leftArg), currSynonVal);
			if (isUses) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(false, true, ResultTable(resultSynonValues, rightArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure has some uses to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are procedures in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {

			std::set<std::string> usesSet = pkb.getUsesVarsFromProc(currSynonVal);

			if (!usesSet.empty()) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(true, false, ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure uses given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are procedures in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given procedures uses historical variables in source.
			bool isUses = pkb.areInUsesProcRelationship(currSynonVal, Utility::trim_double_quotes(rightArg));
			if (isUses) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(true, false, ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, right type is a varible defined in QPS, find all pairs of procedure p defined in source and varible v 
	// defined in source such that p uses v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
		resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
		std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);


		ResultTable tempResultTable({ leftArg, rightArg });
		for (int i = 0; i < currLeftValues.size(); i++) {
			bool isRightUsesLeft = pkb.areInUsesProcRelationship(currLeftValues[i], currRightValues[i]);
			if (isRightUsesLeft) {
				tempResultTable.insertTuple({ currLeftValues[i], currRightValues[i] });
			}
		}

		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
			return result;
		}

		result.setClauseResult(true, true, tempResultTable);
	}
	//Do we need to throw exception if type doesn't match? As all semantics are checked already.
	return result;
}