#include "QPS/include/evaluator/ModifiesSHandler.h"


ModifiesSHandler::ModifiesSHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result ModifiesSHandler::evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	//std::string leftType = Utility::getReferenceType(leftArg);
	//std::string rightType = Utility::getReferenceType(rightArg);
	Result result;
	ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
	ReferenceType rightType = Utility::getEnumReferenceType(rightArg);
	switch (leftType)
	{
	case INTEGER:
		switch (rightType)
		{
			// Find ident string in source program which is modified by a statement line defined in source.
		case QUOTED_IDENT: {
			// identString of format \"x\"
			bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), Utility::trim_double_quotes(rightArg));
			if (!isModifies) {
				result.setResultTrue(false);
				return result;
			}
			break;
		}
						
		case UNDERSCORE: {
			//input statement line number, return all vars modified in statement line.
			std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(leftArg));
			if (modifiesSet.empty()) {
				result.setResultTrue(false);
				return result;
			}
			break;
		}
					   //Find variable v defined in QPS which is modified by given statement line defined in source. 
		default:
		{
			string synonDeType = synonymTable.find(rightArg)->second;
			/*resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
			std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);*/
			std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
			std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
			std::vector<std::string> resultSynonValues;

			for (auto currSynonVal : currSynonValues) {
				// check whether given statement line modifies historical variables in source.
				bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), currSynonVal);
				if (isModifies) {
					resultSynonValues.push_back(currSynonVal);
				}
			}

			if (resultSynonValues.empty()) {
				result.setResultTrue(false);
				return result;
			}
			result.setClauseResult(ResultTable(resultSynonValues, rightArg));

			break;
		}
		}
		break;
	default:
		switch (rightType)
		{
			//Left type is a statement defined in QPS, find whether given statement modifies given variable in source.
		case QUOTED_IDENT: {
			string synonDeType = synonymTable.find(leftArg)->second;
			// currSynonValues here are statement line numbers in string format.
			std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
			std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
			std::vector<std::string> resultSynonValues;

			for (auto currSynonVal : currSynonValues) {
				// check whether given statement line modifies historical variables in source.
				bool isModifies = pkb.areInModifiesStmtRelationship(stoi(currSynonVal), Utility::trim_double_quotes(rightArg));
				if (isModifies) {
					resultSynonValues.push_back(currSynonVal);
				}
			}

			if (resultSynonValues.empty()) {
				result.setResultTrue(false);
				return result;
			}
			result.setClauseResult(ResultTable(resultSynonValues, leftArg));
			break;
		}
						 //Left type is a statement defined in QPS, find whether given statement has some modifications to some variables in source
		case UNDERSCORE: {
			string synonDeType = synonymTable.find(leftArg)->second;		
			// currSynonValues here are statement line numbers in string format.
			std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
			std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
			std::vector<std::string> resultSynonValues;

			for (auto currSynonVal : currSynonValues) {

				std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(currSynonVal));

				if (!modifiesSet.empty()) {
					resultSynonValues.push_back(currSynonVal);
				}
			}

			if (resultSynonValues.empty()) {
				result.setResultTrue(false);
				return result;
			}
			result.setClauseResult(ResultTable(resultSynonValues, leftArg));
			break;
		}
	//Left type is a statement defined in QPS, right type is a varible defined in QPS, find all pairs of statement s defined in source and varible v 
	// defined in source such that s modifies v. 
		default:
		{
			string leftDeType = synonymTable.find(leftArg)->second;
			string rightDeType = synonymTable.find(rightArg)->second;
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
				bool isRightModifiesLeft = pkb.areInModifiesStmtRelationship(stoi(tuple[0]), tuple[1]);
				if (isRightModifiesLeft) {
					tempTable.insertTuple({ tuple[0], tuple[1] });
				}
			}

			if (tempTable.isTableEmpty()) {
				result.setResultTrue(false);
				return result;
			}

			result.setClauseResult(tempTable);

			break;
		}
		}
		break;
	}
	return result;

	//if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
	//	//input statement line number, return all vars modified in statement line.
	//	std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(leftArg));
	//	if (modifiesSet.empty()) {
	//		result.setResultTrue(false);
	//		return result;
	//	}
	//}
	//// Find ident string in source program which is modified by a statement line defined in source.
	//else if (leftType == Utility::INTEGER && rightType == Utility::QUOTED_IDENT) {
	//	// identString of format \"x\"
	//	bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), Utility::trim_double_quotes(rightArg));
	//	if (!isModifies) {
	//		result.setResultTrue(false);
	//		return result;
	//	}
	//}
	////Find variable v defined in QPS which is modified by given statement line defined in source. 
	//else if (leftType == Utility::INTEGER) {
	//	string synonDeType = synonymTable.find(rightArg)->second;
	//	/*resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
	//	std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);*/
	//	std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
	//	std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
	//	std::vector<std::string> resultSynonValues;
	//
	//	for (auto currSynonVal : currSynonValues) {
	//		// check whether given statement line modifies historical variables in source.
	//		bool isModifies = pkb.areInModifiesStmtRelationship(stoi(leftArg), currSynonVal);
	//		if (isModifies) {
	//			resultSynonValues.push_back(currSynonVal);
	//		}
	//	}
	//
	//	if (resultSynonValues.empty()) {
	//		result.setResultTrue(false);
	//		return result;
	//	}
	//	result.setClauseResult(ResultTable(resultSynonValues, rightArg));
	//}
	////Left type is a statement defined in QPS, find whether given statement has some modifications to some variables in source
	//else if (rightType == Utility::UNDERSCORE) {
	//	string synonDeType = synonymTable.find(leftArg)->second;
	//	/*resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);*/
	//	// currSynonValues here are statement line numbers in string format.
	//	//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
	//	std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
	//	std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
	//	std::vector<std::string> resultSynonValues;

	//	for (auto currSynonVal : currSynonValues) {

	//		std::set<std::string> modifiesSet = pkb.getModifiesVarsFromStmt(stoi(currSynonVal));
	//		
	//		if (!modifiesSet.empty()) {
	//			resultSynonValues.push_back(currSynonVal);
	//		}
	//	}
	//
	//	if (resultSynonValues.empty()) {
	//		result.setResultTrue(false);
	//		return result;
	//	}
	//	result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	//}
	////Left type is a statement defined in QPS, find whether given statement modifies given variable in source.
	//else if (rightType == Utility::QUOTED_IDENT) {
	//	string synonDeType = synonymTable.find(leftArg)->second;
	//	//resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
	//	// currSynonValues here are statement line numbers in string format.
	//	//std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
	//	std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
	//	std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
	//	std::vector<std::string> resultSynonValues;

	//	for (auto currSynonVal : currSynonValues) {
	//		// check whether given statement line modifies historical variables in source.
	//		bool isModifies = pkb.areInModifiesStmtRelationship(stoi(currSynonVal), Utility::trim_double_quotes(rightArg));
	//		if (isModifies) {
	//			resultSynonValues.push_back(currSynonVal);
	//		}
	//	}

	//	if (resultSynonValues.empty()) {
	//		result.setResultTrue(false);
	//		return result;
	//	}
	//	result.setClauseResult(ResultTable(resultSynonValues, leftArg));
	//}
	////Left type is a statement defined in QPS, right type is a varible defined in QPS, find all pairs of statement s defined in source and varible v 
	//// defined in source such that s modifies v. 
	//else {
	//	string leftDeType = synonymTable.find(leftArg)->second;
	//	string rightDeType = synonymTable.find(rightArg)->second;
	//	//resultTable.resultTableCheckAndAdd(leftArg, pkb, leftDeType);
	//	//resultTable.resultTableCheckAndAdd(rightArg, pkb, rightDeType);
	//	std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
	//	std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
	//	//convert the set to vector
	//	std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
	//	std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());


	//	//std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
	//	//std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);
	//	ResultTable initTable(currLeftValues, leftArg);
	//	initTable.combineTable(ResultTable(currRightValues, rightArg));
	//	int initTableSize = initTable.getColNum();

	//	ResultTable tempTable({ leftArg, rightArg });

	//	for (int i = 0; i < initTableSize; i++) {
	//		std::vector<std::string> tuple = initTable.getTuple(i);
	//		bool isRightModifiesLeft = pkb.areInModifiesStmtRelationship(stoi(tuple[0]), tuple[1]);
	//		if (isRightModifiesLeft) {
	//			tempTable.insertTuple({ tuple[0], tuple[1] });
	//		}
	//	}

	//	if (tempTable.isTableEmpty()) {
	//		result.setResultTrue(false);
	//		return result;
	//	}

	//	result.setClauseResult(tempTable);
	//}
	////Do we need to throw exception if type doesn't match? As all semantics are checked already.
	//return result;
}
