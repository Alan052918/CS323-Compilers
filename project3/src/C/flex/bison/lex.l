%{
  #include "include/common.hh"
  #include "include/ast_list.hh"
  #include "syntax.tab.h"

  using namespace std;

  #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycoluno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycoluno + yyleng; \
    yycoluno += yyleng;

  extern "C" int yylex();

  int yycoluno = 1;
%}

%option yylineno

SPC     [ \t\r\f\v]
FLOAT   -?[0-9]*\.[0-9]+
INT     0|-?[1-9][0-9]{0,9}|-?0[xX][1-9a-fA-F][0-9a-fA-F]*
CHAR    \'[a-zA-Z]\'|\'\\x[1-9a-fA-F][0-9a-fA-F]*\'
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][0-9a-zA-Z_]*

ERR_ID    [a-zA-Z0-9_]+
ERR_CHAR  \'\\x[0-9a-zA-Z]+\'

SINGLE_LINE_COMMENT "//".*

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
        yylval.keyword_value = (char *)"DOT";
        return DOT;
      }
";"   {
#ifdef DEBUG
        printf("flex: found SEMI, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"SEMI";
        return SEMI;
      }
","   {
#ifdef DEBUG
        printf("flex: found COMMA, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"COMMA";
        return COMMA;
      }
"="   {
#ifdef DEBUG
        printf("flex: found ASSIGN, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"ASSIGN";
        return ASSIGN;
      }
"<"   {
#ifdef DEBUG
        printf("flex: found LT, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"LT";
        return LT;
      }
">"   {
#ifdef DEBUG
        printf("flex: found GT, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"GT";
        return GT;
      }
"+"   {
#ifdef DEBUG
        printf("flex: found PLUS, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"PLUS";
        return PLUS;
      }
"-"   {
#ifdef DEBUG
        printf("flex: found MINUS, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"MINUS";
        return MINUS;
      }
"*"   {
#ifdef DEBUG
        printf("flex: found MUL, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"MUL";
        return MUL;
      }
"/"   {
#ifdef DEBUG
        printf("flex: found DIV, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"DIV";
        return DIV;
      }
"!"   {
#ifdef DEBUG
        printf("flex: found NOT, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"NOT";
        return NOT;
      }
"("   {
#ifdef DEBUG
        printf("flex: found LP, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"LP";
        return LP;
      }
")"   {
#ifdef DEBUG
        printf("flex: found RP, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"RP";
        return RP;
      }
"["   {
#ifdef DEBUG
        printf("flex: found LB, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"LB";
        return LB;
      }
"]"   {
#ifdef DEBUG
        printf("flex: found RB, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"RB";
        return RB;
      }
"{"   {
#ifdef DEBUG
        printf("flex: found LC, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"LC";
        return LC;
      }
"}"   {
#ifdef DEBUG
        printf("flex: found RC, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"RC";
        return RC;
      }
"<="  {
#ifdef DEBUG
        printf("flex: found LE, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"LE";
        return LE;
      }
">="  {
#ifdef DEBUG
        printf("flex: found GE, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"GE";
        return GE;
      }
"!="  {
#ifdef DEBUG
        printf("flex: found NE, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"NE";
        return NE;
      }
"=="  {
#ifdef DEBUG
        printf("flex: found EQ, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"EQ";
        return EQ;
      }
"&&"  {
#ifdef DEBUG
        printf("flex: found AND, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"AND";
        return AND;
      }
"||"  {
#ifdef DEBUG
        printf("flex: found OR, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"OR";
        return OR;
      }

"struct"  {
#ifdef DEBUG
            printf("flex: found STRUCT, line %d\n", yylineno);
#endif
            yylval.keyword_value = (char *)"STRUCT";
            return STRUCT;
          }
"if"  {
#ifdef DEBUG
        printf("flex: found IF, line %d\n", yylineno);
#endif
        yylval.keyword_value = (char *)"IF";
        return IF;
      }
"else"  {
#ifdef DEBUG
          printf("flex: found ELSE, line %d\n", yylineno);
#endif
          yylval.keyword_value = (char *)"ELSE";
          return ELSE;
        }
"while" {
#ifdef DEBUG
          printf("flex: found WHILE, line %d\n", yylineno);
#endif
          yylval.keyword_value = (char *)"WHILE";
          return WHILE;
        }
"return"  {
#ifdef DEBUG
            printf("flex: found RETURN, line %d\n", yylineno);
#endif
            yylval.keyword_value = (char *)"RETURN";
            return RETURN;
          }
{FLOAT} {
#ifdef DEBUG
          printf("flex: found FLOAT %f, line %d\n", yylval.float_value, yylineno);
#endif
          yylval.float_value = atof(yytext);
          return FLOAT;
        }
{INT} {
        if (yytext[0] == '0' && yytext[1] == 'x') {
          int i = strtol(yytext, NULL, 0);
          if (i == 0) {
#ifdef DEBUG
            printf("flex: found invalid INT %s, line %d\n", yytext, yylineno);
#endif
          }
          yylval.int_value = i;
        } else {
          yylval.int_value = atoi(yytext);
        }
#ifdef DEBUG
        printf("flex: found INT %ld[%s], line %d\n", yylval.int_value, yytext, yylineno);
#endif
        return INT;
      }
{CHAR}  {
          if (yytext[1] == '\\' && yytext[2] == 'x') {
            // hexadecimal-form char
            yytext[1] = '0';
            int c = strtol(yytext + 1, NULL, 16);
            yytext[1] = '\\';
            if (c == 0 || c > 255) {
#ifdef DEBUG
              printf("flex: found invalid CHAR %d[%s], line %d\n", c, yytext, yylineno);
#endif
            }
          }
          yylval.char_value = strdup(yytext);
#ifdef DEBUG
          printf("flex: found CHAR %s[%s], line %d\n", yylval.char_value, yytext, yylineno);
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

{ERR_ID}  {
            // This will match any combination of letters, numbers, and underscores
#ifdef DEBUG
            printf("flex: found invalid id %s, line %d\n", yytext, yylineno);
#endif
          }
{ERR_CHAR}  {
#ifdef DEBUG
              printf("flex: found invalid hex char %s, line %d\n", yytext, yylineno);
#endif
            }

{SINGLE_LINE_COMMENT} {
#ifdef DEBUG
                        printf("flex: found single line comment, line %d\n", yylineno);
#endif
                      }
. {
    // This will match any character
#ifdef DEBUG
    printf("flex: found invalid character %s, line %d\n", yytext, yylineno);
#endif
  }

%%
