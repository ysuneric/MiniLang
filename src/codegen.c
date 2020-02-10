//
// Eric Sun 2020
// 260673824
//

#include <stdio.h>
#include "codegen.h"
#include "tree.h"
#include "type.h"

extern size_t indent;
FILE *output;

void genExpression(EXP *e)
{
	if (e == NULL) return;
	switch (e->kind)
	{
		case INT_LITERAL:
			fprintf(output, "%d", e->val.intLiteral);
			break;
		case FLOAT_LITERAL:
			fprintf(output, "%lf", e->val.floatLiteral);
			break;
		case BOOL_LITERAL:
			if (e->val.boolLiteral)
			{
				fprintf(output, "True");
			} else
			{
				fprintf(output, "False");
			}
			break;
		case STRING_LITERAL:
			fprintf(output, "%s", e->val.idE.name);
			break;
		case IDENTIFIER:
			fprintf(output, "%s", e->val.idE.name);
			break;
		case EXPRESSION_ADD:
		{
			Type type = typeExpression(e);
			if (type == STRING)
			{
				fprintf(output, "cat(");
				genExpression(e->val.binary.lhs);
				fprintf(output, ", ");
				genExpression(e->val.binary.rhs);
				fprintf(output, ")");
			} else
			{
				fprintf(output, "(");
				genExpression(e->val.binary.lhs);
				fprintf(output, " + ");
				genExpression(e->val.binary.rhs);
				fprintf(output, ")");
			}
			break;
		}
		case EXPRESSION_MINUS:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " - ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_TIMES:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " * ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_DIVIDE:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " / ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_NEG:
			fprintf(output, "-(");
			genExpression(e->val.binary.lhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_EQUAL:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " == ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_NE:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " != ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_LTE:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " <= ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_LT:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " < ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_GTE:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " >= ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_GT:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " > ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_AND:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " && ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_OR:
			fprintf(output, "(");
			genExpression(e->val.binary.lhs);
			fprintf(output, " || ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ")");
			break;
		case EXPRESSION_NOT:
			fprintf(output, "!(");
			genExpression(e->val.binary.lhs);
			fprintf(output, ")");
			break;
		default:
			break;
	}
}

void generate(EXP *e)
{
	if (e == NULL) return;
	switch (e->kind)
	{
		case DECLARATION:
		{
			Type type = e->val.binary.lhs->val.idE.idsym->kind;
			char *id = e->val.binary.lhs->val.idE.name;
			EXP *val = e->val.binary.rhs;
			switch (type)
			{
				case INT:
					fprintf(output, "int %s = ", id);
					genExpression(val);
					fprintf(output, ";\n");
					break;
				case FLOAT:
					fprintf(output, "float %s = ", id);
					genExpression(val);
					fprintf(output, ";\n");
					break;
				case STRING:
					fprintf(output, "char *%s = ", id);
					genExpression(val);
					fprintf(output, ";\n");
					break;
				case BOOL:
					fprintf(output, "bool %s = ", id);
					genExpression(val);
					fprintf(output, ";\n");
					break;
				default:
					break;
			}
			break;
		}
		case DECLARATION_TYPE:
		{
			Type type = e->val.ternary.left->val.idE.idsym->kind;
			char *id = e->val.ternary.left->val.idE.name;
			EXP *val = e->val.ternary.right;
			switch (type)
			{
				case INT:
					fprintf(output, "int %s = %d;\n", id, val->val.intLiteral);
					break;
				case FLOAT:
					fprintf(output, "float %s = %lf;\n", id, val->val.floatLiteral);
					break;
				case STRING:
					fprintf(output, "char* %s = %s;\n", id, val->val.idE.name);
					break;
				case BOOL:
					if (e->val.boolLiteral)
					{
						fprintf(output, "bool %s = True;\n", id);
					} else
					{
						fprintf(output, "bool %s = False;\n", id);
					}
					break;
				default:
					break;
			}
			break;
		}
		case STATEMENT_READ:
		{
			switch (e->val.idE.idsym->kind)
			{
				case STRING:
					fprintf(output, "scanf(\"%%s\", %s);\n", e->val.idE.name);
					break;
				case INT:
					fprintf(output, "scanf(\"%%d\", %s);\n", e->val.idE.name);
					break;
				case FLOAT:
					fprintf(output, "scanf(\"%%lf\", %s);\n", e->val.idE.name);
					break;
				case BOOL:
					fprintf(output, "%s = scanBool();\n", e->val.idE.name);
					break;
				default:
					break;
			}
			break;
		}
		case STATEMENT_PRINT:
		{
			fprintf(output, "printf(");
			Type type = typeExpression(e->val.binary.lhs);
			switch (type)
			{
				case STRING:
					fprintf(output, "\"%%s\\n\", ");
					genExpression(e->val.binary.lhs);
					fprintf(output, ");\n");
					break;
				case INT:
					fprintf(output, "\"%%d\\n\", ");
					genExpression(e->val.binary.lhs);
					fprintf(output, ");\n");
					break;
				case FLOAT:
					fprintf(output, "\"%%lf\\n\", ");
					genExpression(e->val.binary.lhs);
					fprintf(output, ");\n");
					break;
				case BOOL:
					genExpression(e->val.binary.lhs);
					fprintf(output, " ? \"True\\n\" : \"False\\n\");\n");
					break;
				default:
					break;
			}
			break;
		}
		case STATEMENT_ASSIGN:
		{
			genExpression(e->val.binary.lhs);
			fprintf(output, " = ");
			genExpression(e->val.binary.rhs);
			fprintf(output, ";\n");
			break;
		}
		case STATEMENT_WHILE:
		{
			fprintf(output, "while (");
			genExpression(e->val.binary.lhs);
			fprintf(output, ")\n");
			tab();
			fprintf(output, "{\n");
			indent++;
			generate(e->val.binary.rhs);
			indent--;
			tab();
			fprintf(output, "}\n");
			break;
		}
		case STATEMENT_IF:
		{
			fprintf(output, "if (");
			genExpression(e->val.ternary.left);
			fprintf(output, ")\n");
			tab();
			fprintf(output, "{\n");
			indent++;
			generate(e->val.ternary.center);
			indent--;
			tab();
			fprintf(output, "}");
			if (e->val.ternary.right != NULL)
			{
				generate(e->val.ternary.right);
			} else
			{
				fprintf(output, "\n");
			}
			break;
		}
		case STATEMENT_ELSE_IF:
			fprintf(output, " else if (");
			genExpression(e->val.ternary.left);
			fprintf(output, ")\n");
			tab();
			fprintf(output, "{\n");
			indent++;
			generate(e->val.ternary.center);
			indent--;
			tab();
			fprintf(output, "}");
			if (e->val.ternary.right != NULL)
			{
				generate(e->val.ternary.right);
			} else
			{
				fprintf(output, "\n");
			}
			break;
		case STATEMENT_ELSE:
		{
			fprintf(output, " else\n");
			tab();
			fprintf(output, "{\n");
			indent++;
			generate(e->val.binary.lhs);
			indent--;
			tab();
			fprintf(output, "}\n");
			break;
		}
		case STATEMENT_LIST:
		{
			tab();
			generate(e->val.binary.lhs);
			generate(e->val.binary.rhs);
			break;
		}
		default:
			break;
	}
}

void codegen(EXP *e)
{
	output = fopen(filepath, "w");
	if (output == NULL)
	{
		fprintf(stderr, "Error: creating output file failed\n");
		fclose(output);
		exit(1);
	}

	//to guarantee proper tabs
	if (indent != 0) indent = 0;
	//begin program generation with proper headers
	const char *header = "typedef int bool;\n"
						 "#define True 1\n"
						 "#define False 0\n\n"
						 "#include <stdlib.h>\n"
						 "#include <stdio.h>\n"
						 "#include <string.h>\n\n";
	const char *boolScan = "bool scanBool()\n{\n"
						   "\tchar *buffer = (char *) malloc(sizeof(char) * 1024);\n"
						   "\tscanf(\"%s\", buffer);\n"
						   "\tif (strcmp(buffer, \"True\") == 0)\n\t{\n"
						   "\t\tfree(buffer);\n"
						   "\t\treturn True;\n"
						   "\t} else if (strcmp(buffer, \"False\") == 0)\n\t{\n"
						   "\t\tfree(buffer);\n"
						   "\t\treturn False;\n\t}\n"
						   "\tfree(buffer);\n"
						   "\tfprintf(stderr, \"Error: accepted boolean strings are \\\"True\\\" and \\\"False\\\"\\n\");\n"
						   "\texit(1);\n}\n\n";
	const char *cat = "char *cat(const char *s1, const char *s2)\n{\n"
					  "\tsize_t s1_length = (strlen(s1) + 1) * sizeof(char);\n"
					  "\tsize_t s2_length = (strlen(s2) + 1) * sizeof(char);\n"
					  "\tchar *buffer = (char *) malloc(s1_length + s2_length);\n"
					  "\tstrcpy(buffer, s1);\n"
					  "\tstrcat(buffer, s2);\n"
					  "\treturn buffer;\n}\n\n";
	const char *main = "int main()\n{\n";
	fprintf(output, "%s", header);
	fprintf(output, "%s", boolScan);
	fprintf(output, "%s", cat);
	fprintf(output, "%s", main);
	indent++;
	generate(e);
	indent--;
	fprintf(output, "}\n");
	fclose(output);
}

void tab()
{
	for (int i = 0; i < indent; i++)
	{
		fprintf(output, "\t");
	}
}
