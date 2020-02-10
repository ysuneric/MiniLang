//
//Eric Sun 2020
//260673824
//

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int yylineno;

EXP *malloc_exp()
{
	EXP *new = (EXP *) malloc(sizeof(EXP));
	if (new == NULL)
	{
		free(new);
		fprintf(stderr, "Error: malloc failed\n");
		exit(1);
	}
	return new;
}

EXP *new_intType()
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = INT_TYPE;
	return e;
}

EXP *new_floatType()
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = FLOAT_TYPE;
	return e;
}

EXP *new_boolType()
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = BOOL_TYPE;
	return e;
}

EXP *new_stringType()
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STRING_TYPE;
	return e;
}

EXP *new_intLiteral(int intLiteral)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = INT_LITERAL;
	e->val.intLiteral = intLiteral;
	return e;
}

EXP *new_floatLiteral(float floatLiteral)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = FLOAT_LITERAL;
	e->val.floatLiteral = floatLiteral;
	return e;
}

EXP *new_boolLiteral(bool boolLiteral)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = BOOL_LITERAL;
	e->val.boolLiteral = boolLiteral;
	return e;
}

EXP *new_stringLiteral(const char *stringLiteral)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STRING_LITERAL;
	e->val.idE.name = (char *) stringLiteral;
	return e;
}

EXP *new_identifier(const char *id)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = IDENTIFIER;
	e->val.idE.name = (char *) id;
	return e;
}

EXP *new_expAdd(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_ADD;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expMinus(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_MINUS;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expTimes(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_TIMES;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expDivide(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_DIVIDE;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expNeg(EXP *exp)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_NEG;
	e->val.binary.lhs = exp;
	e->val.binary.rhs = NULL;
	return e;
}

EXP *new_expLess(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_LT;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expLessEqual(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_LTE;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expGreater(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_GT;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expGreaterEqual(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_GTE;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expEqual(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_EQUAL;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expNotEqual(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_NE;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expAnd(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_AND;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expOr(EXP *left, EXP *right)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_OR;
	e->val.binary.lhs = left;
	e->val.binary.rhs = right;
	return e;
}

EXP *new_expNot(EXP *exp)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = EXPRESSION_NOT;
	e->val.binary.lhs = exp;
	e->val.binary.rhs = NULL;
	return e;
}

EXP *new_declaration(EXP *id, EXP *exp)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = DECLARATION;
	e->val.binary.lhs = id;
	e->val.binary.rhs = exp;
	return e;
}

EXP *new_declarationType(EXP *id, EXP *type, EXP *exp) //HOW TO DO THIS BITCH
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = DECLARATION_TYPE;
	e->val.ternary.left = id;
	e->val.ternary.center = type;
	e->val.ternary.right = exp;
	return e;
}

EXP *new_read(const char *id)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_READ;
	e->val.idE.name = (char *) id;
	return e;
}

EXP *new_print(EXP *exp)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_PRINT;
	e->val.binary.lhs = exp;
	e->val.binary.rhs = NULL;
	return e;
}

EXP *new_assign(EXP *id, EXP *exp)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_ASSIGN;
	e->val.binary.lhs = id;
	e->val.binary.rhs = exp;
	return e;
}

EXP *new_while(EXP *exp, EXP *statements)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_WHILE;
	e->val.binary.lhs = exp;
	e->val.binary.rhs = statements;
	return e;
}

EXP *new_if(EXP *exp, EXP *statements, EXP *conditional)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_IF;
	e->val.ternary.left = exp;
	e->val.ternary.center = statements;
	e->val.ternary.right = conditional;
	return e;
}

EXP *new_elseIf(EXP *exp, EXP *statements, EXP *conditional)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_ELSE_IF;
	e->val.ternary.left = exp;
	e->val.ternary.center = statements;
	e->val.ternary.right = conditional;
	return e;
}

EXP *new_else(EXP *statements)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_ELSE;
	e->val.binary.lhs = statements;
	e->val.binary.rhs = NULL;
	return e;
}

EXP *new_statementList(EXP *exp, EXP *statements)
{
	EXP *e = malloc_exp();
	e->lineno = yylineno;
	e->kind = STATEMENT_LIST;
	e->val.binary.lhs = exp;
	e->val.binary.rhs = statements;
	return e;
}

EXP *new_null()
{
	return NULL;
}
