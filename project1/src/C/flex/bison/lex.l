%{
  #include <stdlib.h>
  #include "syntax.tab.h"

  #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycoluno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycoluno + yyleng; \
    yycoluno += yyleng;
    
  int yycoluno = 1;
%}

%option yylineno

SPC     [ \t\r\f\v]
INT     0|-?[1-9][0-9]{0,9}|-?0[xX][1-9a-fA-F][0-9a-fA-F]*
FLOAT   -?[1-9][0-9]*\.[0-9]+
CHAR    \'[a-zA-Z]\'|\\x[1-9a-fA-F][0-9a-fA-F]*
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][a-zA-Z0-9_]{0,31}

%%

{SPC} { /* whitespace characters, do nothing */ }
"\n"  {
#ifdef DEBUG
        printf("flex: found new line, line %d\n", yylineno - 1);
#endif
        yycoluno = 1;
      }
"."   {
#ifdef DEBUG
        printf("flex: found DOT, line %d\n", yylineno);
#endif
        yylval.keyword_value = "DOT";
        return DOT;
      }
";"   {
#ifdef DEBUG
        printf("flex: found SEMI, line %d\n", yylineno);
#endif
        yylval.keyword_value = "SEMI";
        return SEMI;
      }
","   {
#ifdef DEBUG
        printf("flex: found COMMA, line %d\n", yylineno);
#endif
        yylval.keyword_value = "COMMA";
        return COMMA;
      }
"="   {
#ifdef DEBUG
        printf("flex: found ASSIGN, line %d\n", yylineno);
#endif
        yylval.keyword_value = "ASSIGN";
        return ASSIGN;
      }
"<"   {
#ifdef DEBUG
        printf("flex: found LT, line %d\n", yylineno);
#endif
        yylval.keyword_value = "LT";
        return LT;
      }
">"   {
#ifdef DEBUG
        printf("flex: found GT, line %d\n", yylineno);
#endif
        yylval.keyword_value = "GT";
        return GT;
      }
"+"   {
#ifdef DEBUG
        printf("flex: found PLUS, line %d\n", yylineno);
#endif
        yylval.keyword_value = "PLUS";
        return PLUS;
      }
"-"   {
#ifdef DEBUG
        printf("flex: found MINUS, line %d\n", yylineno);
#endif
        yylval.keyword_value = "MINUS";
        return MINUS;
      }
"*"   {
#ifdef DEBUG
        printf("flex: found MUL, line %d\n", yylineno);
#endif
        yylval.keyword_value = "MUL";
        return MUL;
      }
"/"   {
#ifdef DEBUG
        printf("flex: found DIV, line %d\n", yylineno);
#endif
        yylval.keyword_value = "DIV";
        return DIV;
      }
"!"   {
#ifdef DEBUG
        printf("flex: found NOT, line %d\n", yylineno);
#endif
        yylval.keyword_value = "NOT";
        return NOT;
      }
"("   {
#ifdef DEBUG
        printf("flex: found LP, line %d\n", yylineno);
#endif
        yylval.keyword_value = "LP";
        return LP;
      }
")"   {
#ifdef DEBUG
        printf("flex: found RP, line %d\n", yylineno);
#endif
        yylval.keyword_value = "RP";
        return RP;
      }
"["   {
#ifdef DEBUG
        printf("flex: found LB, line %d\n", yylineno);
#endif
        yylval.keyword_value = "LB";
        return LB;
      }
"]"   {
#ifdef DEBUG
        printf("flex: found RB, line %d\n", yylineno);
#endif
        yylval.keyword_value = "RB";
        return RB;
      }
"{"   {
#ifdef DEBUG
        printf("flex: found LC, line %d\n", yylineno);
#endif
        yylval.keyword_value = "LC";
        return LC;
      }
"}"   {
#ifdef DEBUG
        printf("flex: found RC, line %d\n", yylineno);
#endif
        yylval.keyword_value = "RC";
        return RC;
      }
"<="  {
#ifdef DEBUG
        printf("flex: found LE, line %d\n", yylineno);
#endif
        yylval.keyword_value = "LE";
        return LE;
      }
">="  {
#ifdef DEBUG
        printf("flex: found GE, line %d\n", yylineno);
#endif
        yylval.keyword_value = "GE";
        return GE;
      }
"!="  {
#ifdef DEBUG
        printf("flex: found NE, line %d\n", yylineno);
#endif
        yylval.keyword_value = "NE";
        return NE;
      }
"=="  {
#ifdef DEBUG
        printf("flex: found EQ, line %d\n", yylineno);
#endif
        yylval.keyword_value = "EQ";
        return EQ;
      }
"&&"  {
#ifdef DEBUG
        printf("flex: found AND, line %d\n", yylineno);
#endif
        yylval.keyword_value = "AND";
        return AND;
      }
"||"  {
#ifdef DEBUG
        printf("flex: found OR, line %d\n", yylineno);
#endif
        yylval.keyword_value = "OR";
        return OR;
      }

"struct"  {
#ifdef DEBUG
            printf("flex: found STRUCT, line %d\n", yylineno);
#endif
            yylval.keyword_value = "STRUCT";
            return STRUCT;
          }
"if"  {
#ifdef DEBUG
        printf("flex: found IF, line %d\n", yylineno);
#endif
        yylval.keyword_value = "IF";
        return IF;
      }
"else"  {
#ifdef DEBUG
          printf("flex: found ELSE, line %d\n", yylineno);
#endif
          yylval.keyword_value = "ELSE";
          return ELSE;
        }
"while" {
#ifdef DEBUG
          printf("flex: found WHILE, line %d\n", yylineno);
#endif
          yylval.keyword_value = "WHILE";
          return WHILE;
        }
"return"  {
#ifdef DEBUG
            printf("flex: found RETURN, line %d\n", yylineno);
#endif
            yylval.keyword_value = "RETURN";
            return RETURN;
          }

{INT} {
        if (yytext[0] == '0' && yytext[1] == 'x') {
          yylval.int_value = strtol(yytext, NULL, 0);
        } else {
          yylval.int_value = atoi(yytext);
        }
#ifdef DEBUG
        printf("flex: found INT %ld, line %d\n", yylval.int_value, yylineno);
#endif
        return INT;
      }
{FLOAT} {
#ifdef DEBUG
          printf("flex: found FLOAT %f, line %d\n", yylval.float_value, yylineno);
#endif
          yylval.float_value = atof(yytext);
          return FLOAT;
        }
{CHAR}  {
          if (yytext[0] == '\'' && yytext[yyleng - 1] == '\'') {
            yylval.char_value = yytext[1];
          } else {
            yytext[0] = '0';
            yylval.char_value = strtol(yytext, NULL, 0);
          }
#ifdef DEBUG
          printf("flex: found CHAR %c, line %d\n", yylval.char_value, yylineno);
#endif
          return CHAR;
        }
{TYPE}  {
          yylval.type_value = strdup(yytext);
#ifdef DEBUG
          printf("flex: found TYPE %s, line %d\n", yylval.type_value, yylineno);
#endif
          return TYPE;
        }
{ID}  {
        yylval.id_value = strdup(yytext);
#ifdef DEBUG
        printf("flex: found ID %s, line %d\n", yylval.id_value, yylineno);
#endif
        return ID;
      }

. {
    printf("Error type A at Line %d: unknown lexeme %s\n", yylineno, yytext);
  }

%%
