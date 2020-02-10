//
//Eric Sun 2020
//260673824
//

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "pretty.h"
#include "symbol.h"
#include "type.h"
#include "codegen.h"

int g_tokens = 0;
int g_symbols = 0;
EXP *root;
SymbolTable *table;

void yyparse();

int yylex();

void scan(int mode);

void toC(const char *source);

int main(int argc, char *argv[])
{
	//scanning step
	if (strcmp(argv[1], "scan") == 0)
	{
		scan(0);
		printf("OK\n");
		return 0;
	} else if (strcmp(argv[1], "tokens") == 0)
	{
		scan(1);
		return 0;
	}

	//parsing step
	yyparse();

	if (strcmp(argv[1], "parse") == 0)
	{
		printf("OK\n");
		return 0;
	} else if (strcmp(argv[1], "pretty") == 0)
	{
		prettyEXP(root);
		return 0;
	}

	//symbol table step
	table = initSymbolTable();

	if (strcmp(argv[1], "symbol") == 0)
	{
		g_symbols = 1;
		generateTable(table, root);
		return 0;
	}

	g_symbols = 0;
	generateTable(table, root);

	//typechecking step
	typeCheck(root);
	if (strcmp(argv[1], "typecheck") == 0)
	{
		printf("OK\n");
		return 0;
	}

	//codegen step
	if (strcmp(argv[1], "codegen") == 0)
	{
		toC(argv[2]);
		codegen(root);
		printf("OK\n");
		return 0;
	}
	fprintf(stderr, "Error: main call failed\n");
	return 1;
}

void scan(int mode)
{
	g_tokens = mode;
	while (yylex())
	{
		//loops until all tokens are read
	}
}

void toC(const char *source)
{
	//retrieve and parse the new file path
	char *temp = (char *) malloc(sizeof(char) * 1024);
	size_t length = strlen(source);
	memcpy(temp, source, length - 4);
	filepath = strncat(temp, ".c", 2);
	free(temp);
}
