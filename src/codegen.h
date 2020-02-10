//
// Eric Sun 2020
// 260673824
//

#ifndef CODEGEN_H
#define CODEGEN_H

#include "tree.h"
#include "symbol.h"

const char *filepath;

void genExpression(EXP *e);

void generate(EXP *e);

void codegen(EXP *e);

void tab();

#endif //CODEGEN_H
