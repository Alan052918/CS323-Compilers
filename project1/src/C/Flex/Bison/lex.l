%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  int yycoluno = 1;

  #define YY_USER_ACTION \
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

{SPC} { /* whitespace characters, do nothing */ }
"\n"  {
        printf("flex: found new line, line %d\n", yylineno - 1);
        yycoluno = 1;
      }
"."   {
        printf("flex: found DOT, line %d\n", yylineno);
        yylval.keyword_value = "DOT";
        return DOT;
      }
";"   {
        printf("flex: found SEMI, line %d\n", yylineno);
        yylval.keyword_value = "SEMI";
        return SEMI;
      }
","   {
        printf("flex: found COMMA, line %d\n", yylineno);
        yylval.keyword_value = "COMMA";
        return COMMA;
      }
"="   {
        printf("flex: found ASSIGN, line %d\n", yylineno);
        yylval.keyword_value = "ASSIGN";
        return ASSIGN;
      }
"<"   {
        printf("flex: found LT, line %d\n", yylineno);
        yylval.keyword_value = "LT";
        return LT;
      }
">"   {
        printf("flex: found GT, line %d\n", yylineno);
        yylval.keyword_value = "GT";
        return GT;
      }
"+"   {
        printf("flex: found PLUS, line %d\n", yylineno);
        yylval.keyword_value = "PLUS";
        return PLUS;
      }
"-"   {
        printf("flex: found MINUS, line %d\n", yylineno);
        yylval.keyword_value = "MINUS";
        return MINUS;
      }
"*"   {
        printf("flex: found MUL, line %d\n", yylineno);
        yylval.keyword_value = "MUL";
        return MUL;
      }
"/"   {
        printf("flex: found DIV, line %d\n", yylineno);
        yylval.keyword_value = "DIV";
        return DIV;
      }
"!"   {
        printf("flex: found NOT, line %d\n", yylineno);
        yylval.keyword_value = "NOT";
        return NOT;
      }
"("   {
        printf("flex: found LP, line %d\n", yylineno);
        yylval.keyword_value = "LP";
        return LP;
      }
")"   {
        printf("flex: found RP, line %d\n", yylineno);
        yylval.keyword_value = "RP";
        return RP;
      }
"["   {
        printf("flex: found LB, line %d\n", yylineno);
        yylval.keyword_value = "LB";
        return LB;
      }
"]"   {
        printf("flex: found RB, line %d\n", yylineno);
        yylval.keyword_value = "RB";
        return RB;
      }
"{"   {
        printf("flex: found LC, line %d\n", yylineno);
        yylval.keyword_value = "LC";
        return LC;
      }
"}"   {
        printf("flex: found RC, line %d\n", yylineno);
        yylval.keyword_value = "RC";
        return RC;
      }
"<="  {
        printf("flex: found LE, line %d\n", yylineno);
        yylval.keyword_value = "LE";
        return LE;
      }
">="  {
        printf("flex: found GE, line %d\n", yylineno);
        yylval.keyword_value = "GE";
        return GE;
      }
"!="  {
        printf("flex: found NE, line %d\n", yylineno);
        yylval.keyword_value = "NE";
        return NE;
      }
"=="  {
        printf("flex: found EQ, line %d\n", yylineno);
        yylval.keyword_value = "EQ";
        return EQ;
      }
"&&"  {
        printf("flex: found AND, line %d\n", yylineno);
        yylval.keyword_value = "AND";
        return AND;
      }
"||"  {
        printf("flex: found OR, line %d\n", yylineno);
        yylval.keyword_value = "OR";
        return OR;
      }

"struct"  {
            printf("flex: found STRUCT, line %d\n", yylineno);
            yylval.keyword_value = "STRUCT";
            return STRUCT;
          }
"if"  {
        printf("flex: found IF, line %d\n", yylineno);
        yylval.keyword_value = "IF";
        return IF;
      }
"else"  {
          printf("flex: found ELSE, line %d\n", yylineno);
          yylval.keyword_value = "ELSE";
          return ELSE;
        }
"while" {
          printf("flex: found WHILE, line %d\n", yylineno);
          yylval.keyword_value = "WHILE";
          return WHILE;
        }
"return"  {
            printf("flex: found RETURN, line %d\n", yylineno);
            yylval.keyword_value = "RETURN";
            return RETURN;
          }

{INT} {
        if (yytext[0] == '0' && yytext[1] == 'x') {
          yylval.int_value = strtol(yytext, NULL, 0);
        } else {
          yylval.int_value = atoi(yytext);
        }
        printf("flex: found INT %ld, line %d\n", yylval.int_value, yylineno);
        return INT;
      }
{FLOAT} {
          yylval.float_value = atof(yytext);
          printf("flex: found FLOAT %f, line %d\n", yylval.float_value, yylineno);
          return FLOAT;
        }
{CHAR}  {
          if (yytext[0] == '\'' && yytext[yyleng - 1] == '\'') {
            yylval.char_value = yytext[1];
          } else {
            yytext[0] = '0';
            yylval.char_value = strtol(yytext, NULL, 0);
          }
          printf("flex: found CHAR %c, line %d\n", yylval.char_value, yylineno);
          return CHAR;
        }
{TYPE}  {
          yylval.type_value = strdup(yytext);
          printf("flex: found TYPE %s, line %d\n", yylval.type_value, yylineno);
          return TYPE;
        }
{ID}  {
        yylval.id_value = strdup(yytext);
        printf("flex: found ID %s, line %d\n", yylval.id_value, yylineno);
        return ID;
      }

. {
    printf("Error type A at Line %d: Unknown characters \'%s\'\n",
      yylineno, yytext);
  }

%%
