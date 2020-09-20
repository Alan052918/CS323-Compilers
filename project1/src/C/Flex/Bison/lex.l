%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  int yycolno = 1;

  #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycolno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycolno + yyleng; \
    yycolno += yyleng;
%}

%option yylineno

SPC     [ \t\r\f\v]
INT     -?[0-9][0-9]*|[-+]?0[xX][0-9a-fA-F][0-9a-fA-F]*
FLOAT   -?[0-9]+\.[0-9]+
CHAR    \'[a-zA-Z]\'|\'\\x[0-9a-fA-F]+\'
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

{SPC}     { /* whitespace characters, do nothing */ }
"\n"      { yycolno = 1; }
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

{INT}     { yylval = atoi(yytext); return INT; }
{FLOAT}   { yylval = atof(yytext); return FLOAT; }
{CHAR}    { yylval = yytext; return CHAR; }
{TYPE}    { yylval = yytext; return TYPE; }
{ID}      { yylval = yytext; return ID; }

.         {
  printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
    yylineno, yytext);
}

%%

int main(int argc, char **argv) {
  char *file_name;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    return EXIT_FAILURE;
  } else if (argc == 2) {
    file_name = argv[1];
    if (!(yyin = fopen(file_name, "r"))) {
      perror(argv[1]);
      return EXIT_FAILURE;
    }
    yylex();
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
