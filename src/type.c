//
// Eric Sun 2020
// 260673824
//

#include <stdio.h>

#include "type.h"
#include "tree.h"

char *toString(Type t)
{
	switch (t)
	{
		case INT:
			return "int";
		case FLOAT:
			return "float";
		case STRING:
			return "string";
		case BOOL:
			return "bool";
		case INFER:
			return "<infer>";
		default:
			return "error";
	}
}

Type typeAdd(Type t, Type t2)
{
	switch (t)
	{
		case STRING:
			if (t2 == STRING) return STRING;
			return INVALID;
		case INT:
			switch (t2)
			{
				case INT:
					return INT;
				case FLOAT:
					return FLOAT;
				default:
					return INVALID;
			}
		case FLOAT:
			if (t2 == INT || t2 == FLOAT) return FLOAT;
			return INVALID;
		default:
			return INVALID;
	}
}

Type typeMath(Type t, Type t2)
{
	switch (t)
	{
		case INT:
			switch (t2)
			{
				case INT:
					return INT;
				case FLOAT:
					return FLOAT;
				default:
					return INVALID;
			}
		case FLOAT:
			if (t2 == INT || t2 == FLOAT) return FLOAT;
			return INVALID;
		default:
			return INVALID;
	}
}

Type typeCompare(Type t, Type t2)
{
	switch (t)
	{
		case BOOL:
			if (t2 == BOOL) return BOOL;
			return INVALID;
		case STRING:
			if (t2 == STRING) return BOOL;
			return INVALID;
		case INT:
			if (t2 == INT || t2 == FLOAT) return BOOL;
			return INVALID;
		case FLOAT:
			if (t2 == FLOAT || t2 == INT) return BOOL;
			return INVALID;
		default:
			return INVALID;
	}
}

Type typeAssign(EXP *e)
{
	EXP *id = e->val.binary.lhs;
	EXP *exp = e->val.binary.rhs;
	Type typeId = id->val.idE.idsym->kind;
	Type typeExp = typeExpression(exp);
	switch (typeId)
	{
		case INT:
			if (typeExp == INT) return INT;
		case FLOAT:
			if (typeExp == INT || typeExp == FLOAT) return FLOAT;
		case BOOL:
			if (typeExp == BOOL) return BOOL;
		case STRING:
			if (typeExp == STRING) return STRING;
		default:
			break;
	}
	fprintf(stderr, "Error: (line %d) incompatible assignment [%s = %s], expected ‘%s'\n",
			e->lineno, toString(typeId), toString(typeExp), toString(typeId));
	exit(1);
}

