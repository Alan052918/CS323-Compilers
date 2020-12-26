%{
  #include "include/ast_list.hh"
  #include "include/common.hh"
  #include "include/typedef.hh"

  extern "C" FILE *yyin;

  bool syntax_error;
  Program *program_root;

  extern "C" int yylex();
  extern "C" int yyparse();

  void yyerror(const char *);
%}

%union {
  long int_value;
  float float_value;
  char *char_value;
  char *type_value;
  char *id_value;
  char *keyword_value;
  Program *program_node;
  ExtDefList *ext_def_list_node;
  ExtDef *ext_def_node;
  ExtDecList *ext_dec_list_node;
  Specifier *specifier_node;
  StructSpecifier *struct_specifier_node;
  VarDec *var_dec_node;
  FunDec *fun_dec_node;
  VarList *var_list_node;
  ParamDec *param_dec_node;
  CompSt *comp_st_node;
  StmtList *stmt_list_node;
  Stmt *stmt_node;
  DefList *def_list_node;
  Def *def_node;
  DecList *dec_list_node;
  Dec *dec_node;
  Exp *exp_node;
  Args *args_node;
}

%type <program_node> Program
%type <ext_def_list_node> ExtDefList
%type <ext_def_node> ExtDef
%type <ext_dec_list_node> ExtDecList
%type <specifier_node> Specifier
%type <struct_specifier_node> StructSpecifier
%type <var_dec_node> VarDec
%type <fun_dec_node> FunDec
%type <var_list_node> VarList
%type <param_dec_node> ParamDec
%type <comp_st_node> CompSt
%type <stmt_list_node> StmtList
%type <stmt_node> Stmt
%type <def_list_node> DefList
%type <def_node> Def
%type <dec_list_node> DecList
%type <dec_node> Dec
%type <exp_node> Exp
%type <args_node> Args

%token <int_value> INT
%token <float_value> FLOAT
%token <char_value> CHAR
%token <type_value> TYPE
%token <id_value> ID

%token <keyword_value> STRUCT
%token <keyword_value> LC RC COMMA SEMI
%token <keyword_value> RETURN WHILE IF

%nonassoc LOWER_ELSE
%nonassoc <keyword_value> ELSE

%nonassoc UNKNOWN_LEXEME
%right <keyword_value> ASSIGN
%left <keyword_value> OR
%left <keyword_value> AND
%left <keyword_value> LT LE GT GE NE EQ
%left <keyword_value> PLUS MINUS
%left <keyword_value> MUL DIV
%right <keyword_value> NOT
%left <keyword_value> LB RB LP RP DOT

%%

/**
 * High-level definition: top-level syntax for a SPL program
 * - global variable declarations
 * - function definitions
 */
