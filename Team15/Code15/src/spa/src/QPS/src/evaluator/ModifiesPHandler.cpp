#include "QPS/include/evaluator/ModifiesPHandler.h"


ModifiesPHandler::ModifiesPHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result ModifiesPHandler::evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	std::string leftType = Utility::getReferenceType(leftArg);
	std::string rightType = Utility::getReferenceType(rightArg);
	Result result;

	// Find everything defined in source modified by a procedure defined in source.
	if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
		//input procedure name, return all vars modified in procedure.
		std::set<std::string> usesSet = pkb.getModifiesVarsFromProc(Utility::trim_double_quotes(leftArg));
		if (usesSet.empty()) {
			result.setResultTrue(false);
			return result;
		}
	}
	// Find ident string in source program which is modified by a procedure defined in source.
	else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
		// identString of format \"x\"
		bool isModifies = pkb.areInModifiesProcRelationship(Utility::trim_double_quotes(leftArg), Utility::trim_double_quotes(rightArg));
		if (!isModifies) {
			result.setResultTrue(false);
			return result;
		}
	}
	//Find variable v defined in QPS which is modified by given procedure defined in source. 
	else if (leftType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(rightArg)->second;
		/*resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
		std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);*/
		std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		std::vector<std::string> resultSynonValues;

		for (std::string currSynonVal : currSynonValues) {
			// check whether given procedure modifies historical variables in source.
			bool isModifies = pkb.areInModifiesProcRelationship(Utility::trim_double_quotes(leftArg), currSynonVal);
			if (isModifies) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(ResultTable(resultSynonValues, rightArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure has some modifies to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		/*resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);*/
		std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (std::string currSynonVal : currSynonValues) {

			std::set<std::string> modifiesSet = pkb.getModifiesVarsFromProc(currSynonVal);

			if (!modifiesSet.empty()) {
				resultSynonValues.push_back(currSynonVal);
			}
		}

		if (resultSynonValues.empty()) {
			result.setResultTrue(false);
			return result;
		}
		result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, find whether given procedure modifies given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		//resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
		// currSynonValues here are procedure names in string format.
		//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
		std::vector<std::string> resultSynonValues;

		for (std::string currSynonVal : currSynonValues) {
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
		result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	}
	//Left type is a procedure defined in QPS, right type is a varible defined in QPS, find all pairs of procedure p defined in source and varible v 
	// defined in source such that p modifies v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		//resultTable.resultTableCheckAndAdd(leftArg, pkb, leftDeType);
		//resultTable.resultTableCheckAndAdd(rightArg, pkb, rightDeType);
		/*set<string> currLeftValues = resultTable.getStringSetFromKey(leftArg);
		set<string> currRightValues = resultTable.getStringSetFromKey(rightArg);*/
		std::set<string> leftSynValuesStrSet = Utility::getFullSetFromPkb(pkb, leftDeType);
		std::set<string> rightSynValuesStrSet = Utility::getFullSetFromPkb(pkb, rightDeType);
		//convert the set to vector
		std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
		std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

		ResultTable initTable(currLeftValues, leftArg);
		initTable.combineTable(ResultTable(currRightValues, rightArg));
		int initTableSize = initTable.getColNum();

		ResultTable tempTable({ leftArg, rightArg });
		for (int i = 0; i < initTableSize; i++) {
			std::vector<std::string> tuple = initTable.getTuple(i);
			bool isLeftModifiesRight = pkb.areInModifiesProcRelationship(tuple[0], tuple[1]);
			if (isLeftModifiesRight) {
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
