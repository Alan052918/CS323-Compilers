%{
    #include"lex.yy.c"
    void yyerror(const char*);
%}

%token LC RC LB RB COLON COMMA
%token STRING NUMBER ERROR_NUMBER
%token TRUE FALSE VNULL
%%

Json:
    | Value
    | Value COMMA error { puts("Comma after the close, recovered"); }
    ;
Value:
      Object
    | Array
    | STRING
    | NUMBER
    | ERROR_NUMBER error { puts("Numbers cannot have leading zeroes, recovered"); }
    | TRUE
    | FALSE
    | VNULL
    ;
Object:
      LC RC
    | LC Members RC
    | LC Members RC Value error { puts("Extra value after close, recovered"); }
    | LC Members COMMA error { puts("Comma instead of closing brace, recovered"); }
    ;
Members:
      Member
    | Member COMMA Members
    | Member COMMA error { puts("Extra comma, recovered"); }
    ;
Member:
      STRING COLON Value
    | STRING Value error { puts("Missing colon, recovered"); }
    | STRING COMMA Value error { puts("Comma instead of colon, recovered"); }
    | STRING COLON COLON Value error { puts("Double colon, recovered"); }
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values error { puts("Unclosed array, recovered"); }
    | LB Values RC error { puts("Unmatched right bracket, recovered"); }
    | LB Values RB RB error { puts("Extra close, recovered"); }
    ;
Values:
      Value
    | Value COMMA Values
    | Value COMMA error { puts("Extra comma, recovered"); }
    | Value COMMA COMMA error { puts("Double extra comma, recovered"); }
    | Value COLON Values error { puts("Colon instead of comma, recovered"); }
    | COMMA Values error { puts("Missing value, recovered"); }
    ;
%%

void yyerror(const char *s){
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    return 0;
}