Type typeExpression(EXP *e)
{
	if (e == NULL) return INVALID;
	switch (e->kind)
	{
		case INT_LITERAL:
			return INT;
		case FLOAT_LITERAL:
			return FLOAT;
		case BOOL_LITERAL:
			return BOOL;
		case STRING_LITERAL:
			return STRING;
		case IDENTIFIER:
		{
			Type check = e->val.idE.idsym->kind;
			return check;
		}
		case EXPRESSION_ADD:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeAdd(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '+' operation [%s + %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_MINUS:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeMath(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '-' operation [%s - %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_TIMES:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeMath(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '*' operation [%s * %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_DIVIDE:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeMath(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '/' operation [%s / %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_NEG:
		{
			Type val = typeExpression(e->val.binary.lhs);
			switch (val)
			{
				case INT:
					return INT;
				case FLOAT:
					return FLOAT;
				default:
				{
					fprintf(stderr, "Error: (line %d) incompatible operands to '-' operation [- %s]\n",
							e->lineno, toString(val));
					exit(1);
				}
			}
		}
		case EXPRESSION_EQUAL:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '==' operation [%s == %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_NE:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '!=' operation [%s != %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_LTE:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '<=' operation [%s <= %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_LT:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '<' operation [%s < %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_GTE:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '>=' operation [%s >= %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_GT:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			Type res = typeCompare(left, right);
			if (res == INVALID)
			{
				fprintf(stderr, "Error: (line %d) incompatible operands to '>' operation [%s > %s]\n",
						e->lineno, toString(left), toString(right));
				exit(1);
			}
			return res;
		}
		case EXPRESSION_AND:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			if (left == BOOL && right == BOOL)
			{
				return BOOL;
			}
			fprintf(stderr, "Error: (line %d) incompatible operands to '&&' operation [%s && %s]\n",
					e->lineno, toString(left), toString(right));
			exit(1);
		}
		case EXPRESSION_OR:
		{
			Type left = typeExpression(e->val.binary.lhs);
			Type right = typeExpression(e->val.binary.rhs);
			if (left == BOOL && right == BOOL)
			{
				return BOOL;
			}
			fprintf(stderr, "Error: (line %d) incompatible operands to '||' operation [%s || %s]\n",
					e->lineno, toString(left), toString(right));
			exit(1);
		}
		case EXPRESSION_NOT:
		{
			Type val = typeExpression(e->val.binary.lhs);
			if (val == BOOL)
			{
				return BOOL;
			}
			fprintf(stderr, "Error: (line %d) incompatible operands to '!' operation [! %s]\n",
					e->lineno, toString(val));
			exit(1);
		}
		default:
			return INVALID;
	}
}

Type typeDeclaration(EXP *e)
{
	switch (e->kind)
	{
		case DECLARATION:
		{
			EXP *id = e->val.binary.lhs;
			EXP *val = e->val.binary.rhs;
			id->val.idE.idsym->kind = typeExpression(val);
			return id->val.idE.idsym->kind;
		}
		case DECLARATION_TYPE:
		{
			EXP *id = e->val.ternary.left;
			EXP *val = e->val.ternary.right;
			Type typeId = id->val.idE.idsym->kind;
			Type typeVal = typeExpression(val);
			if (typeId != typeVal)
			{
				fprintf(stderr, "Error: (line %d) incompatible assignment [%s = %s], expected ‘%s'\n",
						e->lineno, toString(typeId), toString(typeVal), toString(typeId));
				exit(1);
			}
			return typeId;
		}
		default:
			return INVALID;
	}
}

void typeCheck(EXP *e)
{
	if (e == NULL) return;
	switch (e->kind)
	{
		case DECLARATION:
			typeDeclaration(e);
			return;
		case DECLARATION_TYPE:
			typeDeclaration(e);
			return;
		case STATEMENT_READ:
			return;
		case STATEMENT_PRINT:
		{
			typeExpression(e->val.binary.lhs);
			return;
		}
		case STATEMENT_ASSIGN:
			typeAssign(e);
			return;
		case STATEMENT_WHILE:
		{
			Type check = typeExpression(e->val.binary.lhs);
			if (check != BOOL)
			{
				fprintf(stderr, "Error: (line %d) while statement condition expected type 'bool', received '%s'\n",
						e->lineno, toString(check));
				exit(1);
			}
			typeCheck(e->val.binary.rhs);
			return;
		}
		case STATEMENT_IF:
		{
			Type check = typeExpression(e->val.ternary.left);
			if (check != BOOL)
			{
				fprintf(stderr, "Error: (line %d) if statement condition expected type 'bool', received '%s'\n",
						e->lineno, toString(check));
				exit(1);
			}
			typeCheck(e->val.ternary.center);
			typeCheck(e->val.ternary.right);
			return;
		}
		case STATEMENT_ELSE_IF:
		{

			Type check = typeExpression(e->val.ternary.left);
			if (check != BOOL)
			{
				fprintf(stderr, "Error: (line %d) if statement condition expected type 'bool', received '%s'\n",
						e->lineno, toString(check));
				exit(1);
			}
			typeCheck(e->val.ternary.center);
			typeCheck(e->val.ternary.right);
			return;
		}
		case STATEMENT_ELSE:
			typeCheck(e->val.binary.lhs);
			return;
		case STATEMENT_LIST:
			typeCheck(e->val.binary.lhs);
			typeCheck(e->val.binary.rhs);
			return;
		default:
			return;
	}
}
