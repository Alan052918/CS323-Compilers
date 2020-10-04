#define YY_USER_ACTION \
  yylloc.first_line = yylineno; \
  yylloc.first_column = yycoluno; \
  yylloc.last_line = yylineno; \
  yylloc.last_column = yycoluno + yyleng; \
  yycoluno += yyleng;

