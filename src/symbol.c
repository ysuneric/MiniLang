//
// Eric Sun 2020
// 260673824
//

#include <string.h>
#include <stdio.h>
#include "symbol.h"
#include "tree.h"

extern int yylineno;
extern int g_symbols;

int Hash(char *str)
{
	unsigned int hash = 0;
	while (*str) hash = (hash << 1) + *str++;
	return hash % HashSize;
}

SymbolTable *initSymbolTable()
{
	SymbolTable *t = malloc(sizeof(SymbolTable));
	for (int i = 0; i < HashSize; i++)
	{
		t->table[i] = NULL;
	}
	t->parent = NULL;
	return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{
	SymbolTable *t = initSymbolTable();
	t->parent = s;
	return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, Type kind)
{
	int i = Hash(name);
	for (SYMBOL *s = t->table[i]; s; s = s->next)
	{
		if (strcmp(s->name, name) == 0) // throw an error
		{
			fprintf(stderr, "Error: (line %d) variable \"%s\"is already declared\n", yylineno, name);
			exit(1);
		}
	}
	SYMBOL *s = malloc(sizeof(SYMBOL));
	s->name = name;
	s->kind = kind;
	s->next = t->table[i];
	t->table[i] = s;
	return s;
}

SYMBOL *getSymbol(SymbolTable *t, char *name)
{
	int i = Hash(name);
	for (SYMBOL *s = t->table[i]; s; s = s->next)
	{
		if (strcmp(s->name, name) == 0)
		{
			return s;
		}
	}
	if (t->parent == NULL) return NULL;
	return getSymbol(t->parent, name);
}

bool isDeclared(SymbolTable *t, char *name)
{
	int i = Hash(name);
	for (SYMBOL *s = t->table[i]; s; s = s->next)
	{
		if (strcmp(s->name, name) == 0)
		{
			return true;
		}
	}
	return false;
}

void generateTable(SymbolTable *table, EXP *root)
{
	if (root == NULL) return;
	switch (root->kind)
	{
		case DECLARATION:
		{
			EXP *id = root->val.binary.lhs;
			if (isDeclared(table, id->val.idE.name))
			{
				fprintf(stderr, "Error: (line %d) \"%s\" is already declared\n", yylineno, id->val.idE.name);
				exit(1);
			}
			putSymbol(table, id->val.idE.name, INFER);
			id->val.idE.idsym = getSymbol(table, id->val.idE.name);
			if (g_symbols) printSym(table, id->val.idE.name);
			generateTable(table, root->val.binary.rhs);
			break;
		}
		case DECLARATION_TYPE:
		{
			EXP *id = root->val.ternary.left;
			EXP *typeBranch = root->val.ternary.center;
			if (isDeclared(table, id->val.idE.name))
			{
				fprintf(stderr, "Error: (line %d) \"%s\" is already declared\n", yylineno, id->val.idE.name);
				exit(1);
			}
			Type type;
			switch (typeBranch->kind)
			{
				case INT_TYPE:
					type = INT;
					break;
				case FLOAT_TYPE:
					type = FLOAT;
					break;
				case BOOL_TYPE:
					type = BOOL;
					break;
				case STRING_TYPE:
					type = STRING;
					break;
				default:
					type = INFER;
			}
			putSymbol(table, id->val.idE.name, type);
			id->val.idE.idsym = getSymbol(table, id->val.idE.name);
			if (g_symbols) printSym(table, id->val.idE.name);
			generateTable(table, root->val.ternary.right);
			break;
		}
		case IDENTIFIER:
		{
			SYMBOL *symbol = getSymbol(table, root->val.idE.name);
			if (symbol == NULL)
			{
				fprintf(stderr, "Error: (line %d) \"%s\" is not declared\n", yylineno, root->val.idE.name);
				exit(1);
			}
			root->val.idE.idsym = symbol;
			break;
		}
		case EXPRESSION_ADD:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_MINUS:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_TIMES:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_DIVIDE:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_NEG:
			generateTable(table, root->val.binary.lhs);
			break;
		case EXPRESSION_EQUAL:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_NE:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_LTE:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_LT:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_GTE:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_GT:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_AND:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_OR:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		case EXPRESSION_NOT:
			generateTable(table, root->val.binary.lhs);
			break;
		case STATEMENT_READ:
		{
			SYMBOL *symbol = getSymbol(table, root->val.idE.name);
			if (symbol == NULL)
			{
				fprintf(stderr, "Error: (line %d) \"%s\" is not declared\n", yylineno, root->val.idE.name);
				exit(1);
			}
			root->val.idE.idsym = symbol;
			break;
		}
		case STATEMENT_PRINT:
			generateTable(table, root->val.binary.lhs);
			break;
		case STATEMENT_ASSIGN:
		{
			EXP *id = root->val.binary.lhs;
			SYMBOL *symbol = getSymbol(table, id->val.idE.name);
			if (symbol == NULL)
			{
				fprintf(stderr, "Error: (line %d) \"%s\" is not declared\n", yylineno, id->val.idE.name);
				exit(1);
			}
			id->val.idE.idsym = symbol;
			generateTable(table, root->val.binary.rhs);
			break;
		}
		case STATEMENT_WHILE:
			generateTable(table, root->val.binary.lhs);
			if (g_symbols)
			{
				tabUp(table);
				printf("{\n");
			}
			generateTable(scopeSymbolTable(table), root->val.binary.rhs);
			if (g_symbols)
			{
				tabUp(table);
				printf("}\n");
			}
			break;
		case STATEMENT_IF:
			generateTable(table, root->val.ternary.left);
			if (g_symbols)
			{
				tabUp(table);
				printf("{\n");
			}
			generateTable(scopeSymbolTable(table), root->val.ternary.center);
			if (g_symbols)
			{
				tabUp(table);
				printf("}\n");
			}
			generateTable(table, root->val.ternary.right);
			break;
		case STATEMENT_ELSE_IF:
			generateTable(table, root->val.ternary.left);
			if (g_symbols)
			{
				tabUp(table);
				printf("{\n");
			}
			generateTable(scopeSymbolTable(table), root->val.ternary.center);
			if (g_symbols)
			{
				tabUp(table);
				printf("}\n");
			}
			generateTable(table, root->val.ternary.right);
			break;
		case STATEMENT_ELSE:
			if (g_symbols)
			{
				tabUp(table);
				printf("{\n");
			}
			generateTable(scopeSymbolTable(table), root->val.binary.lhs);
			if (g_symbols)
			{
				tabUp(table);
				printf("}\n");
			}
			break;
		case STATEMENT_LIST:
			generateTable(table, root->val.binary.lhs);
			generateTable(table, root->val.binary.rhs);
			break;
		default:
			break;
	}
}

void printSym(SymbolTable *table, char *name)
{
	SYMBOL *symbol = getSymbol(table, name);
	tabUp(table);
	printf("%s: ", symbol->name);
	switch (symbol->kind)
	{
		case INT:
			printf("int\n");
			break;
		case FLOAT:
			printf("float\n");
			break;
		case BOOL:
			printf("bool\n");
			break;
		case STRING:
			printf("string\n");
			break;
		case INFER:
			printf("<infer>\n");
			break;
		default:
			break;
	}
}

void tabUp(SymbolTable *table)
{
	while (table->parent != NULL)
	{
		table = table->parent;
		printf("\t");
	}
}
