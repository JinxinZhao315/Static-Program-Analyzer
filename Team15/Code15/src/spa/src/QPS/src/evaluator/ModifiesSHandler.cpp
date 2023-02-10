#include "QPS/include/evaluator/ModifiesSHandler.h"


//ModifiesSHandler::ModifiesSHandler(PKB& pkb) : ClauseHandler(pkb) {}
//
//Result ModifiesSHandler::evalModifiesS(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
//	std::string leftArg = suchThatClause.getLeftArg();
//	std::string righttArg = suchThatClause.getRightArg();
//	std::string leftType = Utility::getReferenceType(leftArg);
//	std::string rightType = Utility::getReferenceType(righttArg);
//	//std::set<std::string> getModifiesVarsFromStmt(int stmtNum);
//
//	//std::set<int> getModifiesStmtsFromVar(std::string varName);
//
//	//std::set<std::string> getModifiesVarsFromProc(std::string procName);
//
//	//std::set<std::string> getModifiesProcsFromVar(std::string varName);
//
//	//bool areInModifiesStmtRelationship(int stmtNum, std::string varName);
//
//	// bool areInModifiesProcRelationship(std::string procName, std::string varName);
//	// Find everything modified by a statement line.
//	if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
//		//pkb.getAllModifiedByStmt(int stmtNum);
//	}
//	// Find ident string in source program which is modified by a statement line.
//	else if (leftType == Utility::INTEGER && rightType == Utility::QUOTED_IDENT) {
//
//	}
//	//Find variable v which is modified by a statement line. 
//	else if (leftType == Utility::INTEGER && synonymTable.find(righttArg)->second == "variable") {
//		string synonDeType = synonymTable.find(leftArg)->second;
//		resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
//		std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);
//
//		std::set<string> resultSynonValues;
//
//		if (rightType == Utility::UNDERSCORE) {
//			for (string currSynonVal : currSynonValues) {
//				//std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, currSynonVal); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
//				/*if (!followerSet.empty()) {
//					resultSynonValues.insert(currSynonVal);
//				}*/
//			}
//		}
//		else if (rightType == Utility::INTEGER) {
//			for (string currSynonVal : currSynonValues) {
//				//bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currSynonVal, rightArg); //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
//				/*if (isRightFollowLeft) {
//					resultSynonValues.insert(currSynonVal);
//				}*/
//			}
//		}
//		if (resultSynonValues.empty()) {
//			//result.setResultTrue(false);
//			return result;
//		}
//		result.setLeftArg(leftArg, resultSynonValues);
//	}
//	//Find 
//	else if (rightType == Utility::UNDERSCORE) {
//
//	}
//	//Find
//	else if (rightType == Utility::QUOTED_IDENT) {
//
//	}
//	//Find
//	else {
//
//	}
//	return result;
//}
//
//std::set<int> ModifiesSHandler::getModifiesSFromPKB(bool isStar, string type, string arg) {
//
//}
//
//bool ModifiesSHandler::getIsModifiesSFromPKB(bool isStar, string leftArg, string rightArg) {
//
//}

