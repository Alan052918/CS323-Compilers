%{
    #include"lex.yy.c"
    void yyerror(const char *s);
    int result;
%}
%token LP RP LB RB LC RC
%%

Program: Exp { result = 1; }
 ;
Exp: %empty
 | Exp LP Exp RP
 | Exp LB Exp RB
 | Exp LC Exp RC
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
