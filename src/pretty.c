//
//Eric Sun 2020
//260673824
//

#include <stdio.h>
#include <stdbool.h>

#include "pretty.h"

size_t indent = 0;

void prettyEXP(EXP *e)
{
	if (e == NULL) return;
	switch (e->kind)
	{
		case INT_TYPE:
			printf("int");
			break;
		case FLOAT_TYPE:
			printf("float");
			break;
		case BOOL_TYPE:
			printf("bool");
			break;
		case STRING_TYPE:
			printf("string");
			break;
		case INT_LITERAL:
			printf("%d", e->val.intLiteral);
			break;
		case FLOAT_LITERAL:
			printf("%f", e->val.floatLiteral);
			break;
		case BOOL_LITERAL:
			printf("%s", e->val.boolLiteral ? "True" : "False");
			break;
		case STRING_LITERAL:
			printf("%s", e->val.idE.name);
			break;
		case IDENTIFIER:
			printf("%s", e->val.idE.name);
			break;
		case EXPRESSION_ADD:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" + ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_MINUS:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" - ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_TIMES:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" * ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_DIVIDE:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" / ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_NEG:
			printf("-(");
			prettyEXP(e->val.binary.lhs);
			printf(")");
			break;
		case EXPRESSION_EQUAL:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" == ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_NE:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" != ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_LTE:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" <= ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_LT:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" < ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_GTE:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" >= ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_GT:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" > ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_AND:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" && ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_OR:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" || ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case EXPRESSION_NOT:
			printf("!(");
			prettyEXP(e->val.binary.lhs);
			printf(")");
			break;
		case DECLARATION:
			printf("var ");
			prettyEXP(e->val.binary.lhs);
			printf(" = ");
			prettyEXP(e->val.binary.rhs);
			printf(";\n");
			break;
		case DECLARATION_TYPE:
			printf("var ");
			prettyEXP(e->val.ternary.left);
			printf(": ");
			prettyEXP(e->val.ternary.center);
			printf(" = ");
			prettyEXP(e->val.ternary.right);
			printf(";\n");
			break;
		case STATEMENT_READ:
			printf("read(%s);\n", e->val.idE.name);
			break;
		case STATEMENT_PRINT:
			printf("print(");
			prettyEXP(e->val.binary.lhs);
			printf(");\n");
			break;
		case STATEMENT_ASSIGN:
			prettyEXP(e->val.binary.lhs);
			printf(" = ");
			prettyEXP(e->val.binary.rhs);
			printf(";\n");
			break;
		case STATEMENT_WHILE:
			printf("while (");
			prettyEXP(e->val.binary.lhs);
			printf(") {\n");
			indent++;
			prettyEXP(e->val.binary.rhs);
			indent--;
			printf("}\n");
			break;
		case STATEMENT_IF:
			printf("if (");
			prettyEXP(e->val.ternary.left);
			printf(") {\n");
			indent++;
			prettyEXP(e->val.ternary.center);
			indent--;
			printf("}");
			if (e->val.ternary.right != NULL)
			{
				prettyEXP(e->val.ternary.right);
			} else
			{
				printf("\n");
			}
			break;
		case STATEMENT_ELSE_IF:
			printf(" else if (");
			prettyEXP(e->val.ternary.left);
			printf(") {\n");
			indent++;
			prettyEXP(e->val.ternary.center);
			indent--;
			printf("}");
			if (e->val.ternary.right != NULL)
			{
				prettyEXP(e->val.ternary.right);
			} else
			{
				printf("\n");
			}
			break;
		case STATEMENT_ELSE:
			printf(" else {\n");
			indent++;
			prettyEXP(e->val.binary.lhs);
			indent--;
			printf("}\n");
			break;
		case STATEMENT_LIST:
			for (int i = 0; i < indent; i++)
			{
				printf("\t");
			}
			prettyEXP(e->val.binary.lhs);
			prettyEXP(e->val.binary.rhs);
			break;
		default:
			return;
	}
}
