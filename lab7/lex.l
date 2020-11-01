%{
    #include"syntax.tab.h"
    #include "def.h"
%}
%option noyywrap

unic u[0-9a-fA-F]{4}
esc \\([\"\\/bfnrt]|{unic})
scp [^"\\\x00-\x1f]
string \"({esc}|{scp})*\"

int 0|[1-9][0-9]*
frac \.[0-9]+
exp [Ee][+-]?[0-9]+
number -?{int}{frac}?{exp}?
error_number -?0[0-9]*{frac}?{exp}?

empty [ \n\r\t]

%%

"{" { return LC; }
"}" { return RC; }
"[" { return LB; }
"]" { return RB; }
":" { return COLON; }
"," { return COMMA; }

"true"  {
          yylval.boolean = true;
          return TRUE;
        }
"false" {
          yylval.boolean = false;
          return FALSE;
        }
"null" { return VNULL; }

{string}  {
            yylval.string = strdup(yytext);
            return STRING;
          }
{number}  {
            yylval.number = atof(yytext);
            return NUMBER;
          }
{error_number}  {
                  return ERROR_NUMBER;
                }

{empty} {}

. { printf("lexical error: %s\n", yytext); }
