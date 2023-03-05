#include "QPS/include/evaluator/UsesSHandler.h"


UsesSHandler::UsesSHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result UsesSHandler::evalUsesS(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
	std::string leftArg = suchThatClause.getLeftArg();
	std::string rightArg = suchThatClause.getRightArg();
	std::string leftType = Utility::getReferenceType(leftArg);
	std::string rightType = Utility::getReferenceType(rightArg);
	Result result;

	//std::set<std::string> PKB::getUsesVarsFromStmt(int stmtNum) {
	//	return usesStmtTable.getManyRight(stmtNum);
	//}

	//std::set<int> PKB::getUsesStmtsFromVar(std::string varName) {
	//	return usesStmtTable.getManyLeft(varName);
	//}

	//bool PKB::areInUsesStmtRelationship(int stmtNum, std::string varName) {
	//	return usesStmtTable.inOneToManyRelationship(stmtNum, varName);
	//}


	// Find everything defined in source used by a statement line defined in source.
	if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
		//input statement line number, return all vars modified in statement line.
		std::set<std::string> usesSet = pkb.getUsesVarsFromStmt(stoi(leftArg));
		if (usesSet.empty()) {
			result.setResultTrue(false);
			return result;
		}
	}
	// Find ident string in source program which is used by a statement line defined in source.
	else if (leftType == Utility::INTEGER && rightType == Utility::QUOTED_IDENT) {
		// identString of format \"x\"
		bool isUses = pkb.areInUsesStmtRelationship(stoi(leftArg), Utility::trim_double_quotes(rightArg));
		if (!isUses) {
			result.setResultTrue(false);
			return result;
		}
	}
	//Find variable v defined in QPS which is used by given statement line defined in source. 
	else if (leftType == Utility::INTEGER) {
		string synonDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
		std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given statement line uses historical variables in source.
			bool isUses = pkb.areInUsesStmtRelationship(stoi(leftArg), currSynonVal);
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
	//Left type is a statement defined in QPS, find whether given statement has some uses to some variables in source
	else if (rightType == Utility::UNDERSCORE) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {

			std::set<std::string> usesSet = pkb.getUsesVarsFromStmt(stoi(currSynonVal));

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
	//Left type is a statement defined in QPS, find whether given statement uses given variable in source.
	else if (rightType == Utility::QUOTED_IDENT) {
		string synonDeType = synonymTable.find(leftArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
		// currSynonValues here are statement line numbers in string format.
		std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> resultSynonValues;

		for (auto currSynonVal : currSynonValues) {
			// check whether given statement line uses historical variables in source.
			bool isUses = pkb.areInUsesStmtRelationship(stoi(currSynonVal), Utility::trim_double_quotes(rightArg));
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
	//Left type is a statement defined in QPS, right type is a varible defined in QPS, find all pairs of statement s defined in source and varible v 
	// defined in source such that s uses v. 
	else {
		string leftDeType = synonymTable.find(leftArg)->second;
		string rightDeType = synonymTable.find(rightArg)->second;
		resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
		resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
		/*set<string> currLeftValues = resultTable.getStringSetFromKey(leftArg);
		set<string> currRightValues = resultTable.getStringSetFromKey(rightArg);*/
		std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
		std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);

		/*std::unordered_map<std::string, SynonymLinkageMap> leftResultValues;
		std::unordered_map<std::string, SynonymLinkageMap> rightResultValues;*/
		ResultTable tempResultTable({ leftArg, rightArg });
		for (int i = 0; i < currLeftValues.size(); i++) {
			bool isRightUsesLeft = pkb.areInUsesStmtRelationship(stoi(currLeftValues[i]), currRightValues[i]);
			if (isRightUsesLeft) {
				tempResultTable.insertTuple({ currLeftValues[i], currRightValues[i] });
			}
		}
		//for (string currLeftVal : currLeftValues) {
		//	for (string currRightVal : currRightValues) {
		//		bool isRightUsesLeft = pkb.areInUsesStmtRelationship(stoi(currLeftVal), currRightVal);
		//		if (isRightUsesLeft) {
		//			tempResultTable.insertTuple({ currLeftVal, currRightVal });

		//			/*if (leftResultValues.find(currLeftVal) == leftResultValues.end()) {
		//				SynonymLinkageMap leftLinkedSynonymCollection;
		//				leftLinkedSynonymCollection.insertLinkage(rightArg, currRightVal);
		//				leftResultValues.insert(std::make_pair<>(currLeftVal, leftLinkedSynonymCollection));
		//			}
		//			else {
		//				leftResultValues.find(currLeftVal)->second
		//					.insertLinkage(rightArg, currRightVal);
		//			}

		//			if (rightResultValues.find(currRightVal) == rightResultValues.end()) {
		//				SynonymLinkageMap rightLinkedSynonymCollection;
		//				rightLinkedSynonymCollection.insertLinkage(leftArg, currLeftVal);
		//				rightResultValues.insert(std::make_pair<>(currRightVal, rightLinkedSynonymCollection));
		//			}
		//			else {
		//				rightResultValues.find(currRightVal)->second
		//					.insertLinkage(leftArg, currLeftVal);
		//			}*/
		//		}
		//	}
		//}

		if (tempResultTable.isTableEmpty()) {
			result.setResultTrue(false);
			return result;
		}

		result.setClauseResult(true, true, tempResultTable);
	}
	//Do we need to throw exception if type doesn't match? As all semantics are checked already.
	return result;
}
