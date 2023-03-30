#include <string>
#include <regex>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <set>
#include "exceptions/PQLSyntaxError.h"
#include "pkb/include/PKB.h"

#pragma once
enum Relationship
{
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
    FOLLOWSSTAR,
    USESS,
    USESP,
    MODIFIESS,
    MODIFIESP,
};

enum ReferenceType
{
    SYNONYM,
    INTEGER,
    UNDERSCORE,
    EXPR,
    QUOTED_IDENT,
    INVALID,
    UNDERSCORED_EXPR,
};

enum DesignEntity
{
    PROCEDURE,
    STMT,
    READ,
    PRINT,
    ASSIGN,
    CALL,
    WHILE,
    IF,
    VARIABLE,
    CONSTANT
};

class Utility
{
public:
    inline static const std::string assign = "assign";
    inline static const std::string variable = "variable";
    inline static const std::string procedure = "procedure";
    inline static const std::string print = "print";
    inline static const std::string read = "read";
    inline static const std::string constant = "constant";
    inline static const std::string whileStmt = "while";
    inline static const std::string ifStmt = "if";
    inline static const std::string call = "call";
    inline static const std::string stmt = "stmt";

    inline static const std::unordered_set<std::string> designEntitySet = {procedure, stmt, read, print,
                                                                           assign, call, whileStmt, ifStmt, variable, constant};
    inline static const std::unordered_set<std::string> attrNameSet = {"procName", "varName", "value", "stmt#"};
    inline static const std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
    inline static const std::string integerFormat = "[1-9][0-9]*";
    inline static const std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
    inline static const std::string underscoredExprFormat = "_\"[\\s\\S]*\"_";
    inline static const std::string exprFormat = "\"[\\s\\S]*\"";

    inline static const std::string whiteSpaces = " \t\n";
    inline static const std::string quote = "\"";
    inline static const std::string underscore = "_";
    inline static const std::string expr = "expr";
    inline static const std::string underscored_expr = "underscored_expr";
    inline static const std::string quoted_ident = "quoted_ident";
    inline static const std::string integer = "integer";
    inline static const std::string synonym = "synonym";
    inline static const std::string invalid = "Invalid";

    inline static const std::string parent = "Parent";
    inline static const std::string parentStar = "Parent*";
    inline static const std::string follows = "Follows";
    inline static const std::string followsStar = "Follows*";
    inline static const std::string modifiesS = "ModifiesS";
    inline static const std::string modifiesP = "ModifiesP";
    inline static const std::string modifies = "Modifies";
    inline static const std::string usesS = "UsesS";
    inline static const std::string usesP = "UsesP";
    inline static const std::string uses = "Uses";
    inline static const std::string calls = "Calls";
    inline static const std::string callsStar = "Calls*";
    inline static const std::string next = "Next";
    inline static const std::string nextStar = "Next*";
    inline static const std::string affects = "Affects";
    inline static const std::string affectsStar = "Affects*";

    inline static const std::string procName = "procName";
    inline static const std::string varName = "varName";
    inline static const std::string stmtNum = "stmt#";
    inline static const std::string value = "value";

    inline static const ReferenceType getEnumReferenceType(std::string input)
    {
        if (std::regex_match(input, std::regex(synonymFormat)))
        {
            return SYNONYM;
        }
        else if (std::regex_match(input, std::regex(integerFormat)))
        {
            return INTEGER;
        }
        else if (std::regex_match(input, std::regex(quotedIdentFormat)))
        {
            return QUOTED_IDENT;
        }
        else if (std::regex_match(input, std::regex(underscoredExprFormat)))
        {
            return UNDERSCORED_EXPR;
        }
        else if (std::regex_match(input, std::regex(exprFormat)))
        {
            return EXPR;
        }
        else if (std::regex_match(input, std::regex(underscore)))
        {
            return UNDERSCORE;
        }
        else
        {
            return INVALID;
        }
    };

