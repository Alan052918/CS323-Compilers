%{
    #include"lex.yy.c"
    void yyerror(const char *s);
    int result;
%}
%token LP RP LB RB LC RC
%%

Program: ExpList { result = 1; }
 ;
ExpList: Exp ExpList
 | %empty
 ;
Exp: LP ExpList RP
 | LB ExpList RB
 | LC ExpList RC
 ;

%%

void yyerror(const char *s) {
  result = 0;
}

int validParentheses(char *expr){
    yy_scan_string(expr);
    yyparse();
    return result;
}
