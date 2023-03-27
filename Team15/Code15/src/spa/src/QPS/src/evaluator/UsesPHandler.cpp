#include "QPS/include/evaluator/UsesPHandler.h"


UsesPHandler::UsesPHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result UsesPHandler::evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
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
		/*resultTable.resultTableCheckAndAdd(rightArg, pkb,  synonDeType);
		std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);*/
		std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		std::vector<std::string> resultSynonValues;

		for (const auto& currSynonVal : currSynonValues) {
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
		result.setClauseResult(ResultTable(resultSynonValues, rightArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure has some uses to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		//resultTable.resultTableCheckAndAdd(leftArg, pkb,  synonDeType);
		// currSynonValues here are procedures in string format.
		//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		std::vector<std::string> resultSynonValues;

		for (const auto& currSynonVal : currSynonValues) {

			std::set<std::string> usesSet = pkb.getUsesVarsFromProc(currSynonVal);

			if (!usesSet.empty()) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure uses given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		//resultTable.resultTableCheckAndAdd(leftArg, pkb,  synonDeType);
		// currSynonValues here are procedures in string format.
		//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		std::vector<std::string> resultSynonValues;

		for (const auto& currSynonVal : currSynonValues) {
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
		result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, right type is a varible defined in QPS, find all pairs of procedure p defined in source and varible v 
	// defined in source such that p uses v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		/*resultTable.resultTableCheckAndAdd(leftArg, pkb,  leftDeType);
		resultTable.resultTableCheckAndAdd(rightArg, pkb,  rightDeType);
		std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);*/
		std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
		std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
		//convert the set to vector
		std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
		std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

		ResultTable initTable(currLeftValues, leftArg);
		initTable.combineTable(ResultTable(currRightValues, rightArg));
		int initTableSize = initTable.getColNum();

		ResultTable tempTable({ leftArg, rightArg });
		for (int i = 0; i < initTableSize; i++) {
			std::vector<std::string> tuple = initTable.getTuple(i);
			bool isRightUsesLeft = pkb.areInUsesProcRelationship(tuple[0], tuple[1]);
			if (isRightUsesLeft) {
				tempTable.insertTuple({ tuple[0], tuple[1] });
			}
		}

		if (tempTable.isTableEmpty()) {
			result.setResultTrue(false);
			return result;
		}

		result.setClauseResult(tempTable);
	}
	//Do we need to throw exception if type doesn't match? As all semantics are checked already.
	return result;
}