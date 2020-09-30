%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  int yycoluno = 1;
  extern YYLTYPE yylloc;

  // #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycoluno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycoluno + yyleng; \
    yycoluno += yyleng;
%}

%option yylineno

SPC     [ \t\r\f\v]
INT     -?[1-9][0-9]{0,9}|-?0[xX][1-9a-fA-F][0-9a-fA-F]*
FLOAT   -?[1-9][0-9]*\.[0-9]+
CHAR    \'[a-zA-Z]\'|\\x[1-9a-fA-F][0-9a-fA-F]*
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][a-zA-Z0-9_]{0,31}

%%

{SPC}     { /* whitespace characters, do nothing */ }
"\n"      { printf("flex: found new line\n"); yycoluno = 1; }
"."       { printf("flex: found DOT\n"); yylval.keyword_value = "DOT"; return DOT; }
";"       { printf("flex: found SEMI\n"); yylval.keyword_value = "SEMI"; return SEMI; }
","       { printf("flex: found COMMA\n"); yylval.keyword_value = "COMMA"; return COMMA; }
"="       { printf("flex: found ASSIGN\n"); yylval.keyword_value = "ASSIGN"; return ASSIGN; }
"<"       { printf("flex: found LT\n"); yylval.keyword_value = "LT"; return LT; }
">"       { printf("flex: found GT\n"); yylval.keyword_value = "GT"; return GT; }
"+"       { printf("flex: found PLUS\n"); yylval.keyword_value = "PLUS"; return PLUS; }
"-"       { printf("flex: found MINUS\n"); yylval.keyword_value = "MINUS"; return MINUS; }
"*"       { printf("flex: found MUL\n"); yylval.keyword_value = "MUL"; return MUL; }
"/"       { printf("flex: found DIV\n"); yylval.keyword_value = "DIV"; return DIV; }
"!"       { printf("flex: found NOT\n"); yylval.keyword_value = "NOT"; return NOT; }
"("       { printf("flex: found LP\n"); yylval.keyword_value = "LP"; return LP; }
")"       { printf("flex: found RP\n"); yylval.keyword_value = "RP"; return RP; }
"["       { printf("flex: found LB\n"); yylval.keyword_value = "LB"; return LB; }
"]"       { printf("flex: found RB\n"); yylval.keyword_value = "RB"; return RB; }
"{"       { printf("flex: found LC\n"); yylval.keyword_value = "LC"; return LC; }
"}"       { printf("flex: found RC\n"); yylval.keyword_value = "RC"; return RC; }
"<="      { printf("flex: found LE\n"); yylval.keyword_value = "LE"; return LE; }
">="      { printf("flex: found GE\n"); yylval.keyword_value = "GE"; return GE; }
"!="      { printf("flex: found NE\n"); yylval.keyword_value = "NE"; return NE; }
"=="      { printf("flex: found EQ\n"); yylval.keyword_value = "EQ"; return EQ; }
"&&"      { printf("flex: found AND\n"); yylval.keyword_value = "AND"; return AND; }
"||"      { printf("flex: found OR\n"); yylval.keyword_value = "OR"; return OR; }

"struct"  { printf("flex: found STRUCT\n"); yylval.keyword_value = "STRUCT"; return STRUCT; }
"if"      { printf("flex: found IF\n"); yylval.keyword_value = "IF"; return IF; }
"else"    { printf("flex: found ELSE\n"); yylval.keyword_value = "ELSE"; return ELSE; }
"while"   { printf("flex: found WHILE\n"); yylval.keyword_value = "WHILE"; return WHILE; }
"return"  { printf("flex: found RETURN\n"); yylval.keyword_value = "RETURN"; return RETURN; }

{INT}     {
            if (yytext[0] == '0' && yytext[1] == 'x') {
              yylval.int_value = strtol(yytext, NULL, 0);
            } else {
              yylval.int_value = atoi(yytext); 
            }
            return INT;
          }
{FLOAT}   { yylval.float_value = atof(yytext); return FLOAT; }
{CHAR}    {
            if (yytext[0] == '\'' && yytext[yyleng - 1] == '\'') {
              yylval.char_value = yytext[1];
            } else {
              yytext[0] = '0';
              yylval.char_value = strtol(yytext, NULL, 0);
            }
            return CHAR;
          }
{TYPE}    { yylval.type_value = strdup(yytext); return TYPE; }
{ID}      { yylval.id_value = strdup(yytext); return ID; }

.         {
            printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
              yylineno, yytext);
          }

%%

