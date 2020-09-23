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
"."       { return DOT; }
";"       { return SEMI; }
","       { return COMMA; }
"="       { return ASSIGN; }
"<"       { return LT; }
">"       { return GT; }
"+"       { return PLUS; }
"-"       { return MINUS; }
"*"       { return MUL; }
"/"       { return DIV; }
"!"       { return NOT; }
"("       { return LP; }
")"       { return RP; }
"["       { return LB; }
"]"       { return RB; }
"{"       { return LC; }
"}"       { return RC; }
"<="      { return LE; }
">="      { return GE; }
"!="      { return NE; }
"=="      { return EQ; }
"&&"      { return AND; }
"||"      { return OR; }

"//"      { char c; while ((c=input()) != '\n'); }

"struct"  { return STRUCT; }
"if"      { return IF; }
"else"    { return ELSE; }
"while"   { return WHILE; }
"return"  { return RETURN; }

{INT}     { yylval.int_value = atoi(yytext); return INT; }
{FLOAT}   { yylval.float_value = atof(yytext); return FLOAT; }
{CHAR}    { yylval.char_value = yytext[0]; return CHAR; }
{TYPE}    { yylval.str_value = strdup(yytext); return TYPE; }
{ID}      { yylval.str_value = strdup(yytext); return ID; }

.         {
  printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
    yylineno, yytext);
}

%%

