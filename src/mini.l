%{
//
//Eric Sun 2020
//260673824
//

#include "parser.tab.h" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>

extern int g_tokens;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

/*options*/
%option yylineno
%option noinput
%option nounput

/*regex stuff here*/
%%
[ \t\r\n\f]+

"!"          { if (g_tokens) { printf("tNOT\n"); } return '!'; }
"&&"         { if (g_tokens) { printf("tAND\n"); } return tAND; }
"||"         { if (g_tokens) { printf("tOR\n"); } return tOR; }
"<"          { if (g_tokens) { printf("tLESS\n"); } return tLT; }
"<="         { if (g_tokens) { printf("tLESSEQUALS\n"); } return tLTE; }
">"          { if (g_tokens) { printf("tGREATER\n"); } return tGT; }
">="         { if (g_tokens) { printf("tGREATEREQUALS\n"); } return tGTE; }
"=="         { if (g_tokens) { printf("tEQUALS\n"); } return tEQUAL; }
"!="         { if (g_tokens) { printf("tNOTEQUALS\n"); } return tNE; }
"="          { if (g_tokens) { printf("tASSIGN\n"); } return '='; }

"+"          { if (g_tokens) { printf("tADD\n"); } return '+'; }
"-"          { if (g_tokens) { printf("tSUB\n"); } return '-'; }
"*"          { if (g_tokens) { printf("tMULT\n"); } return '*'; }
"/"          { if (g_tokens) { printf("tDIV\n"); } return '/'; }
"("          { if (g_tokens) { printf("tLEFTPAREN\n"); } return '('; }
")"          { if (g_tokens) { printf("tRIGHTPAREN\n"); } return ')'; }
"{"          { if (g_tokens) { printf("tLEFTBRACE\n"); } return '{'; }
"}"          { if (g_tokens) { printf("tRIGHTBRACE\n"); } return '}'; }
":"          { if (g_tokens) { printf("tCOLON\n"); } return ':'; }
";"          { if (g_tokens) { printf("tSEMICOLON\n"); } return ';'; }

"int"        { if (g_tokens) { printf("tINT\n"); } return tINT; }
"float"      { if (g_tokens) { printf("tFLOAT\n"); } return tFLOAT; }
"string"     { if (g_tokens) { printf("tSTRING\n"); } return tSTRING; }
"bool"       { if (g_tokens) { printf("tBOOL\n"); } return tBOOL; }
"True"       { if (g_tokens) { printf("tTRUE\n"); } return tTRUE; }
"False"      { if (g_tokens) { printf("tFALSE\n"); } return tFALSE; }
"if"         { if (g_tokens) { printf("tIF\n"); } return tIF; }
"else"       { if (g_tokens) { printf("tELSE\n"); } return tELSE; }
"while"      { if (g_tokens) { printf("tWHILE\n"); } return tWHILE; }
"print"      { if (g_tokens) { printf("tPRINT\n"); } return tPRINT; }
"read"       { if (g_tokens) { printf("tREAD\n"); } return tREAD; }
"var"        { if (g_tokens) { printf("tVAR\n"); } return tVAR; }

0|([1-9][0-9]*) { /*integers*/
	yylval.intval = atoi(yytext);
	if (g_tokens) { printf("tINTVAL(%i)\n", yylval.intval); }
	return tINTVAL;
}
0[0]+[0-9]* { /*integers with leading zeroes*/
    fprintf(stderr, "Error: (line %d) invalid integer \'%s\'\n", yylineno, yytext);
    exit(1);
}

(0|[1-9][0-9]*)\.[0-9]+ { /*integer followed by one . followed by one or more values*/
    yylval.floatval = atof(yytext);
    if (g_tokens) { printf("tFLOATVAL(%f)\n", yylval.floatval); }
    return tFLOATVAL;
}
(\.[0-9]+)|([0-9]+\.)|(0[0-9]+\.[0-9]*) { //invalid float
    fprintf(stderr, "Error: (line %d) invalid float \'%s\'\n", yylineno, yytext);
    exit(1);
}

[a-zA-Z_]{1}[a-zA-Z0-9_]* { /*variable names*/
	yylval.identifier = strdup(yytext);
    if (g_tokens) { printf("tIDENTIFIER(%s)\n", yylval.identifier); }
	return tIDENTIFIER;
}
\"[^\"]*\" { /*match any nonempty string*/
    yylval.identifier = strdup(yytext);
    if (g_tokens) { printf("tSTRINGVAL(%s)\n", yylval.identifier); }
    return tSTRINGVAL;
}
#(.)* { /*do nothing for comments*/ }

. 	{ fprintf(stderr, "Error: (line %d) unexpected character \'%s\'\n", yylineno, yytext); exit(1); }

%%
