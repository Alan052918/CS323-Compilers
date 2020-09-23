%{ 
  #include "lex.yy.c" 
  #include "astdef.h"

  void yyerror(const char *);
%}

%union {
  int int_value;
  float float_value;
  char char_value;
  char *str_value;
  struct ast_node *nonterminal_node;
}

%type <nonterminal_node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

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
Program: ExtDefList { $$ = make_ast_node(Program, $1); }
 ;
ExtDefList: ExtDef ExtDefList { $$ = make_ast_node(ExtDefList, $1, $2); }
 | %empty { $$ = make_ast_node(ExtDefList); }
 ;
ExtDef: Specifier ExtDecList SEMI { $$ = make_ast_node(ExtDef, $1, $2, $3); }
 | Specifier SEMI { $$ = make_ast_node(ExtDef, $1, $2); }
 | Specifier FunDec CompSt { $$ = make_ast_node(ExtDef, $1, $2, $3); }
 ;
ExtDecList: VarDec { $$ = make_ast_node(ExtDecList, $1); }
 | VarDec COMMA ExtDecList { $$ = make_ast_node(ExtDecList, $1, $2, $3); }
 ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier: TYPE { $$ = make_ast_node(Specifier, $1); }
 | StructSpecifier { $$ = make_ast_node(Specifier, $1); }
 ;
StructSpecifier: STRUCT ID LC DefList RC { $$ = make_ast_node(StructSpecifier, $1, $2, $3, $4, $5); }
 | STRUCT ID { $$ = make_ast_node(StructSpecifier, $1, $2); }
 ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec: ID { $$ = make_ast_node(VarDec, $1); }
 | VarDec LB INT RB { $$ = make_ast_node(VarDec, $1, $2, $3, $4); }
 ;
FunDec: ID LP VarList RP { $$ = make_ast_node(FunDec, $1, $2, $3, $4); }
 | ID LP RP { $$ = make_ast_node(FunDec, $1, $2, $3); }
 ;
VarList: ParamDec COMMA VarList { $$ = make_ast_node(VarList, $1, $2, $3); }
 | ParamDec { $$ = make_ast_node(VarList, $1); }
 ;
ParamDec: Specifier VarDec { $$ = make_ast_node(ParamDec, $1, $2); }
 ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt: LC DefList StmtList RC { $$ = make_ast_node(CompSt, $1, $2, $3, $4); }
 ;
StmtList: Stmt StmtList { $$ = make_ast_node(StmtList, $1, $2); }
 | %empty { $$ = make_ast_node(StmtList); }
 ;
Stmt: Exp SEMI { $$ = make_ast_node(Stmt, $1, $2); }
 | CompSt { $$ = make_ast_node(Stmt, $1); }
 | RETURN Exp SEMI { $$ = make_ast_node(Stmt, $1, $2, $3); }
 | IF LP Exp RP Stmt { $$ = make_ast_node(Stmt, $1, $2, $3, $4); }
 | IF LP Exp RP Stmt ELSE Stmt { $$ = make_ast_node(Stmt, $1, $2, $3, $4, $5, $6, $7); }
 | WHILE LP Exp RP Stmt { $$ = make_ast_node(Stmt, $1, $2, $3, $4); }
 ;

/* Local definition: declaration and assignment of local variables */
DefList: Def DefList { $$ = make_ast_node(DefList, $1, $2); }
 | %empty  { $$ = make_ast_node(DefList); }
 ;
Def: Specifier DecList SEMI { $$ = make_ast_node(Def, $1, $2, $3); }
 ;
DecList: Dec { $$ = make_ast_node(DecList, $1); }
 | Dec COMMA DecList { $$ = make_ast_node(DecList, $1, $2, $3); }
 ;
Dec: VarDec { $$ = make_ast_node(Dec, $1); }
 | VarDec ASSIGN Exp { $$ = make_ast_node(Dec, $1, $2, $3); }
 ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp: Exp ASSIGN Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp AND Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp OR Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp LT Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp LE Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp GT Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp GE Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp NE Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp EQ Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp PLUS Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp MINUS Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp MUL Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp DIV Exp { $$ = make_ast_node(Exp, $1, $2, $3); }
 | LP Exp RP { $$ = make_ast_node(Exp, $1, $2, $3); }
 | MINUS Exp { $$ = make_ast_node(Exp, $1, $2); }
 | NOT Exp { $$ = make_ast_node(Exp, $1, $2); }
 | ID LP Args RP { $$ = make_ast_node(Exp, $1, $2, $3, $4); }
 | ID LP RP { $$ = make_ast_node(Exp, $1, $2, $3); }
 | Exp LB Exp RB { $$ = make_ast_node(Exp, $1, $2, $3, $4); }
 | Exp DOT ID { $$ = make_ast_node(Exp, $1, $2, $3); }
 | ID { $$ = make_ast_node(Exp, $1); }
 | INT { $$ = make_ast_node(Exp, $1); }
 | FLOAT { $$ = make_ast_node(Exp, $1); }
 | CHAR { $$ = make_ast_node(Exp, $1); }
 ;
Args: Exp COMMA Args { $$ = make_ast_node(Args, $1, $2, $3); }
 | Exp { $$ = make_ast_node(Args, $1); }
 ;

%%

struct ast_node *make_ast_node(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int node_type = va_arg(args, int);
      struct ast_node *node = (struct ast_node *)malloc(sizeof(struct ast_node));
      node->node_type = node_type;
    } else if (*fmt
  }
  return node;
}

void yyerror(const char *s) {
  fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
  char *file_name;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    return EXIT_FAILURE;
  } else if (argc == 2) {
    file_name = argv[1];
    if (!(yyin = fopen(file_name, "r"))) {
      perror(argv[1]);
      return EXIT_FAILURE;
    }
    yyparse();
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
