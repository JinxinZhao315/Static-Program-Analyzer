#include<string>
#include<regex>
#include<unordered_set>
#include <algorithm>
#include <iterator>
#include <set>
#include"exceptions/PQLSyntaxError.h"
#include "pkb/include/PKB.h"

#pragma once
enum Relationship {
    MODIFIES,
    USES,
    CALLS,
    CALLSSTAR,
    AFFECTS,
    AFFECTSSTAR,
    NEXT,
    NEXTSTAR,
    PARENT,
    PARENTSTAR,
    FOLLOWS,
    FOLLOWSSTAR
};

enum ReferenceType {
    SYNONYM,
    INTEGER,
    UNDERSCORE,
    EXPR,
    QUOTED_IDENT,
    INVALID,
    UNDERSCORED_EXPR,
};

class Utility {
public:
	inline static const std::unordered_set<std::string> designEntitySet = { "procedure", "stmt", "read", "print",
		"assign", "call", "while", "if", "variable", "constant" };
	inline static const std::unordered_set<std::string> attrNameSet = { "procName", "varName", "value", "stmt#"};
	inline static const std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	inline static const std::string integerFormat = "[1-9][0-9]*";
	inline static const std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	inline static const std::string underscoredExpr = "_\"[\\s\\S]*\"_";
	inline static const std::string expr = "\"[\\s\\S]*\"";

    inline static const std::string whiteSpaces = " \t\n";
    inline static const std::string quote = "\"";
	inline static const std::string underscore = "_";
    inline static const std::string exprType = "expr";
    inline static const std::string underscored_expr = "underscoredExpr";
    inline static const std::string quoted_ident = "quotedIdent";
    inline static const std::string integer = "integer";
    inline static const std::string synonym = "synonym";
    inline static const std::string invalid = "Invalid";


	inline static const ReferenceType getEnumReferenceType(std::string input) {
		if (std::regex_match(input, std::regex(synonymFormat))) {
			return SYNONYM;
		}
		else if (std::regex_match(input, std::regex(integerFormat))) {
			return INTEGER;
		}
		else if (std::regex_match(input, std::regex(quotedIdentFormat))) {
			return QUOTED_IDENT;
		}
		else if (std::regex_match(input, std::regex(underscoredExpr))) {
			return UNDERSCORED_EXPR;
		}
		else if (std::regex_match(input, std::regex(expr))) {
			return EXPR;
		}
		else if (std::regex_match(input, std::regex(underscore))) {
			return UNDERSCORE;
		}
		else {
			return INVALID;
		}
	};

	//remove exprToTrim in the front and end
    inline static const std::string trim(std::string input, std::string exprToTrim) {
        std::string trimmed = input;
        std::size_t firstWhitespace = trimmed.find_first_not_of(exprToTrim);
        // trim left
        if (firstWhitespace != std::string::npos) {
            trimmed = trimmed.substr(firstWhitespace);
        }
        // trim right
        std::size_t lastWhitespace = trimmed.find_last_not_of(exprToTrim);
        if (lastWhitespace != std::string::npos) {
            trimmed = trimmed.substr(0, lastWhitespace + 1);
        }
        return trimmed;
    };

	inline static const std::string trim_double_quotes(std::string s) {
		if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"') {
			return s.substr(1, s.length() - 2);
		}
		return s;
	}

    inline static const bool isStarRelationship(std::string relationship) {
        return relationship.find('*') != std::string::npos;
    }

    inline static const std::set<std::string> getResultFromPKB(PKB& pkb, std::string DeType) {
        std::set<std::string> ret;
        if (DeType == "constant") {
            ret = pkb.getAllConstVals();
        }
        else if (DeType == "procedure") {
            ret = pkb.getAllProcNames();
        }
        else if (DeType == "variable") {
            ret = pkb.getAllVarNames();
        }
        else {
            std::set<int> allStmtIntSet;

            if (DeType == "stmt") {
                allStmtIntSet = pkb.getAllStmtNums();
            }
            else if (DeType == "assign") {
                allStmtIntSet = pkb.getAllStmtNumsByType("=");
            }
            else {
                allStmtIntSet = pkb.getAllStmtNumsByType(DeType);
            }

            for (int stmtNum : allStmtIntSet) {
                ret.insert(to_string(stmtNum));
            }
        }
        return ret;
    }

    inline static const Relationship getRelationshipFromString(std::string relationship) {
        if (relationship == "Modifies") {
            return MODIFIES;
        }
        else if (relationship == "Uses") {
            return USES;
        }
        else if (relationship == "Calls") {
            return CALLS;
        }
        else if (relationship == "Calls*") {
            return CALLSSTAR;
        }
        else if (relationship == "Follows") {
            return FOLLOWS;
        }
        else if (relationship == "Follows*") {
            return FOLLOWSSTAR;
        }
        else if (relationship == "Parent") {
            return PARENT;
        }
        else if (relationship == "Parent*") {
            return PARENTSTAR;
        }
        else if (relationship == "Affects") {
            return AFFECTS;
        }
        else if (relationship == "Affects*") {
            return AFFECTSSTAR;
        }
        else if (relationship == "Next*") {
            return NEXTSTAR;
        }
        else if (relationship == "Next") {
            return NEXT;
        }
        else {
            throw std::runtime_error("Unsupport relationship string");
        }
    }
};


