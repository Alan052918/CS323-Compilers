%{
  #include "lex.yy.c"

  void yyerror(const char *);

  int indent_level = 0;
%}

%union {
  int int_value;
  float float_value;
  char char_value;
  char *str_value;
}

%token <int_value> INT
%token <float_value> FLOAT
%token <char_value> CHAR
%token ID LC RC TYPE STRUCT
%token COMMA DOT SEMI
%token RETURN WHILE IF

%right ASSIGN
%left OR
%left AND
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left MUL DIV
%right NOT
%left LB RB LP RP DOT
%nonassoc ELSE

%%

/**
 * High-level definition: top-level syntax for a SPL program
 * - global variable declarations
 * - function definitions
 */
Program: ExtDefList { printf("Program (%d)\n", yylineno); }
 ;
ExtDefList: ExtDef ExtDefList { printf("ExtDefList\n"); }
 | %empty { printf("ExtDefList\n"); }
 ;
ExtDef: Specifier ExtDecList SEMI { printf("ExtDef\n"); }
 | Specifier SEMI { printf("ExtDef\n"); }
 | Specifier FunDec CompSt { printf("ExtDef\n"); }
 ;
ExtDecList: VarDec { printf("ExtDecList\n"); }
 | VarDec COMMA ExtDecList { printf("ExtDecList\n"); }
 ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier: TYPE { printf("Specifier\n"); }
 | StructSpecifier { printf("Specifier\n"); }
 ;
StructSpecifier: STRUCT ID LC DefList RC { printf("StructSpecifier\n"); }
 | STRUCT ID { printf("StructSpecifier\n"); }
 ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec: ID { printf("VarDec\n"); }
 | VarDec LB INT RB { printf("VarDec\n"); }
 ;
FunDec: ID LP VarList RP { printf("FunDec\n"); }
 | ID LP RP { printf("FunDec\n"); }
 ;
VarList: ParamDec COMMA VarList { printf("VarList\n"); }
 | ParamDec { printf("VarList\n"); }
 ;
ParamDec: Specifier VarDec { printf("ParamDec\n"); }
 ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt: LC DefList StmtList RC { printf("CompSt\n"); }
 ;
StmtList: Stmt StmtList { printf("StmtList\n"); }
 | %empty { printf("StmtList\n"); }
 ;
Stmt: Exp SEMI { printf("Stmt\n"); }
 | CompSt { printf("Stmt\n"); }
 | RETURN Exp SEMI { printf("Stmt\n"); }
 | IF LP Exp RP Stmt { printf("Stmt\n"); }
 | IF LP Exp RP Stmt ELSE Stmt { printf("Stmt\n"); }
 | WHILE LP Exp RP Stmt { printf("Stmt\n"); }
 ;

/* Local definition: declaration and assignment of local variables */
DefList: Def DefList { printf("DefList\n"); }
 | %empty { printf("DefList\n"); }
 ;
Def: Specifier DecList SEMI { printf("Def\n"); }
 ;
DecList: Dec { printf("DecList\n"); }
 | Dec COMMA DecList { printf("DecList\n"); }
 ;
Dec: VarDec { printf("Dec\n"); }
 | VarDec ASSIGN Exp { printf("Dec\n"); }
 ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp: Exp ASSIGN Exp { printf("Exp\n"); }
 | Exp AND Exp { printf("Exp\n"); }
 | Exp OR Exp { printf("Exp\n"); }
 | Exp LT Exp { printf("Exp\n"); }
 | Exp LE Exp { printf("Exp\n"); }
 | Exp GT Exp { printf("Exp\n"); }
 | Exp GE Exp { printf("Exp\n"); }
 | Exp NE Exp { printf("Exp\n"); }
 | Exp EQ Exp { printf("Exp\n"); }
 | Exp PLUS Exp { printf("Exp\n"); }
 | Exp MINUS Exp { printf("Exp\n"); }
 | Exp MUL Exp { printf("Exp\n"); }
 | Exp DIV Exp { printf("Exp\n"); }
 | LP Exp RP { printf("Exp\n"); }
 | MINUS Exp { printf("Exp\n"); }
 | NOT Exp { printf("Exp\n"); }
 | ID LP Args RP { printf("Exp\n"); }
 | ID LP RP { printf("Exp\n"); }
 | Exp LB Exp RB { printf("Exp\n"); }
 | Exp DOT ID { printf("Exp\n"); }
 | ID { printf("Exp\n"); }
 | INT { printf("Exp\n"); }
 | FLOAT { printf("Exp\n"); }
 | CHAR { printf("Exp\n"); }
 ;
Args: Exp COMMA Args { printf("Args\n"); }
 | Exp { printf("Args\n"); }
 ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv) {
  printf("in syntax.y main method\n");
  yyparse();
}
