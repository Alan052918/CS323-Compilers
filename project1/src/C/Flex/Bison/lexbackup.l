%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  int yycolno = 1;
%}

%option yylineno

SPC     [ \t\r\f\v]
INT     -?[0-9][0-9]*|-?0[xX][0-9a-fA-F][0-9a-fA-F]*
FLOAT   -?[0-9]+\.[0-9]+
CHAR    \'[a-zA-Z]\'|\'\\x[0-9a-fA-F]+\'
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][a-zA-Z0-9_]{0,31}

%%

{SPC}     { /* whitespace characters, do nothing */ }
"\n"      { yycolno = 1; yylineno++; }
"."       { printf("DOT\n"); return DOT; }
";"       { printf("SEMI\n"); return SEMI; }
","       { printf("COMMA\n"); return COMMA; }
"="       { printf("ASSIGN\n"); return ASSIGN; }
"<"       { printf("LT\n"); return LT; }
">"       { printf("GT\n"); return GT; }
"+"       { printf("PLUS\n"); return PLUS; }
"-"       { printf("MINUS\n"); return MINUS; }
"*"       { printf("MUL\n"); return MUL; }
"/"       { printf("DIV\n"); return DIV; }
"!"       { printf("NOT\n"); return NOT; }
"("       { printf("LP\n"); return LP; }
")"       { printf("RP\n"); return RP; }
"["       { printf("LB\n"); return LB; }
"]"       { printf("RB\n"); return RB; }
"{"       { printf("LC\n"); return LC; }
"}"       { printf("RC\n"); return RC; }
"<="      { printf("LE\n"); return LE; }
">="      { printf("GE\n"); return GE; }
"!="      { printf("NE\n"); return NE; }
"=="      { printf("EQ\n"); return EQ; }
"&&"      { printf("AND\n"); return AND; }
"||"      { printf("OR\n"); return OR; }

"//"      { char c; while ((c=input()) != '\n'); }

"struct"  { printf("STRUCT\n"); return STRUCT; }
"if"      { printf("IF\n"); return IF; }
"else"    { printf("ELSE\n"); return ELSE; }
"while"   { printf("WHILE\n"); return WHILE; }
"return"  { printf("RETURN\n"); return RETURN; }

{INT}     { printf("INT\n"); yylval.int_value = atoi(yytext); return INT; }
{FLOAT}   { printf("FLOAT\n"); yylval.float_value = atof(yytext); return FLOAT; }
{CHAR}    { printf("CHAR\n"); yylval.char_value = yytext[0]; return CHAR; }
{TYPE}    { printf("TYPE\n"); yylval.str_value = strdup(yytext); return TYPE; }
{ID}      { printf("ID\n"); yylval.str_value = strdup(yytext); return ID; }

.         {
  printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
    yylineno, yytext);
}

%%

