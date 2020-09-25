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
Program: ExtDefList { $$ = make_ast_node(Program); push_right($$, $1); }
 ;
ExtDefList: ExtDef ExtDefList { $$ = make_ast_node(ExtDefList); push_right($$, $1); push_right($$, $2); }
 | %empty { $$ = make_ast_node(ExtDefList); }
 ;
ExtDef: Specifier ExtDecList SEMI { $$ = make_ast_node(ExtDef); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Specifier SEMI { $$ = make_ast_node(ExtDef); push_right($$, $1); push_right($$, $2); }
 | Specifier FunDec CompSt { $$ = make_ast_node(ExtDef); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;
ExtDecList: VarDec { $$ = make_ast_node(ExtDecList); push_right($$, $1); }
 | VarDec COMMA ExtDecList { $$ = make_ast_node(ExtDecList); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier: TYPE { $$ = make_ast_node(Specifier); push_right($$, $1); }
 | StructSpecifier { $$ = make_ast_node(Specifier); push_right($$, $1); }
 ;
StructSpecifier: STRUCT ID LC DefList RC { $$ = make_ast_node(StructSpecifier); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); push_right($$, $5); }
 | STRUCT ID { $$ = make_ast_node(StructSpecifier); push_right($$, $1); push_right($$, $2); }
 ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec: ID { $$ = make_ast_node(VarDec); push_right($$, $1); }
 | VarDec LB INT RB { $$ = make_ast_node(VarDec); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); }
 ;
FunDec: ID LP VarList RP { $$ = make_ast_node(FunDec); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); }
 | ID LP RP { $$ = make_ast_node(FunDec); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;
VarList: ParamDec COMMA VarList { $$ = make_ast_node(VarList); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | ParamDec { $$ = make_ast_node(VarList); push_right($$, $1); }
 ;
ParamDec: Specifier VarDec { $$ = make_ast_node(ParamDec); push_right($$, $1); push_right($$, $2); }
 ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt: LC DefList StmtList RC { $$ = make_ast_node(CompSt); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); }
 ;
StmtList: Stmt StmtList { $$ = make_ast_node(StmtList); push_right($$, $1); push_right($$, $2); }
 | %empty { $$ = make_ast_node(StmtList); }
 ;
Stmt: Exp SEMI { $$ = make_ast_node(Stmt); push_right($$, $1); push_right($$, $2); }
 | CompSt { $$ = make_ast_node(Stmt); push_right($$, $1); }
 | RETURN Exp SEMI { $$ = make_ast_node(Stmt); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | IF LP Exp RP Stmt { $$ = make_ast_node(Stmt); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); push_right($$, $5); }
 | IF LP Exp RP Stmt ELSE Stmt { $$ = make_ast_node(Stmt); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); push_right($$, $5); push_right($$, $6); push_right($$, $7); }
 | WHILE LP Exp RP Stmt { $$ = make_ast_node(Stmt); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); push_right($$, $5); }
 ;

/* Local definition: declaration and assignment of local variables */
DefList: Def DefList { $$ = make_ast_node(DefList); push_right($$, $1); push_right($$, $2); }
 | %empty  { $$ = make_ast_node(DefList); }
 ;
Def: Specifier DecList SEMI { $$ = make_ast_node(Def); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;
DecList: Dec { $$ = make_ast_node(DecList); push_right($$, $1); }
 | Dec COMMA DecList { $$ = make_ast_node(DecList); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;
Dec: VarDec { $$ = make_ast_node(Dec); push_right($$, $1); }
 | VarDec ASSIGN Exp { $$ = make_ast_node(Dec); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp: Exp ASSIGN Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp AND Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp OR Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp LT Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp LE Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp GT Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp GE Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp NE Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp EQ Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp PLUS Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp MINUS Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp MUL Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp DIV Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | LP Exp RP { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | MINUS Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); }
 | NOT Exp { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); }
 | ID LP Args RP { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); }
 | ID LP RP { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp LB Exp RB { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3); push_right($$, $4); }
 | Exp DOT ID { $$ = make_ast_node(Exp); push_right($$, $1); push_right($$, $2); push_right($$, $3);}
 | ID { $$ = make_ast_node(Exp); push_right($$, $1);}
 | INT { $$ = make_ast_node(Exp); push_right($$, $1);}
 | FLOAT { $$ = make_ast_node(Exp); push_right($$, $1);}
 | CHAR { $$ = make_ast_node(Exp); push_right($$, $1); }
 ;
Args: Exp COMMA Args { $$ = make_ast_node(Args); push_right($$, $1); push_right($$, $2); push_right($$, $3); }
 | Exp { $$ = make_ast_node(Args); push_right($$, $1); }
 ;

%%

struct ast_node *make_ast_node(const int node_type) {
  struct ast_node *node = (struct ast_node *)malloc(sizeof(struct ast_node));
  node->node_type = node_type;
  node->RHS = NULL;
  return node;
}

void push_nonterminal(struct ast_node *LHS, struct ast_node *node) {
  struct list_node *ptr = LHS->RHS;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  struct list_node *ln = (struct list_node *)malloc(sizeof(struct list_node));
  ln->nonterminal_token = node;
  ln->next = NULL;
  ptr->next = ln;
}

void push_int(struct ast_node *LHS, const int int_terminal) {
  struct list_node *ptr = LHS->RHS;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  struct list_node *ln = (struct list_node *)malloc(sizeof(struct list_node));
  ln->int_token = int_terminal;
  ln->next = NULL;
  ptr->next = ln;
}

void push_float(struct ast_node *LHS, const float float_terminal) {
  struct list_node *ptr = LHS->RHS;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  struct list_node *ln = (struct list_node *)malloc(sizeof(struct list_node));
  ln->float_token = float_terminal;
  ln->next = NULL;
  ptr->next = ln;
}

void push_char(struct ast_node *LHS, const char char_terminal) {
  struct list_node *ptr = LHS->RHS;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  struct list_node *ln = (struct list_node *)malloc(sizeof(struct list_node));
  ln->char_token = char_terminal;
  ln->next = NULL;
  ptr->next = ln;
}

char *get_node_type_name(const int node_type_enum) {
  switch (node_type_enum) {
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
    case Terminal: return "Terminal";
    default: return "Undefined node type!";
  }
}

void print_tree(const struct ast_node *node, int indent_depth) {
  for (int i = 0; i < indent_depth; i++) {
    printf(" ");
  }
  printf("%s \(%d\)\n", get_node_type_name(node->node_type), yylineno);
  struct list_node *ptr = node->RHS;
  while (ptr != NULL) {
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
    yyparse();
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
