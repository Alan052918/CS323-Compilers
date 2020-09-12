%{
  #define EXIT_OK 0
  #define EXIT_FAIL 1
%}

%option yylineno

INT     [0-9]+|0[xX][0-9]+
FLOAT   [0-9]+\.[0-9]+
CHAR    \'[a-zA-Z]\'
ID      [^0-9][0-9a-zA-Z]+
TYPE    "int"|"char"|"float"

%%

{INT}       { printf("INT\n"); }
{FLOAT}     { printf("FLOAT\n"); }
{CHAR}      { printf("CHAR\n"); }
{ID}        { printf("ID %s\n", yytext); }
{TYPE}      { printf("TYPE %s\n", yytext); }
"struct"    { printf("STRUCT\n"); }
"if"        { printf("IF\n"); }
"else"      { printf("ELSE\n"); }
"while"     { printf("WHILE\n"); }
"return"    { printf("RETURN\n"); }
"."         { printf("DOT\n"); }
";"         { printf("SEMI\n"); }
","         { printf("COMMA\n"); }
"="         { printf("ASSIGN\n"); }
"<"         { printf("LT\n"); }
"<="        { printf("LE\n"); }
">"         { printf("GT\n"); }
">="        { printf("GE\n"); }
"!="        { printf("NE\n"); }
"=="        { printf("EQ\n"); }
"+"         { printf("PLUS\n"); }
"-"         { printf("MINUS\n"); }
"*"         { printf("MUL\n"); }
"/"         { printf("DIV\n"); }
"&&"        { printf("AND\n"); }
"||"        { printf("OR\n"); }
"!"         { printf("NOT\n"); }
"("         { printf("LP\n"); }
")"         { printf("RP\n"); }
"["         { printf("LB\n"); }
"]"         { printf("RB\n"); }
"{"         { printf("LC\n"); }
"}"         { printf("RC\n"); }

"//"        { char c; while((c=input()) != ’\n’); }
\"[^\"]*\"  {
  if(yytext[yyleng-2] == ’\\’) {
    yyless(yyleng-1);
    yymore();
  } else {
    /* process the string literal */
  }
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
