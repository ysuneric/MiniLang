//
// Eric Sun 2020
// 260673824
//

#ifndef SYMBOL_H
#define SYMBOL_H

#define HashSize 317

#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef enum Type
{
	INFER,
	STRING,
	INT,
	FLOAT,
	BOOL,
	INVALID
} Type;

typedef struct SYMBOL
{
	char *name;
	Type kind;
	struct SYMBOL *next;
} SYMBOL;

typedef struct SymbolTable
{
	SYMBOL *table[HashSize];
	struct SymbolTable *parent;
} SymbolTable;

int Hash(char *str);

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *s);

SYMBOL *getSymbol(SymbolTable *t, char *name);

SYMBOL *putSymbol(SymbolTable *t, char *name, Type kind);

void generateTable(SymbolTable *table, EXP *tree);

bool isDeclared(SymbolTable *t, char *name);

void printSym(SymbolTable *t, char *name);

void tabUp(SymbolTable *t);

#endif //SYMBOL_H
