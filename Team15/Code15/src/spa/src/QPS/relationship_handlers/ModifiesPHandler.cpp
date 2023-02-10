//#include "ModifiesPHandler.h"
//
//
//ModifiesPHandler::ModifiesPHandler(PKB& pkb) : ClauseHandler(pkb) {}
//
//Result ModifiesPHandler::evalModifiesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
//	std::string leftArg = suchThatClause.getLeftArg();
//	std::string righttArg = suchThatClause.getRightArg();
//	std::string leftType = Utility::getReferenceType(leftArg);
//	std::string rightType = Utility::getReferenceType(righttArg);
//	if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
//		pkb.getProcModifiesVar();
//	} 
//	else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
//		
//	} 
//	else if (leftType == Utility::QUOTED_IDENT) {
//	
//	} 
//	else if (rightType == Utility::UNDERSCORE) {
//	
//	} 
//	else if (rightType == Utility::QUOTED_IDENT) {
//
//	}
//	else {
//	
//	}
//	return result
//}
//
//std::set<int> ModifiesPHandler::getModifiesPFromPKB(string type, string arg) {
//
//}
//
//bool ModifiesPHandler::getIsModifiesPFromPKB(string leftArg, string rightArg) {
//
//}