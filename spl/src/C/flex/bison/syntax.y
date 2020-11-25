%{
  #include "include/ast/ast.h"
  #include "include/ast/ast_list.h"
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
      // $$ = lhs(Program, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      // program_root = $$;
      $$ = Program(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->ext_def_list = $1;
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      // $$ = lhs(ExtDefList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      $$ = ExtDefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->node_list.push_back($1);
      for (ExtDef *ext_def : $2->node_list) {
        $$->node_list.push_back(ext_def);
      }
    }
  | %empty {
      // $$ = lhs(Nil, 1, 0, 0, 0, 0);
      $$ = ExtDefList(1, 0, 0, 0, 0);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      // $$ = lhs(ExtDef, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      // push_keyword($$, $3);
      $$ = ExtDef(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->ext_dec_list = $2;
    }
  | Specifier SEMI {
      // $$ = lhs(ExtDef, 1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      $$ = ExtDef(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->specifier = $1;
    }
  | Specifier FunDec CompSt {
      // $$ = lhs(ExtDef, 2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      // push_nonterminal($$, $3);
      $$ = ExtDef(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->fun_dec = $2;
      $$->comp_st = $3;
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      // $$ = lhs(ExtDef, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = ExtDef(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      // $$ = lhs(ExtDef, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = ExtDef(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
ExtDecList:
    VarDec {
      // $$ = lhs(ExtDecList, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = ExtDecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | VarDec COMMA ExtDecList {
      // $$ = lhs(ExtDecList, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = ExtDecList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

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
      // $$ = lhs(Specifier, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_type($$, $1);
      $$ = Specifier(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *type_node = TerminalNode(Type, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(type_node->type_token, $1);
      $$->type_node = type_node;
    }
  | StructSpecifier {
      // $$ = lhs(Specifier, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = StructSpecifier(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->struct_specifier = $1;
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      // $$ = lhs(StructSpecifier, 0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      // push_keyword($$, $1);
      // push_id($$, $2);
      // push_keyword($$, $3);
      // push_nonterminal($$, $4);
      // push_keyword($$, $5);
      $$ = StructSpecifier(0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      TerminalNode *id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node->id_token, $2);
      $$->id_node = id_node;

      $$->def_list = $4;
    }
  | STRUCT ID {
      // $$ = lhs(StructSpecifier, 1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_keyword($$, $1);
      // push_id($$, $2);
      $$ = StructSpecifier(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      TerminalNode *id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node->id_token, $2);
      $$->id_node = id_node;
    }
  ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec:
    ID {
      // $$ = lhs(VarDec, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_id($$, $1);
      $$ = VarDec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node->id_token, $1);
      $$->id_node = id_node;
    }
  | VarDec LB INT RB {
      // $$ = lhs(VarDec, 1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_int($$, $3);
      // push_keyword($$, $4);
      $$ = VarDec(1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->var_dec = $1;

      TerminalNode *int_node = TerminalNode(Int, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      int_node->int_token = $3;
      $$->int_node = int_node;
    }
  | UNKNOWN_LEXEME error {
      // $$ = lhs(VarDec, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = VarDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  ;
FunDec:
    ID LP VarList RP {
      // $$ = lhs(FunDec, 0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      // push_id($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      $$ = FunDec(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      TerminalNode *id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node->id_token, $2);
      $$->id_node = id_node;

      $$->var_list = $3;
    }
  | ID LP RP {
      // $$ = lhs(FunDec, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_id($$, $1);
      // push_keyword($$, $2);
      // push_keyword($$, $3);
      $$ = FunDec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      TerminalNode *id_node = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(id_node->id_token, $2);
      $$->id_node = id_node;
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      // $$ = lhs(FunDec, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = FunDec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      // $$ = lhs(FunDec, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = FunDec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
VarList:
    ParamDec COMMA VarList {
      // $$ = lhs(VarList, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = VarList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (ParamDec *param_dec : $3->node_list) {
        $$->node_list.push_back(param_dec);
      }
    }
  | ParamDec {
      // $$ = lhs(VarList, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = VarList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  ;
ParamDec:
    Specifier VarDec {
      // $$ = lhs(ParamDec, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      $$ = ParamDec(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->specifier = $1;
      $$->var_dec = $2;
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      // $$ = lhs(ParamDec, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = ParamDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
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
      // $$ = lhs(CompSt, 0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      // push_keyword($$, $1);
      // push_nonterminal($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      $$ = CompSt(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->def_list = $2;
      $$->stmt_list = $3;
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      // $$ = lhs(CompSt, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = CompSt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
StmtList:
    Stmt StmtList {
      // $$ = lhs(StmtList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      $$ = StmtList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->node_list.push_back($1);
      for (Stmt *stmt : $2->node_list) {
        $$->node_list.push_back(stmt);
      }
    }
  | %empty {
      // $$ = lhs(Nil, 1, 0, 0, 0, 0);
      $$ = StmtList(1, 0, 0, 0, 0);
    }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      // $$ = lhs(StmtList, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = StmtList(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Stmt:
    Exp SEMI {
      // $$ = lhs(Stmt, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      $$ = Stmt(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->exp = $1;
    }
  | CompSt {
      // $$ = lhs(Stmt, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = Stmt(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->comp_st = $1;
    }
  | RETURN Exp SEMI {
      // $$ = lhs(Stmt, 2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_keyword($$, $1);
      // push_nonterminal($$, $2);
      // push_keyword($$, $3);
      $$ = Stmt(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp = $2;
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      // $$ = lhs(Stmt, 3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      // push_keyword($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      // push_nonterminal($$, $5);
      $$ = Stmt(3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      // $$ = lhs(Stmt, 4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      // push_keyword($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      // push_nonterminal($$, $5);
      // push_keyword($$, $6);
      // push_nonterminal($$, $7);
      $$ = Stmt(4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
      $$->stmt_2 = $7;
    }
  | WHILE LP Exp RP Stmt {
      // $$ = lhs(Stmt, 5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      // push_keyword($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      // push_nonterminal($$, $5);
      $$ = Stmt(5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      // $$ = lhs(Stmt, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = Stmt(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      // $$ = lhs(Stmt, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      // $$ = lhs(Stmt, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      // $$ = lhs(Stmt, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = Stmt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      // $$ = lhs(DefList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      $$ = DefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      $$->def = $1;
      $$->def_list = $2;
    }
  | %empty  {
      // $$ = lhs(Nil, 1, 0, 0, 0, 0);
      $$ = DefList(1, 0, 0, 0, 0);
    }
  ;
Def:
    Specifier DecList SEMI {
      // $$ = lhs(Def, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_nonterminal($$, $2);
      // push_keyword($$, $3);
      $$ = Def(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->specifier = $1;
      $$->dec_list = $2;
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      // $$ = lhs(Def, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Def(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
DecList:
    Dec {
      // $$ = lhs(DecList, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = DecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | Dec COMMA DecList {
      // $$ = lhs(DecList, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = DecList(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (Dec *dec : $3->node_list) {
        $$->node_list.push_back(dec);
      }
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      // $$ = lhs(DecList, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = DecList(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
Dec:
    VarDec {
      // $$ = lhs(Dec, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = Dec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->var_dec = $1;
    }
  | VarDec ASSIGN Exp {
      // $$ = lhs(Dec, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Dec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->var_dec = $1;
      $$->exp = $3;
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      // $$ = lhs(Dec, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = Dec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      // $$ = lhs(Dec, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Dec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp AND Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp OR Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp LT Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp LE Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp GT Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp GE Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp NE Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp EQ Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp PLUS Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp MINUS Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp MUL Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | Exp DIV Exp {
      // $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode *keyword_node = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      strcpy(keyword_node->keyword_token, $2);
      $$->keyword_node = keyword_node;
    }
  | LP Exp RP {
      // $$ = lhs(Exp, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_keyword($$, $1);
      // push_nonterminal($$, $2);
      // push_keyword($$, $3);
      $$ = Exp(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $2;
    }
  | MINUS Exp {
      // $$ = lhs(Exp, 2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_keyword($$, $1);
      // push_nonterminal($$, $2);
      $$ = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      TerminalNode *keyword_node = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(keyword_node->keyword_token, $1);
      $$->keyword_node = keyword_node;

      $$->exp_1 = $2;
    }
  | NOT Exp {
      // $$ = lhs(Exp, 2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      // push_keyword($$, $1);
      // push_nonterminal($$, $2);
      $$ = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);

      TerminalNode *keyword_node = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(keyword_node->keyword_token, $1);
      $$->keyword_node = keyword_node;

      $$->exp_1 = $2;
    }
  | ID LP Args RP {
      // $$ = lhs(Exp, 3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      // push_id($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      $$ = Exp(3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      TerminalNode *id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node->id_token, $1);
      $$->id_node = id_node;

      $$->args = $3;
    }
  | ID LP RP {
      // $$ = lhs(Exp, 4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_id($$, $1);
      // push_keyword($$, $2);
      // push_keyword($$, $3);
      $$ = Exp(4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      TerminalNode *id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node->id_token, $1);
      $$->id_node = id_node;
    }
  | Exp LB Exp RB {
      // $$ = lhs(Exp, 5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      // push_keyword($$, $4);
      $$ = Exp(5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);

      $$->exp_1 = $1;
      $$->exp_2 = $3;
    }
  | Exp DOT ID {
      // $$ = lhs(Exp, 6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_id($$, $3);
      $$ = Exp(6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->exp_1 = $1;

      TerminalNode *id_node = TerminalNode(Id, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      strcpy(id_node->id_token, $3);
      $$->id_node = id_node;
    }
  | ID {
      // $$ = lhs(Exp, 7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_id($$, $1);
      $$ = Exp(7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *id_node = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(id_node->id_token, $1);
      $$->id_node = id_node;
    }
  | INT {
      // $$ = lhs(Exp, 8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_int($$, $1);
      $$ = Exp(8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *int_node = TerminalNode(Int, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      int_node->int_token = $1;
      $$->int_node = int_node;
    }
  | FLOAT {
      // $$ = lhs(Exp, 9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_float($$, $1);
      $$ = Exp(9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *float_node = TerminalNode(Float, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      float_node->float_token = $1;
      $$->float_node = float_node;
    }
  | CHAR {
      // $$ = lhs(Exp, 10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_char($$, $1);
      $$ = Exp(10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      TerminalNode *char_node = TerminalNode(Char, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      strcpy(char_node->char_token, $1);
      $$->char_node = char_node;
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      // $$ = lhs(Exp, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      // $$ = lhs(Exp, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Exp(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      // $$ = lhs(Exp, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Args:
    Exp COMMA Args {
      // $$ = lhs(Args, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      // push_nonterminal($$, $1);
      // push_keyword($$, $2);
      // push_nonterminal($$, $3);
      $$ = Args(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);

      $$->node_list.push_back($1);
      for (Exp *exp : $3->node_list) {
        $$->node_list.push_back(exp);
      }
    }
  | Exp {
      // $$ = lhs(Args, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      // push_nonterminal($$, $1);
      $$ = Args(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);

      $$->node_list.push_back($1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      // $$ = lhs(Args, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = Args(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

%%

/* #include "src/C/parsetree.cpp"
#include "src/C/visitor.cpp" */

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
      /* visit_Program(program_root); */
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
