%{
  #include "astdef.h"
  #include "lex.yy.c"

  struct node *program_root;

  void yyerror(const char *);
%}

%union {
  long int_value;
  float float_value;
  char char_value;
  char *type_value;
  char *id_value;
  char *keyword_value;
  struct node *nonterminal_node;
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

%right <keyword_value> ASSIGN
%left <keyword_value> OR
%left <keyword_value> AND
%left <keyword_value> LT LE GT GE NE EQ
%left <keyword_value> PLUS MINUS
%left <keyword_value> MUL DIV
%right <keyword_value> NOT
%left <keyword_value> LB RB LP RP DOT
%nonassoc <keyword_value> ELSE

%%

/**
 * High-level definition: top-level syntax for a SPL program
 * - global variable declarations
 * - function definitions
 */
Program: ExtDefList { $$ = lfs(Program); push_nonterminal($$, $1); program_root = $$; }
 ;
ExtDefList: ExtDef ExtDefList { $$ = lfs(ExtDefList); push_nonterminal($$, $1); push_nonterminal($$, $2); }
 | %empty { $$ = lfs(Nil); }
 ;
ExtDef: Specifier ExtDecList SEMI { $$ = lfs(ExtDef); push_nonterminal($$, $1); push_nonterminal($$, $2); push_keyword($$, $3); }
 | Specifier SEMI { $$ = lfs(ExtDef); push_nonterminal($$, $1); push_keyword($$, $2); }
 | Specifier FunDec CompSt { $$ = lfs(ExtDef); push_nonterminal($$, $1); push_nonterminal($$, $2); push_nonterminal($$, $3); }
 ;
ExtDecList: VarDec { $$ = lfs(ExtDecList); push_nonterminal($$, $1); }
 | VarDec COMMA ExtDecList { $$ = lfs(ExtDecList); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 ;

/**
 * Specifier: SPL type system
 * - primitive types: int, float, char
 * - structure type
 */
Specifier: TYPE { $$ = lfs(Specifier); push_type($$, $1); }
 | StructSpecifier { $$ = lfs(Specifier); push_nonterminal($$, $1); }
 ;
StructSpecifier: STRUCT ID LC DefList RC { $$ = lfs(StructSpecifier); push_keyword($$, $1); push_keyword($$, $2); push_keyword($$, $3); push_nonterminal($$, $4); push_keyword($$, $5); }
 | STRUCT ID { $$ = lfs(StructSpecifier); push_keyword($$, $1); push_id($$, $2); }
 ;

/**
 * Declarator: variable and function declaration
 * The array type is specified by the declarator
 */
VarDec: ID { $$ = lfs(VarDec); push_id($$, $1); }
 | VarDec LB INT RB { $$ = lfs(VarDec); push_nonterminal($$, $1); push_keyword($$, $2); push_int($$, $3); push_keyword($$, $4); }
 ;
FunDec: ID LP VarList RP { $$ = lfs(FunDec); push_id($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); }
 | ID LP RP { $$ = lfs(FunDec); push_id($$, $1); push_keyword($$, $2); push_keyword($$, $3); }
 ;
VarList: ParamDec COMMA VarList { $$ = lfs(VarList); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | ParamDec { $$ = lfs(VarList); push_nonterminal($$, $1); }
 ;
ParamDec: Specifier VarDec { $$ = lfs(ParamDec); push_nonterminal($$, $1); push_nonterminal($$, $2); }
 ;

/**
 * Statement: program structures like branchs and loops
 * - enclosed bny curly braces
 * - end with a semicolon
 */
CompSt: LC DefList StmtList RC { $$ = lfs(CompSt); push_keyword($$, $1); push_nonterminal($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); }
 ;
StmtList: Stmt StmtList { $$ = lfs(StmtList); push_nonterminal($$, $1); push_nonterminal($$, $2); }
 | %empty { $$ = lfs(Nil); }
 ;
Stmt: Exp SEMI { $$ = lfs(Stmt); push_nonterminal($$, $1); push_keyword($$, $2); }
 | CompSt { $$ = lfs(Stmt); push_nonterminal($$, $1); }
 | RETURN Exp SEMI { $$ = lfs(Stmt); push_keyword($$, $1); push_nonterminal($$, $2); push_keyword($$, $3); }
 | IF LP Exp RP Stmt { $$ = lfs(Stmt); push_keyword($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); push_nonterminal($$, $5); }
 | IF LP Exp RP Stmt ELSE Stmt { $$ = lfs(Stmt); push_keyword($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); push_nonterminal($$, $5); push_keyword($$, $6); push_nonterminal($$, $7); }
 | WHILE LP Exp RP Stmt { $$ = lfs(Stmt); push_keyword($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); push_nonterminal($$, $5); }
 ;

/* Local definition: declaration and assignment of local variables */
DefList: Def DefList { $$ = lfs(DefList); push_nonterminal($$, $1); push_nonterminal($$, $2); }
 | %empty  { $$ = lfs(Nil); }
 ;
Def: Specifier DecList SEMI { $$ = lfs(Def); push_nonterminal($$, $1); push_nonterminal($$, $2); push_keyword($$, $3); }
 ;
DecList: Dec { $$ = lfs(DecList); push_nonterminal($$, $1); }
 | Dec COMMA DecList { $$ = lfs(DecList); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 ;
Dec: VarDec { $$ = lfs(Dec); push_nonterminal($$, $1); }
 | VarDec ASSIGN Exp { $$ = lfs(Dec); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 ;

/**
 * Expression
 * - single constant
 * - operations on variables: operators have precedence and associativity
 */
Exp: Exp ASSIGN Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp AND Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp OR Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp LT Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp LE Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp GT Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp GE Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp NE Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp EQ Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp PLUS Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp MINUS Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp MUL Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp DIV Exp { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | LP Exp RP { $$ = lfs(Exp); push_keyword($$, $1); push_nonterminal($$, $2); push_keyword($$, $3); }
 | MINUS Exp { $$ = lfs(Exp); push_keyword($$, $1); push_nonterminal($$, $2); }
 | NOT Exp { $$ = lfs(Exp); push_keyword($$, $1); push_nonterminal($$, $2); }
 | ID LP Args RP { $$ = lfs(Exp); push_keyword($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); }
 | ID LP RP { $$ = lfs(Exp); push_keyword($$, $1); push_keyword($$, $2); push_keyword($$, $3); }
 | Exp LB Exp RB { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); push_keyword($$, $4); }
 | Exp DOT ID { $$ = lfs(Exp); push_nonterminal($$, $1); push_keyword($$, $2); push_id($$, $3);}
 | ID { $$ = lfs(Exp); push_id($$, $1);}
 | INT { $$ = lfs(Exp); push_int($$, $1);}
 | FLOAT { $$ = lfs(Exp); push_float($$, $1);}
 | CHAR { $$ = lfs(Exp); push_char($$, $1); }
 ;
Args: Exp COMMA Args { $$ = lfs(Args); push_nonterminal($$, $1); push_keyword($$, $2); push_nonterminal($$, $3); }
 | Exp { $$ = lfs(Args); push_nonterminal($$, $1); }
 ;

%%

struct node *lfs(int nonterminal_type) {
  // printf("  lfs: %s\n", get_nonterminal_name(nonterminal_type));
  struct node *new_nonterminal_node = (struct node *)malloc(sizeof(struct node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->lineno = yylineno;
  new_nonterminal_node->coluno = yycoluno;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->rhs = NULL;
  return new_nonterminal_node;
}

void push_int(struct node *lfs_node, int int_val) {
  // printf("    push int: %d ", int_val);
  struct node *new_int_node = (struct node *)malloc(sizeof(struct node));
  new_int_node->node_type = INT_T;
  new_int_node->lineno = yylineno;
  new_int_node->coluno = yycoluno;
  new_int_node->int_token = int_val;
  new_int_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_int_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_float(struct node *lfs_node, float float_val) {
  // printf("    push float: %f ", float_val);
  struct node *new_float_node = (struct node *)malloc(sizeof(struct node));
  new_float_node->node_type = FLOAT_T;
  new_float_node->lineno = yylineno;
  new_float_node->coluno = yycoluno;
  new_float_node->float_token = float_val;
  new_float_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_float_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_char(struct node *lfs_node, char char_val) {
  // printf("    push char: %c ", char_val);
  struct node *new_char_node = (struct node *)malloc(sizeof(struct node));
  new_char_node->node_type = CHAR_T;
  new_char_node->lineno = yylineno;
  new_char_node->coluno = yycoluno;
  new_char_node->char_token = char_val;
  new_char_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_char_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_type(struct node *lfs_node, char *type_val) {
  // printf("    push type: %s ", type_val);
  struct node *new_type_node = (struct node *)malloc(sizeof(struct node));
  new_type_node->node_type = TYPE_T;
  new_type_node->lineno = yylineno;
  new_type_node->coluno = yycoluno;
  new_type_node->type_token = type_val;
  new_type_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_type_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_id(struct node *lfs_node, char *id_val) {
  // printf("    push id: %s ", id_val);
  struct node *new_id_node = (struct node *)malloc(sizeof(struct node));
  new_id_node->node_type = ID_T;
  new_id_node->lineno = yylineno;
  new_id_node->coluno = yycoluno;
  new_id_node->id_token = id_val;
  new_id_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_id_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_keyword(struct node *lfs_node, char *keyword_val) {
  printf("    push keyword: %s, line %d\n", keyword_val, yylineno);
  struct node *new_keyword_node = (struct node *)malloc(sizeof(struct node));
  new_keyword_node->node_type = KEYWORD_T;
  new_keyword_node->lineno = yylineno;
  new_keyword_node->coluno = yycoluno;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_keyword_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_nonterminal(struct node *lfs_node, struct node *nonterminal) {
  // printf("    push nonterminal: %s ", get_nonterminal_name(nonterminal->nonterminal_token));
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = nonterminal;
  new_rhs_node->next = NULL;
  if (nonterminal->lineno < lfs_node->lineno) {
    lfs_node->lineno = nonterminal->lineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
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

void print_tree(struct node *pnode, int indent_depth) {
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
    case NONTERMINAL_T: printf("%s (%d)\n", get_nonterminal_name(pnode->nonterminal_token), pnode->lineno); break;
    default: printf("Undefined node type!\n"); break;
  }
  struct rhs_node *ptr = pnode->rhs;
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
      print_tree(program_root, 0);
    } else if (result == 1) {
      printf("Abort\n");
    } else {
      printf("Exhausted\n");
    }
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