Program:
    ExtDefList {
      $$ = new Program(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->ext_def_list = $1;

      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      $$ = new ExtDefList(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 0);

      $$->node_list.push_back($1);
      for (ExtDef *ext_def : $2->node_list) {
        $$->node_list.push_back(ext_def);
      }
    }
  | %empty {
      $$ = new ExtDefList(0, 0, 0, 0, 1);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      $$ = new ExtDef(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->specifier = $1;
      $$->ext_dec_list = $2;
    }
  | Specifier SEMI {
      $$ = new ExtDef(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 1);

      $$->specifier = $1;
    }
  | Specifier FunDec CompSt {
      $$ = new ExtDef(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 2);

      $$->specifier = $1;
      $$->fun_dec = $2;
      $$->comp_st = $3;
    }
  ;
ExtDecList:
    VarDec {
      $$ = new ExtDecList(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->node_list.push_back($1);
    }
  | VarDec COMMA ExtDecList {
      $$ = new ExtDecList(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->node_list.push_back($1);
      for (VarDec *var_dec : $3->node_list) {
        $$->node_list.push_back(var_dec);
      }
    }
  ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier:
    TYPE {
      $$ = new Specifier(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->type_node = new TerminalNode(Type, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->type_node->type_token = $1;
    }
  | StructSpecifier {
      $$ = new Specifier(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 1);

      $$->struct_specifier = $1;
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      $$ = new StructSpecifier(@1.first_line, @5.last_line, @1.first_column, @5.last_column, 0);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $2;

      $$->def_list = $4;
    }
  | STRUCT ID {
      $$ = new StructSpecifier(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 1);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $2;
    }
  ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec:
    ID {
      $$ = new VarDec(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | VarDec LB INT RB {
      $$ = new VarDec(@1.first_line, @4.last_line, @1.first_column, @4.last_column, 1);

      $$->var_dec = $1;

      $$->int_node = new TerminalNode(Int, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      $$->int_node->int_token = $3;
    }
  | UNKNOWN_LEXEME error {
      $$ = new VarDec(@1.first_line, @1.last_line, @1.first_column, @1.last_column, -1);
    }
  ;
FunDec:
    ID LP VarList RP {
      $$ = new FunDec(@1.first_line, @4.last_line, @1.first_column, @4.last_column, 0);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $1;

      $$->var_list = $3;
    }
  | ID LP RP {
      $$ = new FunDec(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 1);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $1;
    }
  ;
VarList:
    ParamDec COMMA VarList {
      $$ = new VarList(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->node_list.push_back($1);
      for (ParamDec *pd : $3->node_list) {
        $$->node_list.push_back(pd);
      }
    }
  | ParamDec {
      $$ = new VarList(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->node_list.push_back($1);
    }
  ;
ParamDec:
    Specifier VarDec {
      $$ = new ParamDec(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 0);

      $$->specifier = $1;
      $$->var_dec = $2;
    }
  ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 * Definitions must come before statements!
 */
CompSt:
    LC DefList StmtList RC {
      $$ = new CompSt(@1.first_line, @4.last_line, @1.first_column, @4.last_column, 0);

      $$->def_list = $2;
      $$->stmt_list = $3;
    }
  ;
StmtList:
    Stmt StmtList {
      $$ = new StmtList(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 0);

      $$->node_list.push_back($1);
      for (Stmt *stmt : $2->node_list) {
        $$->node_list.push_back(stmt);
      }
    }
  | %empty {
      $$ = new StmtList(0, 0, 0, 0, 1);
    }
  ;
Stmt:
    Exp SEMI {
      $$ = new Stmt(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 0);

      $$->exp = $1;
    }
  | CompSt {
      $$ = new Stmt(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 1);

      $$->comp_st = $1;
    }
  | RETURN Exp SEMI {
      $$ = new Stmt(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 2);

      $$->exp = $2;
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      $$ = new Stmt(@1.first_line, @5.last_line, @1.first_column, @5.last_column, 3);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      $$ = new Stmt(@1.first_line, @7.last_line, @1.first_column, @7.last_column, 4);

      $$->exp = $3;
      $$->stmt_1 = $5;
      $$->stmt_2 = $7;
    }
  | WHILE LP Exp RP Stmt {
      $$ = new Stmt(@1.first_line, @5.last_line, @1.first_column, @5.last_column, 5);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      $$ = new DefList(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 0);

      $$->node_list.push_back($1);
      for (Def *d : $2->node_list) {
        $$->node_list.push_back(d);
      }
    }
  | %empty  {
      $$ = new DefList(0, 0, 0, 0, 1);
    }
  ;
Def:
    Specifier DecList SEMI {
      $$ = new Def(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->specifier = $1;
      $$->dec_list = $2;
    }
  ;
DecList:
    Dec {
      $$ = new DecList(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->node_list.push_back($1);
    }
  | Dec COMMA DecList {
      $$ = new DecList(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->node_list.push_back($1);
      for (Dec *dec : $3->node_list) {
        $$->node_list.push_back(dec);
      }
    }
  ;
Dec:
    VarDec {
      $$ = new Dec(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->var_dec = $1;
    }
  | VarDec ASSIGN Exp {
      $$ = new Dec(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 1);

      $$->var_dec = $1;
      $$->exp = $3;
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp AND Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp OR Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp LT Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp LE Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp GT Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp GE Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp NE Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp EQ Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp PLUS Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp MINUS Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp MUL Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp DIV Exp {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | LP Exp RP {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 1);

      $$->exp_1 = $2;
    }
  | MINUS Exp {
      $$ = new Exp(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 2);

      $$->keyword_node = new TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->keyword_node->keyword_token = $1;

      $$->exp_1 = $2;
    }
  | NOT Exp {
      $$ = new Exp(@1.first_line, @2.last_line, @1.first_column, @2.last_column, 2);

      $$->keyword_node = new TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->keyword_node->keyword_token = $1;

      $$->exp_1 = $2;
    }
  | ID LP Args RP {
      $$ = new Exp(@1.first_line, @4.last_line, @1.first_column, @4.last_column, 3);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;

      $$->args = $3;
    }
  | ID LP RP {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 4);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | Exp LB Exp RB {
      $$ = new Exp(@1.first_line, @4.last_line, @1.first_column, @4.last_column, 5);

      $$->exp_1 = $1;
      $$->exp_2 = $3;
    }
  | Exp DOT ID {
      $$ = new Exp(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 6);

      $$->exp_1 = $1;

      $$->id_node = new TerminalNode(Id, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      $$->id_node->id_token = $3;
    }
  | ID {
      $$ = new Exp(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 7);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | INT {
      $$ = new Exp(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 8);

      $$->int_node = new TerminalNode(Int, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->int_node->int_token = $1;
    }
  | FLOAT {
      $$ = new Exp(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 9);

      $$->float_node = new TerminalNode(Float, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->float_node->float_token = $1;
    }
  | CHAR {
      $$ = new Exp(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 10);

      $$->char_node = new TerminalNode(Char, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->char_node->char_token = $1;
    }
  ;
Args:
    Exp COMMA Args {
      $$ = new Args(@1.first_line, @3.last_line, @1.first_column, @3.last_column, 0);

      $$->node_list.push_back($1);
      for (Exp *e : $3->node_list) {
        $$->node_list.push_back(e);
      }
    }
  | Exp {
      $$ = new Args(@1.first_line, @1.last_line, @1.first_column, @1.last_column, 0);

      $$->node_list.push_back($1);
    }
  ;

%%

void yyerror(const char *s) {
  syntax_error = true;
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
    syntax_error = false;
    int result = yyparse();
    if (result == 0 && syntax_error == false) {
#ifdef DEBUG
      printf("\n*********************\n");
#endif
      SymbolTable *st = new SymbolTable();
      program_root->visit(0, st);
    } else if (result == 1) {
#ifdef DEBUG
      fprintf(stderr, "Abort\n");
#endif
    } else if (result > 1) {
#ifdef DEBUG
      fprintf(stderr, "Exhausted\n");
#endif
    } else if (syntax_error == true) {
#ifdef DEBUG
      fprintf(stderr, "Syntax error\n");
#endif
    } else {
#ifdef DEBUG
      fprintf(stderr, "Unknown error\n");
#endif
    }
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