    inline static const std::string getReferenceType(std::string input)
    {
        if (std::regex_match(input, std::regex(synonymFormat)))
        {
            return synonym;
        }
        else if (std::regex_match(input, std::regex(integerFormat)))
        {
            return integer;
        }
        else if (std::regex_match(input, std::regex(quotedIdentFormat)))
        {
            return quoted_ident;
        }
        else if (std::regex_match(input, std::regex(underscoredExprFormat)))
        {
            return underscored_expr;
        }
        else if (std::regex_match(input, std::regex(exprFormat)))
        {
            return expr;
        }
        else if (std::regex_match(input, std::regex(underscore)))
        {
            return underscore;
        }
        else
        {
            return invalid;
        }
    };

    // remove exprToTrim in the front and end
    inline static const std::string trim(std::string input, std::string exprToTrim)
    {
        std::string trimmed = input;
        std::size_t firstPos = trimmed.find_first_not_of(exprToTrim);
        // trim left
        if (firstPos != std::string::npos)
        {
            trimmed = trimmed.substr(firstPos);
        }
        // trim right
        std::size_t lastPos = trimmed.find_last_not_of(exprToTrim);
        if (lastPos != std::string::npos)
        {
            trimmed = trimmed.substr(0, lastPos + 1);
        }
        return trimmed;
    };

    inline static const std::string trim_double_quotes(std::string s)
    {
        if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"')
        {
            return s.substr(1, s.length() - 2);
        }
        return s;
    }

    inline static const bool isStarRelationship(std::string relationship)
    {
        return relationship.find('*') != std::string::npos;
    }

    inline static const std::set<std::string> getResultFromPKB(PKB &pkb, std::string DeType)
    {
        std::set<std::string> ret;
        if (DeType == constant)
        {
            ret = pkb.getAllConstVals();
        }
        else if (DeType == procedure)
        {
            ret = pkb.getAllProcNames();
        }
        else if (DeType == variable)
        {
            ret = pkb.getAllVarNames();
        }
        else
        {
            std::set<int> allStmtIntSet;

            if (DeType == stmt)
            {
                allStmtIntSet = pkb.getAllStmtNums();
            }
            else if (DeType == assign)
            {
                allStmtIntSet = pkb.getAllStmtNumsByType("=");
            }
            else
            {
                allStmtIntSet = pkb.getAllStmtNumsByType(DeType);
            }

            for (int stmtNum : allStmtIntSet)
            {
                ret.insert(to_string(stmtNum));
            }
        }
        return ret;
    }
    inline static const DesignEntity getDesignEntityFromString(std::string designEntity)
    {
        if (designEntity == procedure)
        {
            return PROCEDURE;
        }
        else if (designEntity == stmt)
        {
            return STMT;
        }
        else if (designEntity == constant)
        {
            return CONSTANT;
        }
        else if (designEntity == variable)
        {
            return VARIABLE;
        }
        else if (designEntity == read)
        {
            return READ;
        }
        else if (designEntity == print)
        {
            return PRINT;
        }
        else if (designEntity == ifStmt)
        {
            return IF;
        }
        else if (designEntity == whileStmt)
        {
            return WHILE;
        }
        else if (designEntity == call)
        {
            return CALL;
        }
        else if (designEntity == assign)
        {
            return ASSIGN;
        }
        else
        {
            throw std::runtime_error("Unsupport designEntity string");
        }
    }

    inline static const Relationship getRelationshipFromString(std::string relationship)
    {
        if (relationship == modifies)
        {
            return MODIFIES;
        }
        else if (relationship == uses)
        {
            return USES;
        }
        else if (relationship == calls)
        {
            return CALLS;
        }
        else if (relationship == callsStar)
        {
            return CALLSSTAR;
        }
        else if (relationship == follows)
        {
            return FOLLOWS;
        }
        else if (relationship == followsStar)
        {
            return FOLLOWSSTAR;
        }
        else if (relationship == parent)
        {
            return PARENT;
        }
        else if (relationship == parentStar)
        {
            return PARENTSTAR;
        }
        else if (relationship == affects)
        {
            return AFFECTS;
        }
        else if (relationship == affectsStar)
        {
            return AFFECTSSTAR;
        }
        else if (relationship == nextStar)
        {
            return NEXTSTAR;
        }
        else if (relationship == next)
        {
            return NEXT;
        }
        else
        {
            throw std::runtime_error("Unsupport relationship string");
        }
    }
};
