%{
  #define EXIT_OK 0
  #define EXIT_FAIL 1
%}

%option yylineno

SPC     [ \t\r\n\f\v]
INT     [-+]?[0-9][0-9]*|[-+]?0[xX][0-9a-fA-F][0-9a-fA-F]*
FLOAT   [0-9]+\.[0-9]+
CHAR    \'[a-zA-Z]\'|\'\\x[0-9a-fA-F]+\'
TYPE    "int"|"char"|"float"
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

{SPC}     { /* whitespace characters, do nothing */ }
"."       { printf("DOT\n"); }
";"       { printf("SEMI\n"); }
","       { printf("COMMA\n"); }
"="       { printf("ASSIGN\n"); }
"<"       { printf("LT\n"); }
">"       { printf("GT\n"); }
"+"       { printf("PLUS\n"); }
"-"       { printf("MINUS\n"); }
"*"       { printf("MUL\n"); }
"/"       { printf("DIV\n"); }
"!"       { printf("NOT\n"); }
"("       { printf("LP\n"); }
")"       { printf("RP\n"); }
"["       { printf("LB\n"); }
"]"       { printf("RB\n"); }
"{"       { printf("LC\n"); }
"}"       { printf("RC\n"); }
"<="      { printf("LE\n"); }
">="      { printf("GE\n"); }
"!="      { printf("NE\n"); }
"=="      { printf("EQ\n"); }
"&&"      { printf("AND\n"); }
"||"      { printf("OR\n"); }

"//"      { char c; while ((c=input()) != '\n'); }

"struct"  { printf("STRUCT\n"); }
"if"      { printf("IF\n"); }
"else"    { printf("ELSE\n"); }
"while"   { printf("WHILE\n"); }
"return"  { printf("RETURN\n"); }

{INT}     { printf("INT %s\n", yytext); }
{FLOAT}   { printf("FLOAT %s\n", yytext); }
{CHAR}    { printf("CHAR %s\n", yytext); }
{TYPE}    { printf("TYPE %s\n", yytext); }
{ID}      { printf("ID %s\n", yytext); }

.         {
  printf("Error type A at Line %d: Unknown characters \'%s\'\n", 
    yylineno, yytext);
}

%%

int main(int argc, char **argv) {
  char *file_name;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    return EXIT_FAIL;
  } else if (argc == 2) {
    file_name = argv[1];
    if (!(yyin = fopen(file_name, "r"))) {
      perror(argv[1]);
      return EXIT_FAIL;
    }
    yylex();
    return EXIT_OK;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAIL;
  }
}
