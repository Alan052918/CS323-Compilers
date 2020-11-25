%{
  #include "include/ast_list.h"
  #include "include/common.h"
  #include "include/typedef.h"

  extern "C" FILE *yyin;

  bool syntax_error;

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
  const char *keyword_value;
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
      Program program = Program(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &program;

      $$->ext_def_list = $1;
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      ExtDefList ext_def_list = ExtDefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ext_def_list;

      $$->node_list.push_back($1);
      for (ExtDef *ext_def : $2->node_list) {
        $$->node_list.push_back(ext_def);
      }
    }
  | %empty {
      ExtDefList ext_def_list = ExtDefList(1, 0, 0, 0, 0);
      $$ = &ext_def_list;
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      ExtDef ext_def = ExtDef(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &ext_def;

      $$->specifier = $1;
      $$->ext_dec_list = $2;
    }
  | Specifier SEMI {
      ExtDef ext_def = ExtDef(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ext_def;

      $$->specifier = $1;
    }
  | Specifier FunDec CompSt {
      ExtDef ext_def = ExtDef(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &ext_def;

      $$->specifier = $1;
      $$->fun_dec = $2;
      $$->comp_st = $3;
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      ExtDef ext_def = ExtDef(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &ext_def;
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      ExtDef ext_def = ExtDef(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ext_def;
    }
  ;
ExtDecList:
    VarDec {
      ExtDecList ext_dec_list = ExtDecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &ext_dec_list;

      $$->node_list.push_back($1);
    }
  | VarDec COMMA ExtDecList {
      ExtDecList ext_dec_list = ExtDecList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &ext_dec_list;

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
      Specifier specifier = Specifier(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &specifier;

      TerminalNode type_node = TerminalNode(Type, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(type_node.type_token, $1);
      $$->type_node = &type_node;
    }
  | StructSpecifier {
      Specifier specifier = Specifier(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &specifier;

      $$->struct_specifier = $1;
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      StructSpecifier struct_specifier = StructSpecifier(0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &struct_specifier;

      TerminalNode id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node.id_token, $2);
      $$->id_node = &id_node;

      $$->def_list = $4;
    }
  | STRUCT ID {
      StructSpecifier struct_specifier = StructSpecifier(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &struct_specifier;

      TerminalNode id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node.id_token, $2);
      $$->id_node = &id_node;
    }
  ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec:
    ID {
      VarDec var_dec = VarDec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &var_dec;

      TerminalNode id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node.id_token, $1);
      $$->id_node = &id_node;
    }
  | VarDec LB INT RB {
      VarDec var_dec = VarDec(1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &var_dec;

      $$->var_dec = $1;

      TerminalNode int_node = TerminalNode(Int, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      int_node.int_token = $3;
      $$->int_node = &int_node;
    }
  | UNKNOWN_LEXEME error {
      VarDec var_dec = VarDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &var_dec;
    }
  ;
FunDec:
    ID LP VarList RP {
      FunDec fun_dec = FunDec(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &fun_dec;

      TerminalNode id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node.id_token, $2);
      $$->id_node = &id_node;

      $$->var_list = $3;
    }
  | ID LP RP {
      FunDec fun_dec = FunDec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &fun_dec;

      TerminalNode id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node.id_token, $2);
      $$->id_node = &id_node;
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      FunDec fun_dec = FunDec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &fun_dec;
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      FunDec fun_dec = FunDec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &fun_dec;
    }
  ;
VarList:
    ParamDec COMMA VarList {
      VarList var_list = VarList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &var_list;

      $$->node_list.push_back($1);
      for (ParamDec *param_dec : $3->node_list) {
        $$->node_list.push_back(param_dec);
      }
    }
  | ParamDec {
      VarList var_list = VarList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &var_list;

      $$->node_list.push_back($1);
    }
  ;
ParamDec:
    Specifier VarDec {
      ParamDec param_dec = ParamDec(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &param_dec;

      $$->specifier = $1;
      $$->var_dec = $2;
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      ParamDec param_dec = ParamDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &param_dec;
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
      CompSt comp_st = CompSt(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &comp_st;

      $$->def_list = $2;
      $$->stmt_list = $3;
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      CompSt comp_st = CompSt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &comp_st;
    }
  ;
StmtList:
    Stmt StmtList {
      StmtList stmt_list = StmtList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &stmt_list;

      $$->node_list.push_back($1);
      for (Stmt *stmt : $2->node_list) {
        $$->node_list.push_back(stmt);
      }
    }
  | %empty {
      StmtList stmt_list = StmtList(1, 0, 0, 0, 0);
      $$ = &stmt_list;
    }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      StmtList stmt_list = StmtList(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &stmt_list;
    }
  ;
Stmt:
    Exp SEMI {
      Stmt stmt = Stmt(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &stmt;

      $$->exp = $1;
    }
  | CompSt {
      Stmt stmt = Stmt(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &stmt;

      $$->comp_st = $1;
    }
  | RETURN Exp SEMI {
      Stmt stmt = Stmt(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &stmt;

      $$->exp = $2;
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      Stmt stmt = Stmt(3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &stmt;

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      Stmt stmt = Stmt(4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      $$ = &stmt;

      $$->exp = $3;
      $$->stmt_1 = $5;
      $$->stmt_2 = $7;
    }
  | WHILE LP Exp RP Stmt {
      Stmt stmt = Stmt(5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &stmt;

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt stmt = Stmt(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &stmt;
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt stmt = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &stmt;
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt stmt = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &stmt;
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      Stmt stmt = Stmt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &stmt;
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      DefList def_list = DefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &def_list;

      $$->node_list.push_back($1);
      for (Def *def : $2->node_list) {
        $$->node_list.push_back(def);
      }
    }
  | %empty  {
      DefList def_list = DefList(1, 0, 0, 0, 0);
      $$ = &def_list;
    }
  ;
Def:
    Specifier DecList SEMI {
      Def def = Def(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &def;

      $$->specifier = $1;
      $$->dec_list = $2;
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Def def = Def(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &def;
    }
  ;
DecList:
    Dec {
      DecList dec_list = DecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &dec_list;

      $$->node_list.push_back($1);
    }
  | Dec COMMA DecList {
      DecList dec_list = DecList(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &dec_list;

      $$->node_list.push_back($1);
      for (Dec *dec : $3->node_list) {
        $$->node_list.push_back(dec);
      }
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      DecList dec_list = DecList(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &dec_list;
    }
  ;
Dec:
    VarDec {
      Dec dec = Dec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &dec;

      $$->var_dec = $1;
    }
  | VarDec ASSIGN Exp {
      Dec dec = Dec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &dec;

      $$->var_dec = $1;
      $$->exp = $3;
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      Dec dec = Dec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &dec;
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      Dec dec = Dec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &dec;
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp AND Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp OR Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp LT Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp LE Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp GT Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp GE Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp NE Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp EQ Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp PLUS Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp MINUS Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp MUL Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | Exp DIV Exp {
      Exp exp = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node.keyword_token, $2);
      $$->keyword_node = &keyword_node;
    }
  | LP Exp RP {
      Exp exp = Exp(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $2;
    }
  | MINUS Exp {
      Exp exp = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &exp;

      TerminalNode keyword_node = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(keyword_node.keyword_token, $1);
      $$->keyword_node = &keyword_node;

      $$->exp_1 = $2;
    }
  | NOT Exp {
      Exp exp = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &exp;

      TerminalNode keyword_node = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(keyword_node.keyword_token, $1);
      $$->keyword_node = &keyword_node;

      $$->exp_1 = $2;
    }
  | ID LP Args RP {
      Exp exp = Exp(3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &exp;

      TerminalNode id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node.id_token, $1);
      $$->id_node = &id_node;

      $$->args = $3;
    }
  | ID LP RP {
      Exp exp = Exp(4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      TerminalNode id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node.id_token, $1);
      $$->id_node = &id_node;
    }
  | Exp LB Exp RB {
      Exp exp = Exp(5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &exp;

      $$->exp_1 = $1;
      $$->exp_2 = $3;
    }
  | Exp DOT ID {
      Exp exp = Exp(6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;

      $$->exp_1 = $1;

      TerminalNode id_node = TerminalNode(Id, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      strcpy(id_node.id_token, $3);
      $$->id_node = &id_node;
    }
  | ID {
      Exp exp = Exp(7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &exp;

      TerminalNode id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node.id_token, $1);
      $$->id_node = &id_node;
    }
  | INT {
      Exp exp = Exp(8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &exp;

      TerminalNode int_node = TerminalNode(Int, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      int_node.int_token = $1;
      $$->int_node = &int_node;
    }
  | FLOAT {
      Exp exp = Exp(9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &exp;

      TerminalNode float_node = TerminalNode(Float, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      float_node.float_token = $1;
      $$->float_node = &float_node;
    }
  | CHAR {
      Exp exp = Exp(10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &exp;

      TerminalNode char_node = TerminalNode(Char, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(char_node.char_token, $1);
      $$->char_node = &char_node;
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      Exp exp = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      Exp exp = Exp(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &exp;
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      Exp exp = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &exp;
    }
  ;
Args:
    Exp COMMA Args {
      Args args = Args(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &args;

      $$->node_list.push_back($1);
      for (Exp *exp : $3->node_list) {
        $$->node_list.push_back(exp);
      }
    }
  | Exp {
      Args args = Args(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &args;

      $$->node_list.push_back($1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      Args args = Args(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &args;
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
