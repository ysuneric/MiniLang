//
//Eric Sun 2020
//260673824
//

#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef enum //definitions for AST
{
	INT_TYPE,
	FLOAT_TYPE,
	BOOL_TYPE,
	STRING_TYPE,

	INT_LITERAL,
	FLOAT_LITERAL,
	BOOL_LITERAL,
	STRING_LITERAL,
	IDENTIFIER,

	EXPRESSION_ADD,
	EXPRESSION_MINUS,
	EXPRESSION_TIMES,
	EXPRESSION_DIVIDE,
	EXPRESSION_NEG,
	EXPRESSION_EQUAL,
	EXPRESSION_NE,
	EXPRESSION_LTE,
	EXPRESSION_LT,
	EXPRESSION_GTE,
	EXPRESSION_GT,
	EXPRESSION_AND,
	EXPRESSION_OR,
	EXPRESSION_NOT,

	DECLARATION,
	DECLARATION_TYPE,
	STATEMENT_READ,
	STATEMENT_PRINT,
	STATEMENT_ASSIGN,
	STATEMENT_WHILE,
	STATEMENT_IF,
	STATEMENT_ELSE_IF,
	STATEMENT_ELSE,

	STATEMENT_LIST,
} ExpressionKind;

typedef struct EXP //struct
{
	ExpressionKind kind;
	int lineno;
	union
	{
		//char *identifier;
		struct
		{
			char *name;
			struct SYMBOL *idsym;
		} idE;
		int intLiteral;
		float floatLiteral;
		bool boolLiteral;
		struct
		{
			struct EXP *lhs;
			struct EXP *rhs;
		} binary;
		struct
		{
			struct EXP *left;
			struct EXP *center;
			struct EXP *right;
		} ternary;
	} val;
} EXP;

//signatures
EXP *malloc_exp();

EXP *new_intType();

EXP *new_floatType();

EXP *new_boolType();

EXP *new_stringType();

EXP *new_intLiteral(int intLiteral);

EXP *new_floatLiteral(float floatLiteral);

EXP *new_boolLiteral(bool boolLiteral);

EXP *new_stringLiteral(const char *stringLiteral);

EXP *new_identifier(const char *id);

EXP *new_expAdd(struct EXP *left, struct EXP *right);

EXP *new_expMinus(struct EXP *left, struct EXP *right);

EXP *new_expTimes(struct EXP *left, struct EXP *right);

EXP *new_expDivide(struct EXP *left, struct EXP *right);

EXP *new_expNeg(struct EXP *exp);

EXP *new_expLess(struct EXP *left, struct EXP *right);

EXP *new_expLessEqual(struct EXP *left, struct EXP *right);

EXP *new_expGreater(struct EXP *left, struct EXP *right);

EXP *new_expGreaterEqual(struct EXP *left, struct EXP *right);

EXP *new_expEqual(struct EXP *left, struct EXP *right);

EXP *new_expNotEqual(struct EXP *left, struct EXP *right);

EXP *new_expAnd(struct EXP *left, struct EXP *right);

EXP *new_expOr(struct EXP *left, struct EXP *right);

EXP *new_expNot(struct EXP *exp);

EXP *new_declaration(struct EXP *id, struct EXP *exp);

EXP *new_declarationType(struct EXP *id, struct EXP *type, struct EXP *exp);

EXP *new_read(const char *id);

EXP *new_print(struct EXP *exp);

EXP *new_assign(struct EXP *id, struct EXP *exp);

EXP *new_while(struct EXP *exp, struct EXP *statements);

EXP *new_if(struct EXP *exp, struct EXP *statements, struct EXP *conditional);

EXP *new_elseIf(struct EXP *exp, struct EXP *statements, struct EXP *conditional);

EXP *new_else(struct EXP *statements);

EXP *new_statementList(struct EXP *exp, struct EXP *statements);

EXP *new_null();

#endif