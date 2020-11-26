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
      Program p = Program(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &p;

      $$->ext_def_list = $1;
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      ExtDefList edl = ExtDefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &edl;

      $$->node_list.push_back($1);
      for (ExtDef *ed : $2->node_list) {
        $$->node_list.push_back(ed);
      }
    }
  | %empty {
      ExtDefList edl = ExtDefList(1, 0, 0, 0, 0);
      $$ = &edl;
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      ExtDef ed = ExtDef(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &ed;

      $$->specifier = $1;
      $$->ext_dec_list = $2;
    }
  | Specifier SEMI {
      ExtDef ed = ExtDef(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ed;

      $$->specifier = $1;
    }
  | Specifier FunDec CompSt {
      ExtDef ed = ExtDef(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &ed;

      $$->specifier = $1;
      $$->fun_dec = $2;
      $$->comp_st = $3;
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      ExtDef ed = ExtDef(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &ed;
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      ExtDef ed = ExtDef(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ed;
    }
  ;
ExtDecList:
    VarDec {
      ExtDecList edl = ExtDecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &edl;

      $$->node_list.push_back($1);
    }
  | VarDec COMMA ExtDecList {
      ExtDecList edl = ExtDecList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &edl;

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
      Specifier s = Specifier(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &s;

      TerminalNode tn = TerminalNode(Type, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      tn.type_token = $1;
      $$->type_node = &tn;
    }
  | StructSpecifier {
      Specifier s = Specifier(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &s;

      $$->struct_specifier = $1;
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      StructSpecifier ss = StructSpecifier(0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &ss;

      TerminalNode in = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      in.id_token = $2;
      $$->id_node = &in;

      $$->def_list = $4;
    }
  | STRUCT ID {
      StructSpecifier ss = StructSpecifier(1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &ss;

      TerminalNode in = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      in.id_token = $2;
      $$->id_node = &in;
    }
  ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec:
    ID {
      VarDec vd = VarDec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &vd;

      TerminalNode in = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      in.id_token = $1;
      $$->id_node = &in;
    }
  | VarDec LB INT RB {
      VarDec vd = VarDec(1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &vd;

      $$->var_dec = $1;

      TerminalNode in = TerminalNode(Int, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      in.int_token = $3;
      $$->int_node = &in;
    }
  | UNKNOWN_LEXEME error {
      VarDec vd = VarDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &vd;
    }
  ;
FunDec:
    ID LP VarList RP {
      FunDec fd = FunDec(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &fd;

      TerminalNode in = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      in.id_token = $2;
      $$->id_node = &in;

      $$->var_list = $3;
    }
  | ID LP RP {
      FunDec fd = FunDec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &fd;

      TerminalNode in = TerminalNode(Id, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      in.id_token = $2;
      $$->id_node = &in;
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      FunDec fd = FunDec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &fd;
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      FunDec fd = FunDec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &fd;
    }
  ;
VarList:
    ParamDec COMMA VarList {
      VarList vl = VarList(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &vl;

      $$->node_list.push_back($1);
      for (ParamDec *pd : $3->node_list) {
        $$->node_list.push_back(pd);
      }
    }
  | ParamDec {
      VarList vl = VarList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &vl;

      $$->node_list.push_back($1);
    }
  ;
ParamDec:
    Specifier VarDec {
      ParamDec pd = ParamDec(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &pd;

      $$->specifier = $1;
      $$->var_dec = $2;
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      ParamDec pd = ParamDec(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &pd;
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
      CompSt cs = CompSt(0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &cs;

      $$->def_list = $2;
      $$->stmt_list = $3;
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      CompSt cs = CompSt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &cs;
    }
  ;
StmtList:
    Stmt StmtList {
      StmtList sl = StmtList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &sl;

      $$->node_list.push_back($1);
      for (Stmt *stmt : $2->node_list) {
        $$->node_list.push_back(stmt);
      }
    }
  | %empty {
      StmtList sl = StmtList(1, 0, 0, 0, 0);
      $$ = &sl;
    }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      StmtList sl = StmtList(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &sl;
    }
  ;
Stmt:
    Exp SEMI {
      Stmt s = Stmt(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &s;

      $$->exp = $1;
    }
  | CompSt {
      Stmt s = Stmt(1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &s;

      $$->comp_st = $1;
    }
  | RETURN Exp SEMI {
      Stmt s = Stmt(2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &s;

      $$->exp = $2;
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      Stmt s = Stmt(3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &s;

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      Stmt s = Stmt(4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      $$ = &s;

      $$->exp = $3;
      $$->stmt_1 = $5;
      $$->stmt_2 = $7;
    }
  | WHILE LP Exp RP Stmt {
      Stmt s = Stmt(5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      $$ = &s;

      $$->exp = $3;
      $$->stmt_1 = $5;
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt s = Stmt(-1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &s;
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt s = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &s;
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Stmt s = Stmt(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &s;
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      Stmt s = Stmt(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &s;
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      DefList dl = DefList(0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &dl;

      $$->node_list.push_back($1);
      for (Def *d : $2->node_list) {
        $$->node_list.push_back(d);
      }
    }
  | %empty  {
      DefList dl = DefList(1, 0, 0, 0, 0);
      $$ = &dl;
    }
  ;
Def:
    Specifier DecList SEMI {
      Def d = Def(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &d;

      $$->specifier = $1;
      $$->dec_list = $2;
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      Def d = Def(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &d;
    }
  ;
DecList:
    Dec {
      DecList dl = DecList(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &dl;

      $$->node_list.push_back($1);
    }
  | Dec COMMA DecList {
      DecList dl = DecList(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &dl;

      $$->node_list.push_back($1);
      for (Dec *dec : $3->node_list) {
        $$->node_list.push_back(dec);
      }
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      DecList dl = DecList(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &dl;
    }
  ;
Dec:
    VarDec {
      Dec d = Dec(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &d;

      $$->var_dec = $1;
    }
  | VarDec ASSIGN Exp {
      Dec d = Dec(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &d;

      $$->var_dec = $1;
      $$->exp = $3;
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      Dec d = Dec(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &d;
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      Dec d = Dec(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &d;
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp AND Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp OR Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp LT Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp LE Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp GT Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp GE Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp NE Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp EQ Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp PLUS Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp MINUS Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp MUL Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | Exp DIV Exp {
      Exp e = Exp(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;

      TerminalNode kn = TerminalNode(Keyword, @2.first_line, @2.last_line, @2.first_column, @2.last_column);
      kn.keyword_token = $2;
      $$->keyword_node = &kn;
    }
  | LP Exp RP {
      Exp e = Exp(1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $2;
    }
  | MINUS Exp {
      Exp e = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &e;

      TerminalNode kn = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      kn.keyword_token = $1;
      $$->keyword_node = &kn;

      $$->exp_1 = $2;
    }
  | NOT Exp {
      Exp e = Exp(2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &e;

      TerminalNode kn = TerminalNode(Keyword, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      kn.keyword_token = $1;
      $$->keyword_node = &kn;

      $$->exp_1 = $2;
    }
  | ID LP Args RP {
      Exp e = Exp(3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &e;

      TerminalNode in = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      in.id_token = $1;
      $$->id_node = &in;

      $$->args = $3;
    }
  | ID LP RP {
      Exp e = Exp(4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      TerminalNode in = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      in.id_token = $1;
      $$->id_node = &in;
    }
  | Exp LB Exp RB {
      Exp e = Exp(5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      $$ = &e;

      $$->exp_1 = $1;
      $$->exp_2 = $3;
    }
  | Exp DOT ID {
      Exp e = Exp(6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;

      $$->exp_1 = $1;

      TerminalNode in = TerminalNode(Id, @3.first_line, @3.last_line, @3.first_column, @3.last_column);
      in.id_token = $3;
      $$->id_node = &in;
    }
  | ID {
      Exp e = Exp(7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &e;

      TerminalNode in = TerminalNode(Id, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      in.id_token = $1;
      $$->id_node = &in;
    }
  | INT {
      Exp e = Exp(8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &e;

      TerminalNode in = TerminalNode(Int, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      in.int_token = $1;
      $$->int_node = &in;
    }
  | FLOAT {
      Exp e = Exp(9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &e;

      TerminalNode fn = TerminalNode(Float, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      fn.float_token = $1;
      $$->float_node = &fn;
    }
  | CHAR {
      Exp e = Exp(10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &e;

      TerminalNode cn = TerminalNode(Char, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      cn.char_token = $1;
      $$->char_node = &cn;
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      Exp e = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      Exp e = Exp(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &e;
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      Exp e = Exp(-1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &e;
    }
  ;
Args:
    Exp COMMA Args {
      Args a = Args(0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      $$ = &a;

      $$->node_list.push_back($1);
      for (Exp *e : $3->node_list) {
        $$->node_list.push_back(e);
      }
    }
  | Exp {
      Args a = Args(0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      $$ = &a;

      $$->node_list.push_back($1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      Args a = Args(-1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      $$ = &a;
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
