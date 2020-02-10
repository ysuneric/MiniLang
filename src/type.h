//
// Eric Sun 2020
// 260673824
//

#ifndef TYPE_H
#define TYPE_H

#include "tree.h"
#include "symbol.h"

char *toString(Type t);

Type typeAdd(Type t, Type t2);

Type typeMath(Type t, Type t2);

Type typeCompare(Type t, Type t2);

Type typeAssign(EXP *e);

Type typeExpression(EXP *e);

Type typeDeclaration(EXP *e);

void typeCheck(EXP *e);

#endif //TYPE_H
