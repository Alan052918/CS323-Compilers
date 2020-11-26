%{
  #include "include/ast_list.h"
  #include "include/common.h"
  #include "include/typedef.h"

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
      $$ = new Program(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->ext_def_list = $1;

      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      $$ = new ExtDefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->node_list.push_back($1);
      for (ExtDef *ext_def : $2->node_list) {
        $$->node_list.push_back(ext_def);
      }
    }
  | %empty {
      $$ = new ExtDefList(1, 0, 0, 0, 0);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      $$ = new ExtDef(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->ext_dec_list = $2;
    }
  | Specifier SEMI {
      $$ = new ExtDef(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->specifier = $1;
    }
  | Specifier FunDec CompSt {
      $$ = new ExtDef(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->fun_dec = $2;
      $$->comp_st = $3;
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = new ExtDef(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = new ExtDef(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
ExtDecList:
    VarDec {
      $$ = new ExtDecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | VarDec COMMA ExtDecList {
      $$ = new ExtDecList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

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
      $$ = new Specifier(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->type_node = new TerminalNode(Type, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->type_node->type_token = $1;
    }
  | StructSpecifier {
      $$ = new Specifier(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->struct_specifier = $1;
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      $$ = new StructSpecifier(0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $2;

      $$->def_list = $4;
    }
  | STRUCT ID {
      $$ = new StructSpecifier(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

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
      $$ = new VarDec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | VarDec LB INT RB {
      $$ = new VarDec(1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->var_dec = $1;

      $$->int_node = new TerminalNode(Int, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      $$->int_node->int_token = $3;
    }
  | UNKNOWN_LEXEME error {
      $$ = new VarDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  ;
FunDec:
    ID LP VarList RP {
      $$ = new FunDec(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $1;

      $$->var_list = $3;
    }
  | ID LP RP {
      $$ = new FunDec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->id_node = new TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->id_node->id_token = $1;
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = new FunDec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = new FunDec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
VarList:
    ParamDec COMMA VarList {
      $$ = new VarList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (ParamDec *pd : $3->node_list) {
        $$->node_list.push_back(pd);
      }
    }
  | ParamDec {
      $$ = new VarList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  ;
ParamDec:
    Specifier VarDec {
      $$ = new ParamDec(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->specifier = $1;
      $$->var_dec = $2;
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = new ParamDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
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
      $$ = new CompSt(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->def_list = $2;
      $$->stmt_list = $3;
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      $$ = new CompSt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
StmtList:
    Stmt StmtList {
      $$ = new StmtList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->node_list.push_back($1);
      for (Stmt *stmt : $2->node_list) {
        $$->node_list.push_back(stmt);
      }
    }
  | %empty {
      $$ = new StmtList(1, 0, 0, 0, 0);
    }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = new StmtList(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Stmt:
    Exp SEMI {
      $$ = new Stmt(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->exp = $1;
    }
  | CompSt {
      $$ = new Stmt(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->comp_st = $1;
    }
  | RETURN Exp SEMI {
      $$ = new Stmt(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp = $2;
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      $$ = new Stmt(3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      $$ = new Stmt(4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
      $$->stmt_2 = $7;
    }
  | WHILE LP Exp RP Stmt {
      $$ = new Stmt(5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = new Stmt(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = new Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = new Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      $$ = new Stmt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      $$ = new DefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->node_list.push_back($1);
      for (Def *d : $2->node_list) {
        $$->node_list.push_back(d);
      }
    }
  | %empty  {
      $$ = new DefList(1, 0, 0, 0, 0);
    }
  ;
Def:
    Specifier DecList SEMI {
      $$ = new Def(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->dec_list = $2;
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = new Def(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
DecList:
    Dec {
      $$ = new DecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | Dec COMMA DecList {
      $$ = new DecList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (Dec *dec : $3->node_list) {
        $$->node_list.push_back(dec);
      }
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      $$ = new DecList(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
Dec:
    VarDec {
      $$ = new Dec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->var_dec = $1;
    }
  | VarDec ASSIGN Exp {
      $$ = new Dec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->var_dec = $1;
      $$->exp = $3;
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      $$ = new Dec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      $$ = new Dec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp AND Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp OR Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp LT Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp LE Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp GT Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp GE Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp NE Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp EQ Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp PLUS Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp MINUS Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp MUL Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | Exp DIV Exp {
      $$ = new Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      $$->keyword_node = new TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      $$->keyword_node->keyword_token = $2;
    }
  | LP Exp RP {
      $$ = new Exp(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $2;
    }
  | MINUS Exp {
      $$ = new Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->keyword_node = new TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->keyword_node->keyword_token = $1;

      $$->exp_1 = $2;
    }
  | NOT Exp {
      $$ = new Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->keyword_node = new TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->keyword_node->keyword_token = $1;

      $$->exp_1 = $2;
    }
  | ID LP Args RP {
      $$ = new Exp(3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;

      $$->args = $3;
    }
  | ID LP RP {
      $$ = new Exp(4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | Exp LB Exp RB {
      $$ = new Exp(5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;
    }
  | Exp DOT ID {
      $$ = new Exp(6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;

      $$->id_node = new TerminalNode(Id, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      $$->id_node->id_token = $3;
    }
  | ID {
      $$ = new Exp(7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->id_node = new TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->id_node->id_token = $1;
    }
  | INT {
      $$ = new Exp(8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->int_node = new TerminalNode(Int, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->int_node->int_token = $1;
    }
  | FLOAT {
      $$ = new Exp(9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->float_node = new TerminalNode(Float, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->float_node->float_token = $1;
    }
  | CHAR {
      $$ = new Exp(10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->char_node = new TerminalNode(Char, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$->char_node->char_token = $1;
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = new Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = new Exp(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      $$ = new Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Args:
    Exp COMMA Args {
      $$ = new Args(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (Exp *e : $3->node_list) {
        $$->node_list.push_back(e);
      }
    }
  | Exp {
      $$ = new Args(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      $$ = new Args(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
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
      program_root->visit(0);
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
