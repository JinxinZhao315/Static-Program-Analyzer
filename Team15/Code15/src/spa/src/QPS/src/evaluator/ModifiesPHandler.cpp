#include "QPS/include/evaluator/ModifiesPHandler.h"


ModifiesPHandler::ModifiesPHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result ModifiesPHandler::evalModifiesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	std::string leftType = Utility::getReferenceType(leftArg);
	std::string rightType = Utility::getReferenceType(rightArg);
	Result result;

	// Find everything defined in source modified by a procedure defined in source.
	if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
		//input procedure name, return all vars modified in procedure.
		std::set<std::string> usesSet = pkb.getModifiesVarsFromProc(leftArg);
		if (usesSet.empty()) {
			result.setResultTrue(false);
			return result;
		}
	}
	// Find ident string in source program which is modified by a procedure defined in source.
	else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
		// identString of format \"x\"
		bool isModifies = pkb.areInModifiesProcRelationship(leftArg, Utility::trim_double_quotes(rightArg));
		if (!isModifies) {
			result.setResultTrue(false);
			return result;
		}
	}
	//Find variable v defined in QPS which is modified by given procedure defined in source. 
	else if (leftType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
		std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given procedure modifies historical variables in source.
			bool isModifies = pkb.areInModifiesProcRelationship(leftArg, currSynonVal);
			if (isModifies) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(false, true, ResultTable(resultSynonValues, rightArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure has some modifies to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {

			std::set<std::string> modifiesSet = pkb.getModifiesVarsFromProc(currSynonVal);

			if (!modifiesSet.empty()) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(true, false, ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure modifies given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are procedure names in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given procedure uses historical variables in source.
			bool isModifies = pkb.areInModifiesProcRelationship(currSynonVal, Utility::trim_double_quotes(rightArg));
			if (isModifies) {
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
	// defined in source such that p modifies v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
		resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
		/*set<string> currLeftValues = resultTable.getStringSetFromKey(leftArg);
		set<string> currRightValues = resultTable.getStringSetFromKey(rightArg);*/
		std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);


		ResultTable tempResultTable({ leftArg, rightArg });
		for (int i = 0; i < currLeftValues.size(); i++) {
			bool isLeftModifiesRight = pkb.areInModifiesProcRelationship(currLeftValues[i], currRightValues[i]);
			if (isLeftModifiesRight) {
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
