%{
  #include "include/astdef.h"
  #include "lex.yy.c"

  Node *program_root;

  void yyerror(const char *);
%}

%union {
  long int_value;
  float float_value;
  char char_value;
  char *type_value;
  char *id_value;
  char *keyword_value;
  Node *nonterminal_node;
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
      $$ = lfs(Program, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
      program_root = $$;
    }
  ;
ExtDefList:
    ExtDef ExtDefList {
      $$ = lfs(ExtDefList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty {
      $$ = lfs(Nil, 0, 0, 0, 0);
    }
  ;
ExtDef:
    Specifier ExtDecList SEMI {
      $$ = lfs(ExtDef, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | Specifier SEMI {
      $$ = lfs(ExtDef, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | Specifier FunDec CompSt {
      $$ = lfs(ExtDef, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
    }
  ;
ExtDecList:
    VarDec {
      $$ = lfs(ExtDecList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec COMMA ExtDecList {
      $$ = lfs(ExtDecList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
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
      $$ = lfs(Specifier, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_type($$, $1);
    }
  | StructSpecifier {
      $$ = lfs(Specifier, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
StructSpecifier:
    STRUCT ID LC DefList RC {
      $$ = lfs(StructSpecifier, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_id($$, $2);
      push_keyword($$, $3);
      push_nonterminal($$, $4);
      push_keyword($$, $5);
    }
  | STRUCT ID {
      $$ = lfs(StructSpecifier, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
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
      $$ = lfs(VarDec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
   }
 | VarDec LB INT RB {
    $$ = lfs(VarDec, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
    push_nonterminal($$, $1);
    push_keyword($$, $2);
    push_int($$, $3);
    push_keyword($$, $4);
   }
  ;
FunDec:
    ID LP VarList RP {
      $$ = lfs(FunDec, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lfs(FunDec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  ;
VarList:
    ParamDec COMMA VarList {
      $$ = lfs(VarList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | ParamDec {
      $$ = lfs(VarList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;
ParamDec:
    Specifier VarDec {
      $$ = lfs(ParamDec, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt:
    LC DefList StmtList RC {
      $$ = lfs(CompSt, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  ;
StmtList:
    Stmt StmtList {
      $$ = lfs(StmtList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty { $$ = lfs(Nil, 0, 0, 0, 0); }
  ;
Stmt:
    Exp SEMI {
      $$ = lfs(Stmt, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
    }
  | Exp error {
      fprintf(stderr, "Error type B at Line %d: Missing semicolon at the end of statement\n",
        @$.first_line);
    }
  | CompSt {
      $$ = lfs(Stmt, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | RETURN Exp SEMI {
      $$ = lfs(Stmt, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | RETURN Exp error {
      fprintf(stderr, "Error type B at line %d: Missing semicolon ';' at the end of return statement\n", @$.first_line);
    }
  | IF LP Exp RP Stmt %prec LOWER_ELSE {
      $$ = lfs(Stmt, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  | IF LP Exp RP Stmt ELSE Stmt {
      $$ = lfs(Stmt, @1.first_line, @7.last_line, @1.first_column, @7.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
      push_keyword($$, $6);
      push_nonterminal($$, $7);
    }
  | WHILE LP Exp RP Stmt {
      $$ = lfs(Stmt, @1.first_line, @5.last_line, @1.first_column, @5.last_column);
      push_keyword($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
      push_nonterminal($$, $5);
    }
  ;

/* Local definition: declaration and assignment of local variables */
DefList:
    Def DefList {
      $$ = lfs(DefList, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
    }
  | %empty  { $$ = lfs(Nil, 0, 0, 0, 0); }
  ;
Def:
    Specifier DecList SEMI {
      $$ = lfs(Def, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  ;
DecList:
    Dec {
      $$ = lfs(DecList, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | Dec COMMA DecList {
      $$ = lfs(DecList, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  ;
Dec:
    VarDec {
      $$ = lfs(Dec, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  | VarDec ASSIGN Exp {
      $$ = lfs(Dec, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | VarDec ASSIGN error {
      fprintf(stderr, "Error type B at line %d: missing expression at the end of declaration\n", yylloc.first_line);
    }
  ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp:
    Exp ASSIGN Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp AND Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp OR Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LT Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp LE Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GT Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp GE Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp NE Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp EQ Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp PLUS Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MINUS Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp MUL Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp DIV Exp {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | LP Exp RP {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
      push_keyword($$, $3);
    }
  | MINUS Exp {
      $$ = lfs(Exp, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | NOT Exp {
      $$ = lfs(Exp, @1.first_line, @2.last_line, @1.first_column, @2.last_column);
      push_keyword($$, $1);
      push_nonterminal($$, $2);
    }
  | ID LP Args RP {
      $$ = lfs(Exp, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | ID LP RP {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_id($$, $1);
      push_keyword($$, $2);
      push_keyword($$, $3);
    }
  | Exp LB Exp RB {
      $$ = lfs(Exp, @1.first_line, @4.last_line, @1.first_column, @4.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
      push_keyword($$, $4);
    }
  | Exp DOT ID {
      $$ = lfs(Exp, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_id($$, $3);
    }
  | ID {
      $$ = lfs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_id($$, $1);
    }
  | INT {
      $$ = lfs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_int($$, $1);
    }
  | FLOAT {
      $$ = lfs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_float($$, $1);
    }
  | CHAR {
      $$ = lfs(Exp, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_char($$, $1);
    }
  ;
Args:
    Exp COMMA Args {
      $$ = lfs(Args, @1.first_line, @3.last_line, @1.first_column, @3.last_column);
      push_nonterminal($$, $1);
      push_keyword($$, $2);
      push_nonterminal($$, $3);
    }
  | Exp {
      $$ = lfs(Args, @1.first_line, @1.last_line, @1.first_column, @1.last_column);
      push_nonterminal($$, $1);
    }
  ;

%%

Node *lfs(int nonterminal_type, int first_line, int last_line, int first_column, int last_column) {
  Node *new_nonterminal_node = (Node *)malloc(sizeof(Node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->first_line = first_line;
  new_nonterminal_node->last_line = last_line;
  new_nonterminal_node->first_column = first_column;
  new_nonterminal_node->last_column = last_column;
  new_nonterminal_node->rhs = NULL;
#ifdef DEBUG
  printf("  lfs: %s, line %d\n", get_nonterminal_name(nonterminal_type), new_nonterminal_node->first_line);
#endif
  return new_nonterminal_node;
}

void push_int(Node *lfs_node, int int_val) {
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
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_float(Node *lfs_node, float float_val) {
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
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_char(Node *lfs_node, char char_val) {
#ifdef DEBUG
  printf("    push char: %c, line %d\n", char_val, yylloc.first_line);
#endif
  Node *new_char_node = (Node *)malloc(sizeof(Node));
  new_char_node->node_type = CHAR_T;
  new_char_node->char_token = char_val;
  new_char_node->rhs = NULL;
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = new_char_node;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_type(Node *lfs_node, char *type_val) {
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
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_id(Node *lfs_node, char *id_val) {
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
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_keyword(Node *lfs_node, char *keyword_val) {
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
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_nonterminal(Node *lfs_node, Node *nonterminal) {
#ifdef DEBUG
  printf("    push nonterminal: %s, line %d\n", get_nonterminal_name(nonterminal->nonterminal_token), yylloc.first_line);
#endif
  Rhs_node *new_rhs_node = (Rhs_node *)malloc(sizeof(Rhs_node));
  new_rhs_node->token_node = nonterminal;
  new_rhs_node->next = NULL;
  Rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

char *get_nonterminal_name(int nonterminal_val) {
  switch (nonterminal_val) {
    case Program: return "Program";
    case ExtDefList: return "ExtDefList";
    case ExtDef: return "ExtDef";
    case ExtDecList: return "ExtDecList";
    case Specifier: return "Specifier";
    case StructSpecifier: return "StructSpecifier";
    case VarDec: return "VarDec";
    case FunDec: return "FunDec";
    case VarList: return "VarList";
    case ParamDec: return "ParamDec";
    case CompSt: return "CompSt";
    case StmtList: return "StmtList";
    case Stmt: return "Stmt";
    case DefList: return "DefList";
    case Def: return "Def";
    case DecList: return "DecList";
    case Dec: return "Dec";
    case Exp: return "Exp";
    case Args: return "Args";
    case Nil: return "Nil";
    default: return "Undefined nonterminal type!";
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
    case CHAR_T: printf("CHAR: %c\n", pnode->char_token); break;
    case TYPE_T: printf("TYPE: %s\n", pnode->type_token); break;
    case ID_T: printf("ID: %s\n", pnode->id_token); break;
    case KEYWORD_T: printf("%s\n", pnode->keyword_token); break;
    case NONTERMINAL_T: printf("%s (%d)\n", get_nonterminal_name(pnode->nonterminal_token), pnode->first_line); break;
    default: printf("Undefined node type!\n"); break;
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
    int result = yyparse();
    if (result == 0) {
#ifdef DEBUG
      printf("\n*********************\n");
#endif
      print_tree(program_root, 0);
    } else if (result == 1) {
#ifdef DEBUG
      fprintf(stderr, "Abort\n");
#endif
    } else {
#ifdef DEBUG
      fprintf(stderr, "Exhausted\n");
#endif
    }
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
