%{
  #include <cstdio>
  #include <iostream>
  #include <string>
  #include "include/astdef.h"

  using namespace std;

  extern "C" FILE *yyin;

  int syntax_error;
  Node *program_root;

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
  struct Node *nonterminal_node;
}

%type <nonterminal_node> Program
%type <nonterminal_node> ExtDefList ExtDef ExtDecList
%type <nonterminal_node> Specifier StructSpecifier
%type <nonterminal_node> VarDec FunDec VarList ParamDec
%type <nonterminal_node> CompSt StmtList Stmt
%type <nonterminal_node> DefList Def DecList Dec
%type <nonterminal_node> Exp Args

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
      $$ = lhs(Program, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      $$ = lhs(ExtDefList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty {
      $$ = lhs(Nil, 0, 0, 0, 0);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      $$ = lhs(ExtDef, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | Specifier SEMI {
      $$ = lhs(ExtDef, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | Specifier FunDec CompSt {
      $$ = lhs(ExtDef, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(ExtDef, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(ExtDef, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
ExtDecList:
    VarDec {
      $$ = lhs(ExtDecList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec COMMA ExtDecList {
      $$ = lhs(ExtDecList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier:
    TYPE {
      $$ = lhs(Specifier, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_type($$, $1);
    }
  | StructSpecifier {
      $$ = lhs(Specifier, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      $$ = lhs(StructSpecifier, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_id($$, $2);
      push_keyword($$, $3);
      push_nonterminal($$, $4);
      push_keyword($$, $5);
    }
  | STRUCT ID {
      $$ = lhs(StructSpecifier, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_id($$, $2);
    }
  ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec:
    ID {
      $$ = lhs(VarDec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
    }
  | VarDec LB INT RB {
      $$ = lhs(VarDec, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_int($$, $3);
      push_keyword($$, $4);
    }
  | UNKNOWN_LEXEME error {
      $$ = lhs(VarDec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  ;
FunDec:
    ID LP VarList RP {
      $$ = lhs(FunDec, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lhs(FunDec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(FunDec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(FunDec, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
VarList:
    ParamDec COMMA VarList {
      $$ = lhs(VarList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | ParamDec {
      $$ = lhs(VarList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
ParamDec:
    Specifier VarDec {
      $$ = lhs(ParamDec, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(ParamDec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
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
      $$ = lhs(CompSt, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      $$ = lhs(CompSt, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
StmtList:
    Stmt StmtList {
      $$ = lhs(StmtList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty { $$ = lhs(Nil, 0, 0, 0, 0); }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(StmtList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Stmt:
    Exp SEMI {
      $$ = lhs(Stmt, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | CompSt {
      $$ = lhs(Stmt, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | RETURN Exp SEMI {
      $$ = lhs(Stmt, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      $$ = lhs(Stmt, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      $$ = lhs(Stmt, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
      push_keyword($$, $6);
      push_nonterminal($$, $7);
    }
  | WHILE LP Exp RP Stmt {
      $$ = lhs(Stmt, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      $$ = lhs(Stmt, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      $$ = lhs(DefList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty  { $$ = lhs(Nil, 0, 0, 0, 0); }
  ;
Def:
    Specifier DecList SEMI {
      $$ = lhs(Def, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Def, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
DecList:
    Dec {
      $$ = lhs(DecList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | Dec COMMA DecList {
      $$ = lhs(DecList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      $$ = lhs(DecList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
Dec:
    VarDec {
      $$ = lhs(Dec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec ASSIGN Exp {
      $$ = lhs(Dec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      $$ = lhs(Dec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      $$ = lhs(Dec, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp AND Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp OR Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LT Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LE Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GT Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GE Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp NE Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp EQ Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp PLUS Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MINUS Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MUL Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp DIV Exp {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | LP Exp RP {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3); }
  | MINUS Exp {
      $$ = lhs(Exp, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | NOT Exp {
      $$ = lhs(Exp, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | ID LP Args RP {
      $$ = lhs(Exp, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  | Exp LB Exp RB {
      $$ = lhs(Exp, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | Exp DOT ID {
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_id($$, $3);
    }
  | ID {
      $$ = lhs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
    }
  | INT {
      $$ = lhs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_int($$, $1);
    }
  | FLOAT {
      $$ = lhs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_float($$, $1);
    }
  | CHAR {
      $$ = lhs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_char($$, $1);
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(Exp, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      $$ = lhs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Args:
    Exp COMMA Args {
      $$ = lhs(Args, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp {
      $$ = lhs(Args, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      $$ = lhs(Args, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

%%

Node *lhs(int nonterminal_type, int first_line, int last_line, int first_column, int last_column) {
  Node *new_nonterminal_node = (Node *)malloc(sizeof(Node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->first_line = first_line;
  new_nonterminal_node->last_line = last_line;
  new_nonterminal_node->first_column = first_column;
  new_nonterminal_node->last_column = last_column;
  new_nonterminal_node->rhs = NULL;
#ifdef DEBUG
  printf(" lhs: ");
  get_nonterminal_name(nonterminal_type);
  printf("[%d], line %d\n", nonterminal_type, new_nonterminal_node->first_line);
#endif
  return new_nonterminal_node;
}

void push_int(Node *lhs_node, int int_val) {
#ifdef DEBUG
  printf("    push int: %d, line %d\n", int_val, yylloc.first_line);
#endif
  Node *new_int_node = (Node *)malloc(sizeof(Node));
  new_int_node->node_type = INT_T;
  new_int_node->int_token = int_val;
  new_int_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_int_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_float(Node *lhs_node, float float_val) {
#ifdef DEBUG
  printf("    push float: %f, line %d\n", float_val, yylloc.first_line);
#endif
  Node *new_float_node = (Node *)malloc(sizeof(Node));
  new_float_node->node_type = FLOAT_T;
  new_float_node->float_token = float_val;
  new_float_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_float_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_char(Node *lhs_node, char *char_val) {
#ifdef DEBUG
  printf("    push char: %s, line %d\n", char_val, yylloc.first_line);
#endif
  Node *new_char_node = (Node *)malloc(sizeof(Node));
  new_char_node->node_type = CHAR_T;
  new_char_node->char_token = char_val;
  new_char_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_char_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_type(Node *lhs_node, char *type_val) {
#ifdef DEBUG
  printf("    push type: %s, line %d\n", type_val, yylloc.first_line);
#endif
  Node *new_type_node = (Node *)malloc(sizeof(Node));
  new_type_node->node_type = TYPE_T;
  new_type_node->type_token = type_val;
  new_type_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_type_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_id(Node *lhs_node, char *id_val) {
#ifdef DEBUG
  printf("    push id: %s, line %d\n", id_val, yylloc.first_line);
#endif
  Node *new_id_node = (Node *)malloc(sizeof(Node));
  new_id_node->node_type = ID_T;
  new_id_node->id_token = id_val;
  new_id_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_id_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_keyword(Node *lhs_node, const char *keyword_val) {
#ifdef DEBUG
  printf("    push keyword: %s, line %d\n", keyword_val, yylloc.first_line);
#endif
  Node *new_keyword_node = (Node *)malloc(sizeof(Node));
  new_keyword_node->node_type = KEYWORD_T;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_keyword_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_nonterminal(Node *lhs_node, Node *nonterminal) {
#ifdef DEBUG
  printf("    push nonterminal: ");
  get_nonterminal_name(nonterminal->nonterminal_token);
  printf(", line %d\n", yylloc.first_line);
#endif
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = nonterminal;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lhs_node->rhs;
  if (ptr == NULL) {
    lhs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void get_nonterminal_name(int nonterminal_val) {
  switch (nonterminal_val) {
    case Program: printf("Program"); break;
    case ExtDefList: printf("ExtDefList"); break;
    case ExtDef: printf("ExtDef"); break;
    case ExtDecList: printf("ExtDecList"); break;
    case Specifier: printf("Specifier"); break;
    case StructSpecifier: printf("StructSpecifier"); break;
    case VarDec: printf("VarDec"); break;
    case FunDec: printf("FunDec"); break;
    case VarList: printf("VarList"); break;
    case ParamDec: printf("ParamDec"); break;
    case CompSt: printf("CompSt"); break;
    case StmtList: printf("StmtList"); break;
    case Stmt: printf("Stmt"); break;
    case DefList: printf("DefList"); break;
    case Def: printf("Def"); break;
    case DecList: printf("DecList"); break;
    case Dec: printf("Dec"); break;
    case Exp: printf("Exp"); break;
    case Args: printf("Args"); break;
    case Nil: printf("Nil"); break;
    default: printf("Undefined nonterminal type!"); break;
  }
}

void print_tree(Node *pnode, int indent_depth) {
  if (pnode->node_type == NONTERMINAL_T && pnode->nonterminal_token == Nil) {
    return;
  }
  for (int i = 0; i < indent_depth; i++) {
    printf(" ");
  }
  switch (pnode->node_type) {
    case INT_T: printf("INT: %ld\n", pnode->int_token); break;
    case FLOAT_T: printf("FLOAT: %f\n", pnode->float_token); break;
    case CHAR_T: printf("CHAR: %s\n", pnode->char_token); break;
    case TYPE_T: printf("TYPE: %s\n", pnode->type_token); break;
    case ID_T: printf("ID: %s\n", pnode->id_token); break;
    case KEYWORD_T: printf("%s\n", pnode->keyword_token); break;
    case NONTERMINAL_T: 
      get_nonterminal_name(pnode->nonterminal_token);
      printf(" (%d)\n", pnode->first_line);
      break;
    default: printf("Undefined node type %d\n", pnode->node_type); return;
  }
  Rhs_node *ptr = pnode->rhs;
  if (ptr == NULL) {
    return;
  }
  while (ptr != NULL) {
    print_tree(ptr->token_node, indent_depth + 2);
    ptr = ptr->next;
  }
}

void yyerror(const char *s) {
  syntax_error = 1;
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
    syntax_error = 0;
    int result = yyparse();
    if (result == 0 && syntax_error == 0) {
#ifdef DEBUG
      printf("\n*********************\n");
#endif
      print_tree(program_root, 0);
    } else if (result == 1) {
#ifdef DEBUG
      fprintf(stderr, "Abort\n");
#endif
    } else if (result > 1) {
#ifdef DEBUG
      fprintf(stderr, "Exhausted\n");
#endif
    } else if (syntax_error == 1) {
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
