%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  int yycoluno = 1;
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
"\n"      { yycoluno = 1; }
"."       { yylval.keyword_value = "DOT"; return DOT; }
";"       { yylval.keyword_value = "SEMI"; return SEMI; }
","       { yylval.keyword_value = "COMMA"; return COMMA; }
"="       { yylval.keyword_value = "ASSIGN"; return ASSIGN; }
"<"       { yylval.keyword_value = "LT"; return LT; }
">"       { yylval.keyword_value = "GT"; return GT; }
"+"       { yylval.keyword_value = "PLUS"; return PLUS; }
"-"       { yylval.keyword_value = "MINUS"; return MINUS; }
"*"       { yylval.keyword_value = "MUL"; return MUL; }
"/"       { yylval.keyword_value = "DIV"; return DIV; }
"!"       { yylval.keyword_value = "NOT"; return NOT; }
"("       { yylval.keyword_value = "LP"; return LP; }
")"       { yylval.keyword_value = "RP"; return RP; }
"["       { yylval.keyword_value = "LB"; return LB; }
"]"       { yylval.keyword_value = "RB"; return RB; }
"{"       { yylval.keyword_value = "LC"; return LC; }
"}"       { yylval.keyword_value = "RC"; return RC; }
"<="      { yylval.keyword_value = "LE"; return LE; }
">="      { yylval.keyword_value = "GE"; return GE; }
"!="      { yylval.keyword_value = "NE"; return NE; }
"=="      { yylval.keyword_value = "EQ"; return EQ; }
"&&"      { yylval.keyword_value = "AND"; return AND; }
"||"      { yylval.keyword_value = "OR"; return OR; }

"//"      { char c; while ((c=input()) != '\n'); }

"struct"  { yylval.keyword_value = "STRUCT"; return STRUCT; }
"if"      { yylval.keyword_value = "IF"; return IF; }
"else"    { yylval.keyword_value = "ELSE"; return ELSE; }
"while"   { yylval.keyword_value = "WHILE"; return WHILE; }
"return"  { yylval.keyword_value = "RETURN"; return RETURN; }

{INT}     { yylval.int_value = atoi(yytext); return INT; }
{FLOAT}   { yylval.float_value = atof(yytext); return FLOAT; }
{CHAR}    { yylval.char_value = yytext[0]; return CHAR; }
{TYPE}    { yylval.type_value = strdup(yytext); return TYPE; }
{ID}      { yylval.id_value = strdup(yytext); return ID; }

.         {
  printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
    yylineno, yytext);
}

%%

