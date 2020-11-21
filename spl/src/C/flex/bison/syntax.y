%{
  #include <cstdio>
  #include <iostream>
  #include <cstring>
  #include "include/astdef.h"
  #include "include/typedef.h"

  using namespace std;

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

#include "src/C/build_tree.c"
#include "src/C/visitor.c"

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
      visit_Program(program_root);
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
