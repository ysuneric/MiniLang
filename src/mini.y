// C code section
%{
//
//Eric Sun 2020
//260673824
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

extern int yylineno;
extern EXP *root;
int yylex();

void yyerror(const char *s) {
	fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
	exit(1);
}
%}

%code requires
{
	#include "tree.h"
}

%union {
	int intval;
	float floatval;
	char* identifier;
	struct EXP *exp;
}

//tokens
%token tINT tFLOAT tSTRING
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <identifier> tIDENTIFIER
%token <identifier> tSTRINGVAL
%token tBOOL tTRUE tFALSE
%token tIF tELSE tWHILE
%token tPRINT tREAD tVAR
%token tAND tOR tLT tLTE tGT tGTE tEQUAL tNE

//types for AST
%type <exp> StatementList Type Expression
%type <exp> Statement Conditional

//precedence ordering
%left tOR
%left tAND
%left tEQUAL tNE
%left tLT tGT tLTE tGTE
%left '+' '-'
%left '*' '/'
%left NEGATIVE '!'

//program grammar
%start Program

%locations
%define parse.error verbose

%%
Type:       tINT                                                                {$$ = new_intType();}
            | tFLOAT                                                            {$$ = new_floatType();}
            | tSTRING                                                           {$$ = new_stringType();}
            | tBOOL                                                             {$$ = new_boolType();}
            ;

Expression:    tIDENTIFIER                                                      {$$ = new_identifier($1);}
                | tSTRINGVAL                                                    {$$ = new_stringLiteral($1);}
                | tINTVAL                                                       {$$ = new_intLiteral($1);}
                | tFLOATVAL                                                     {$$ = new_floatLiteral($1);}
                | tTRUE                                                         {$$ = new_boolLiteral(true);}
                | tFALSE                                                        {$$ = new_boolLiteral(false);}
                | '!' Expression                                                {$$ = new_expNot($2);}
                | '(' Expression ')'                                            {$$ = $2;}
                | '-' Expression %prec NEGATIVE                                 {$$ = new_expNeg($2);}
                | Expression '+' Expression                                     {$$ = new_expAdd($1, $3);}
                | Expression '-' Expression                                     {$$ = new_expMinus($1, $3);}
                | Expression '*' Expression                                     {$$ = new_expTimes($1, $3);}
                | Expression '/' Expression                                     {$$ = new_expDivide($1, $3);}
                | Expression tEQUAL Expression                                  {$$ = new_expEqual($1, $3);}
                | Expression tNE Expression                                     {$$ = new_expNotEqual($1, $3);}
                | Expression tGTE Expression                                    {$$ = new_expGreaterEqual($1, $3);}
                | Expression tLTE Expression                                    {$$ = new_expLessEqual($1, $3);}
                | Expression tGT Expression                                     {$$ = new_expGreater($1, $3);}
                | Expression tLT Expression                                     {$$ = new_expLess($1, $3);}
                | Expression tAND Expression                                    {$$ = new_expAnd($1, $3);}
                | Expression tOR Expression                                     {$$ = new_expOr($1, $3);}
                ;

Statement:    tREAD '(' tIDENTIFIER ')' ';'                                     {$$ = new_read($3);}
                | tPRINT '(' Expression ')' ';'                                 {$$ = new_print($3);}
		        | tVAR tIDENTIFIER '=' Expression ';'                           {$$ = new_declaration(new_identifier($2), $4);}
		        | tVAR tIDENTIFIER ':' Type '=' Expression ';'                  {$$ = new_declarationType(new_identifier($2), $4, $6);}
                | tIDENTIFIER '=' Expression ';'                                {$$ = new_assign(new_identifier($1), $3);}
                | tWHILE '(' Expression ')' '{' StatementList '}'               {$$ = new_while($3, $6);}
                | tIF '(' Expression ')' '{' StatementList '}' Conditional      {$$ = new_if($3, $6, $8);}

Conditional:    tELSE tIF '(' Expression ')' '{' StatementList '}' Conditional  {$$ = new_elseIf($4, $7, $9);}
                | tELSE '{' StatementList '}'                                   {$$ = new_else($3);}
                | /* empty */                                                   {$$ = new_null();}
                ;

StatementList:    Statement StatementList                                       {$$ = new_statementList($1, $2);}
           	| /* empty */                                                       {$$ = new_null();}
           	;

Program:    StatementList                                                       {root = $1;}
            ;
%%
