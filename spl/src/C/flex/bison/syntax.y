%{
  #include <cstdio>
  #include <iostream>
  #include <cstring>
  #include "include/astdef.h"
  #include "include/typedef.h"

  using namespace std;

  extern "C" FILE *yyin;

  int syntax_error;
  Node *program_root;
  FILE *pt;

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
      $$ = lhs(Program, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      $$ = lhs(ExtDefList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty {
      $$ = lhs(Nil, 1, 0, 0, 0, 0);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      $$ = lhs(ExtDef, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | Specifier SEMI {
      $$ = lhs(ExtDef, 1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | Specifier FunDec CompSt {
      $$ = lhs(ExtDef, 2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
    }
  | ExtDecList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(ExtDef, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | Specifier ExtDecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(ExtDef, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
ExtDecList:
    VarDec {
      $$ = lhs(ExtDecList, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec COMMA ExtDecList {
      $$ = lhs(ExtDecList, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
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
      $$ = lhs(Specifier, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_type($$, $1);
    }
  | StructSpecifier {
      $$ = lhs(Specifier, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      $$ = lhs(StructSpecifier, 0, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_id($$, $2);
      push_keyword($$, $3);
      push_nonterminal($$, $4);
      push_keyword($$, $5);
    }
  | STRUCT ID {
      $$ = lhs(StructSpecifier, 1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
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
      $$ = lhs(VarDec, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
    }
  | VarDec LB INT RB {
      $$ = lhs(VarDec, 1, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_int($$, $3);
      push_keyword($$, $4);
    }
  | UNKNOWN_LEXEME error {
      $$ = lhs(VarDec, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  ;
FunDec:
    ID LP VarList RP {
      $$ = lhs(FunDec, 0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lhs(FunDec, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  | ID LP VarList error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(FunDec, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(FunDec, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
VarList:
    ParamDec COMMA VarList {
      $$ = lhs(VarList, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | ParamDec {
      $$ = lhs(VarList, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
ParamDec:
    Specifier VarDec {
      $$ = lhs(ParamDec, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | VarDec error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(ParamDec, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
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
      $$ = lhs(CompSt, 0, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | LC DefList StmtList error {
      printf("Error type B at Line %d: Missing closing curly bracket '}'\n", @$.last_line);
      $$ = lhs(CompSt, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
StmtList:
    Stmt StmtList {
      $$ = lhs(StmtList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty { $$ = lhs(Nil, 1, 0, 0, 0, 0); }
  | Stmt Def StmtList error {
      printf("Error type B at Line %d: Missing specifier\n", @$.first_line);
      $$ = lhs(StmtList, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Stmt:
    Exp SEMI {
      $$ = lhs(Stmt, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | CompSt {
      $$ = lhs(Stmt, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | RETURN Exp SEMI {
      $$ = lhs(Stmt, 2, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      $$ = lhs(Stmt, 3, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      $$ = lhs(Stmt, 4, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
      push_keyword($$, $6);
      push_nonterminal($$, $7);
    }
  | WHILE LP Exp RP Stmt {
      $$ = lhs(Stmt, 5, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  | Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, -1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
    }
  | RETURN Exp error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Stmt, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | RETURN UNKNOWN_LEXEME SEMI error {
      $$ = lhs(Stmt, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      $$ = lhs(DefList, 0, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty  { $$ = lhs(Nil, 1, 0, 0, 0, 0); }
  ;
Def:
    Specifier DecList SEMI {
      $$ = lhs(Def, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | Specifier DecList error {
      printf("Error type B at Line %d: Missing semicolon ';'\n", @$.first_line);
      $$ = lhs(Def, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
DecList:
    Dec {
      $$ = lhs(DecList, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | Dec COMMA DecList {
      $$ = lhs(DecList, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Dec COMMA error {
      printf("Error type B at Line %d: Redundant comma ','\n", @$.first_line);
      $$ = lhs(DecList, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;
Dec:
    VarDec {
      $$ = lhs(Dec, 0, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec ASSIGN Exp {
      $$ = lhs(Dec, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | VarDec ASSIGN UNKNOWN_LEXEME error {
      $$ = lhs(Dec, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | VarDec ASSIGN error {
      printf("Error type B at Line %d: Missing expression at the end of declaration\n", @$.first_line);
      $$ = lhs(Dec, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp AND Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp OR Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LT Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LE Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GT Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GE Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp NE Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp EQ Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp PLUS Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MINUS Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MUL Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp DIV Exp {
      $$ = lhs(Exp, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | LP Exp RP {
      $$ = lhs(Exp, 1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3); }
  | MINUS Exp {
      $$ = lhs(Exp, 2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | NOT Exp {
      $$ = lhs(Exp, 2, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | ID LP Args RP {
      $$ = lhs(Exp, 3, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lhs(Exp, 4, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  | Exp LB Exp RB {
      $$ = lhs(Exp, 5, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | Exp DOT ID {
      $$ = lhs(Exp, 6, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_id($$, $3);
    }
  | ID {
      $$ = lhs(Exp, 7, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
    }
  | INT {
      $$ = lhs(Exp, 8, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_int($$, $1);
    }
  | FLOAT {
      $$ = lhs(Exp, 9, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_float($$, $1);
    }
  | CHAR {
      $$ = lhs(Exp, 10, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_char($$, $1);
    }
  | Exp UNKNOWN_LEXEME Exp error {}
  | ID LP Args error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(Exp, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  | ID LP error {
      printf("Error type B at Line %d: Missing closing parenthesis ')'\n", @$.first_line);
      $$ = lhs(Exp, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  | Exp LB Exp error {
      printf("Error type B at Line %d Missing closing bracket ']'\n", @$.first_line);
      $$ = lhs(Exp, -1, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
    }
  ;
Args:
    Exp COMMA Args {
      $$ = lhs(Args, 0, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp {
      $$ = lhs(Args, 1, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | Exp COMMA error {
      printf("Error type B at Line %d Redundant comma ','\n", @$.first_line);
      $$ = lhs(Args, -1, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
    }
  ;

%%

Node *lhs(int nonterminal_type, int rhsf, int first_line, int last_line,
          int first_column, int last_column) {
  Node *new_nonterminal_node = (Node *)malloc(sizeof(Node));
  memset(new_nonterminal_node, '\0', sizeof(Node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->rhs_form = rhsf;
  new_nonterminal_node->first_line = first_line;
  new_nonterminal_node->last_line = last_line;
  new_nonterminal_node->first_column = first_column;
  new_nonterminal_node->last_column = last_column;
#ifdef DEBUG
  printf(" lhs: ");
  get_nonterminal_name(nonterminal_type);
  printf("[%d], line %d\n", nonterminal_type, new_nonterminal_node->first_line);
#endif
  return new_nonterminal_node;
}

/* Syntax tree actions */

void push_int(Node *lhs_node, int int_val) {
#ifdef DEBUG
  printf("    push int: %d, line %d\n", int_val, yylloc.first_line);
#endif
  Node *new_int_node = (Node *)malloc(sizeof(Node));
  memset(new_int_node, '\0', sizeof(Node));
  new_int_node->node_type = INT_T;
  new_int_node->int_token = int_val;
  new_int_node->rhs_form = -1;
  lhs_node->children.push_back(new_int_node);
}

void push_float(Node *lhs_node, float float_val) {
#ifdef DEBUG
  printf("    push float: %f, line %d\n", float_val, yylloc.first_line);
#endif
  Node *new_float_node = (Node *)malloc(sizeof(Node));
  memset(new_float_node, '\0', sizeof(Node));
  new_float_node->node_type = FLOAT_T;
  new_float_node->float_token = float_val;
  new_float_node->rhs_form = -1;
  lhs_node->children.push_back(new_float_node);
}

void push_char(Node *lhs_node, char *char_val) {
#ifdef DEBUG
  printf("    push char: %s, line %d\n", char_val, yylloc.first_line);
#endif
  Node *new_char_node = (Node *)malloc(sizeof(Node));
  memset(new_char_node, '\0', sizeof(Node));
  new_char_node->node_type = CHAR_T;
  new_char_node->char_token = char_val;
  new_char_node->rhs_form = -1;
  lhs_node->children.push_back(new_char_node);
}

void push_type(Node *lhs_node, char *type_val) {
#ifdef DEBUG
  printf("    push type: %s, line %d\n", type_val, yylloc.first_line);
#endif
  Node *new_type_node = (Node *)malloc(sizeof(Node));
  memset(new_type_node, '\0', sizeof(Node));
  new_type_node->node_type = TYPE_T;
  new_type_node->type_token = type_val;
  new_type_node->rhs_form = -1;
  lhs_node->children.push_back(new_type_node);
}

void push_id(Node *lhs_node, char *id_val) {
#ifdef DEBUG
  printf("    push id: %s, line %d\n", id_val, yylloc.first_line);
#endif
  Node *new_id_node = (Node *)malloc(sizeof(Node));
  memset(new_id_node, '\0', sizeof(Node));
  new_id_node->node_type = ID_T;
  new_id_node->id_token = id_val;
  new_id_node->rhs_form = -1;
  lhs_node->children.push_back(new_id_node);
}

void push_keyword(Node *lhs_node, const char *keyword_val) {
#ifdef DEBUG
  printf("    push keyword: %s, line %d\n", keyword_val, yylloc.first_line);
#endif
  Node *new_keyword_node = (Node *)malloc(sizeof(Node));
  memset(new_keyword_node, '\0', sizeof(Node));
  new_keyword_node->node_type = KEYWORD_T;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs_form = -1;
  lhs_node->children.push_back(new_keyword_node);
}

void push_nonterminal(Node *lhs_node, Node *nonterminal) {
#ifdef DEBUG
  printf("    push nonterminal: ");
  get_nonterminal_name(nonterminal->nonterminal_token);
  printf(", line %d\n", yylloc.first_line);
#endif
  lhs_node->children.push_back(nonterminal);
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

/* Visitor methods */

int visit_Program(Node *program) {
#ifdef DEBUG
  printf("Program (%d)\n", program->first_line);
#endif
  // Program := ExtDefList
  visit_ExtDefList(program->children[0], 1);
}

int visit_ExtDefList(Node *extDefList, int indent_level) {
  if (extDefList->rhs_form == 1) {
    return 0;
  }
#ifdef DEBUG
  print_indentation(indent_level);
  printf("ExtDefList (%d)\n", extDefList->first_line);
#endif
  switch (extDefList->rhs_form) {
    case 0:  // ExtDefList := ExtDef ExtDefList
      visit_ExtDef(extDefList->children[0], indent_level + 1);
      visit_ExtDefList(extDefList->children[1], indent_level + 1);
      break;
    /* case 1:  // ExtDefList := %empty
      break; */

    default:
      fprintf(stderr, "Fail to visit <ExtDefList> Node: line %d\n",
              extDefList->first_line);
      break;
  }
}

int visit_ExtDef(Node *extDef, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("ExtDef (%d)\n", extDef->first_line);
#endif
  switch (extDef->rhs_form) {
    case 0:  // ExtDef := Specifier ExtDecList SEMI
      visit_Specifier(extDef->children[0], indent_level + 1);
      visit_ExtDecList(extDef->children[1], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // ExtDef := Specifier SEMI
      visit_Specifier(extDef->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 2:  // ExtDef := Specifier FunDec CompSt
      visit_Specifier(extDef->children[0], indent_level + 1);
      visit_FunDec(extDef->children[1], indent_level + 1);
      visit_CompSt(extDef->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
              extDef->first_line);
      break;
  }
}

int visit_ExtDecList(Node *extDecList, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("ExtDecList (%d)\n", extDecList->first_line);
#endif
  switch (extDecList->rhs_form) {
    case 0:  // ExtDecList := VarDec
      visit_VarDec(extDecList->children[0], indent_level + 1);
      break;
    case 1:  // ExtDecList := VarDec COMMA ExtDecList
      visit_VarDec(extDecList->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_ExtDecList(extDecList->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDecList> Node: line %d\n",
              extDecList->first_line);
      break;
  }
}

int visit_Specifier(Node *specifier, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Specifier (%d)\n", specifier->first_line);
#endif
  switch (specifier->rhs_form) {
    case 0:  // Specifier := TYPE
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("TYPE: %s\n", specifier->children[0]->type_token);
#endif
      break;
    case 1:  // Specifier := StructSpecifier
      visit_StructSpecifier(specifier->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Specifier> Node: line %d\n",
              specifier->first_line);
      break;
  }
}

int visit_StructSpecifier(Node *structSpecifier, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("StructSpecifier (%d)\n", structSpecifier->first_line);
#endif
  switch (structSpecifier->rhs_form) {
    case 0:  // StructSpecifier := STRUCT ID LC DefList RC
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("STRUCT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", structSpecifier->children[1]->id_token);
      print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      visit_DefList(structSpecifier->children[3], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      break;
    case 1:  // StructSpecifier := STRUCT ID
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("STRUCT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", structSpecifier->children[1]->id_token);
#endif

    default:
      fprintf(stderr, "Fail to visit <StructSpecifier> Node: line %d\n",
              structSpecifier->first_line);
      break;
  }
}

int visit_VarDec(Node *varDec, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("VarDec (%d)\n", varDec->first_line);
#endif
  switch (varDec->rhs_form) {
    case 0:  // VarDec := ID
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", varDec->children[0]->id_token);
#endif
      break;
    case 1:  // VarDec := VarDec LB INT RB
      visit_VarDec(varDec->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("LB\n");
      print_indentation(indent_level + 1);
      printf("INT: %ld\n", varDec->children[2]->int_token);
      print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <VarDec> Node: line %d\n",
              varDec->first_line);
      break;
  }
}

int visit_FunDec(Node *funDec, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("FunDec (%d)\n", funDec->first_line);
#endif
  switch (funDec->rhs_form) {
    case 0:  // FunDec := ID LP VarList RP
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", funDec->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_VarList(funDec->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 1:  // FunDec := ID LP RP
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", funDec->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <FunDec> Node: line %d\n",
              funDec->first_line);
      break;
  }
}

int visit_VarList(Node *varList, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("VarList (%d)\n", varList->first_line);
#endif
  switch (varList->rhs_form) {
    case 0:  // VarList := ParamDec COMMA VarList
      visit_ParamDec(varList->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_VarList(varList->children[2], indent_level + 1);
      break;
    case 1:  // VarList := ParamDec
      visit_ParamDec(varList->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <VarList> Node: line %d\n",
              varList->first_line);
      break;
  }
}

int visit_ParamDec(Node *paramDec, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("ParamDec (%d)\n", paramDec->first_line);
#endif
  switch (paramDec->rhs_form) {
    case 0:  // ParamDec := Specifier VarDec
      visit_Specifier(paramDec->children[0], indent_level + 1);
      visit_VarDec(paramDec->children[1], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
              paramDec->first_line);
      break;
  }
}

int visit_CompSt(Node *compSt, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("CompSt (%d)\n", compSt->first_line);
#endif
  switch (compSt->rhs_form) {
    case 0:  // CompSt := LC DefList StmtList RC
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      visit_DefList(compSt->children[1], indent_level + 1);
      visit_StmtList(compSt->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <CompSt> Node: line %d\n",
              compSt->first_line);
      break;
  }
}

int visit_StmtList(Node *stmtList, int indent_level) {
  if (stmtList->rhs_form == 1) {
    return 0;
  }
#ifdef DEBUG
  print_indentation(indent_level);
  printf("StmtList (%d)\n", stmtList->first_line);
#endif
  switch (stmtList->rhs_form) {
    case 0:  // StmtList := Stmt StmtList
      visit_Stmt(stmtList->children[0], indent_level + 1);
      visit_StmtList(stmtList->children[1], indent_level + 1);
      break;
    /* case 1:  // StmtList := %empty
      break; */

    default:
      fprintf(stderr, "Fail to visit <StmtList> Node: line %d\n",
              stmtList->first_line);
      break;
  }
}

int visit_Stmt(Node *stmt, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Stmt (%d)\n", stmt->first_line);
#endif
  switch (stmt->rhs_form) {
    case 0:  // Stmt := Exp SEMI
      visit_Exp(stmt->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // Stmt := CompSt
      visit_CompSt(stmt->children[0], indent_level + 1);
      break;
    case 2:  // Stmt := RETURN Exp SEMI
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RETURN\n");
#endif
      visit_Exp(stmt->children[1], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 3:  // Stmt := IF LP Exp RP Stmt
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("IF\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
      break;
    case 4:  // Stmt := IF LP Exp RP Stmt ELSE Stmt
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("IF\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ELSE\n");
#endif
      visit_Stmt(stmt->children[6], indent_level + 1);
      break;
    case 5:  // Stmt := WHILE LP Exp RP Stmt
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("WHILE\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Stmt> Node: line %d\n", stmt->first_line);
      break;
  }
}

int visit_DefList(Node *defList, int indent_level) {
  if (defList->rhs_form == 1) {
    return 0;
  }
#ifdef DEBUG
  print_indentation(indent_level);
  printf("DefList (%d)\n", defList->first_line);
#endif
  switch (defList->rhs_form) {
    case 0:  // DefList := Def DefList
      visit_Def(defList->children[0], indent_level + 1);
      visit_DefList(defList->children[1], indent_level + 1);
      break;
    /* case 1:  // DefList := %empty
      break; */

    default:
      fprintf(stderr, "Fail to visit <DefList> Node: line %d\n",
              defList->first_line);
      break;
  }
}

int visit_Def(Node *def, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Def (%d)\n", def->first_line);
#endif
  switch (def->rhs_form) {
    case 0:  // Def := Specifier DecList SEMI
      visit_Specifier(def->children[0], indent_level + 1);
      visit_DecList(def->children[1], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Def> Node: line %d\n", def->first_line);
      break;
  }
}

int visit_DecList(Node *decList, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("DecList (%d)\n", decList->first_line);
#endif
  switch (decList->rhs_form) {
    case 0:  // DecList := Dec
      visit_Dec(decList->children[0], indent_level + 1);
      break;
    case 1:  // DecList := Dec COMMA DecList
      visit_Dec(decList->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_DecList(decList->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <DecList> Node: line %d\n",
              decList->first_line);
      break;
  }
}

int visit_Dec(Node *dec, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Dec (%d)\n", dec->first_line);
#endif
  switch (dec->rhs_form) {
    case 0:  // Dec := VarDec
      visit_VarDec(dec->children[0], indent_level + 1);
      break;
    case 1:  // Dec := VarDec ASSIGN Exp
      visit_Dec(dec->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ASSIGN\n");
#endif
      visit_Exp(dec->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Dec> Node: line %d\n", dec->first_line);
      break;
  }
}

int visit_Exp(Node *exp, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Exp (%d)\n", exp->first_line);
#endif
  switch (exp->rhs_form) {
    case 0:  // Exp := Exp ASSIGN || AND || OR || LT || LE || GT || GE || NE ||
      // EQ || PLUS || MINUS || DIV Exp
      visit_Exp(exp->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("%s\n", exp->children[1]->keyword_token);
#endif
      visit_Exp(exp->children[2], indent_level + 1);
      break;
    case 1:  // Exp := LP Exp RP
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(exp->children[1], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 2:  // Exp := MINUS || NOT Exp
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("%s\n", exp->children[0]->keyword_token);
#endif
      visit_Exp(exp->children[1], indent_level + 1);
      break;
    case 3:  // Exp := ID LP Args RP
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Args(exp->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 4:  // Exp := ID LP RP
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 5:  // Exp := Exp LB Exp RB
      visit_Exp(exp->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("LB\n");
#endif
      visit_Exp(exp->children[2], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;
    case 6:  // Exp := Exp DOT ID
      visit_Exp(exp->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("DOT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[2]->id_token);
#endif
      break;
    case 7:  // Exp := ID
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
#endif
      break;
    case 8:  // Exp := INT
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("INT: %ld\n", exp->children[0]->int_token);
#endif
      break;
    case 9:  // Exp := FLOAT
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("FLOAT: %f\n", exp->children[0]->float_token);
#endif
      break;
    case 10:  // Exp := CHAR
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("CHAR: %s\n", exp->children[0]->char_token);
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Exp> Node: line %d\n", exp->first_line);
      break;
  }
}

int visit_Args(Node *args, int indent_level) {
#ifdef DEBUG
  print_indentation(indent_level);
  printf("Args (%d)\n", args->first_line);
#endif
  switch (args->rhs_form) {
    case 0:  // Args := Exp COMMA Args
      visit_Exp(args->children[0], indent_level + 1);
#ifdef DEBUG
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_Args(args->children[2], indent_level + 1);
      break;
    case 1:  // Args := Exp
      visit_Exp(args->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Args> Node: line %d\n", args->first_line);
      break;
  }
}

void print_indentation(int indent_level) {
  for (int i = 0; i < indent_level; i++) {
    printf("  ");  // indent with 2 spaces
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
      visit_Program(program_root);
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
