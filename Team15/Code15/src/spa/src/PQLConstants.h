namespace PQLConstants {

	enum class Entity {
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

	enum class Relationship {
		FOLLOWS,
		FOLLOWS_T,
		PARENT,
		PARENT_T,
		USES_S,
		USES_P,
		MODIFIES_S,
		MODIFIES_P
	};

}