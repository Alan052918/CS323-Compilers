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
Program: ExtDefList { printf("Program\n"); }
 ;
ExtDefList: ExtDef ExtDefList { printf("\tExtDefList\n"); }
 | %empty { printf("\tExtDefList\n"); }
 ;
ExtDef: Specifier ExtDecList SEMI { printf("\t\tExtDef\n"); }
 | Specifier SEMI { printf("\t\tExtDef\n"); }
 | Specifier FunDec CompSt { printf("\t\tExtDef\n"); }
 ;
ExtDecList: VarDec { printf("\t\t\tExtDecList\n"); }
 | VarDec COMMA ExtDecList { printf("\t\t\tExtDecList\n"); }
 ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier: TYPE { printf("\t\t\t\tSpecifier\n"); }
 | StructSpecifier { printf("\t\t\t\tSpecifier\n"); }
 ;
StructSpecifier: STRUCT ID LC DefList RC { printf("\t\t\t\t\tSpecifier\n"); }
 | STRUCT ID { printf("\t\t\t\t\tSpecifier\n"); }
 ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec: ID
 | VarDec LB INT RB
 ;
FunDec: ID LP VarList RP
 | ID LP RP
 ;
VarList: ParamDec COMMA VarList
 | ParamDec
 ;
ParamDec: Specifier VarDec
 ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt: LC DefList StmtList RC
 ;
StmtList: Stmt StmtList
 | %empty
 ;
Stmt: Exp SEMI
 | CompSt
 | RETURN Exp SEMI
 | IF LP Exp RP Stmt
 | IF LP Exp RP Stmt ELSE Stmt
 | WHILE LP Exp RP Stmt
 ;

/* Local definition: declaration and assignment of local variables */
DefList: Def DefList
 | %empty
 ;
Def: Specifier DecList SEMI
 ;
DecList: Dec
 | Dec COMMA DecList
 ;
Dec: VarDec
 | VarDec ASSIGN Exp
 ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp: Exp ASSIGN Exp
 | Exp AND Exp
 | Exp OR Exp
 | Exp LT Exp
 | Exp LE Exp
 | Exp GT Exp
 | Exp GE Exp
 | Exp NE Exp
 | Exp EQ Exp
 | Exp PLUS Exp
 | Exp MINUS Exp
 | Exp MUL Exp
 | Exp DIV Exp
 | LP Exp RP
 | MINUS Exp
 | NOT Exp
 | ID LP Args RP
 | ID LP RP
 | Exp LB Exp RB
 | Exp DOT ID
 | ID
 | INT
 | FLOAT
 | CHAR
 ;
Args: Exp COMMA Args
 | Exp
 ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv) {
  yyparse();
}
