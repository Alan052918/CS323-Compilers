%{
  #include "lex.yy.c"
  #include "astdef.h"

  void yyerror(const char *);
%}

%union {
  int int_value;
  float float_value;
  char char_value;
  char *type_value;
  char *id_value;
  struct ast_node *nonterminal_node;
}

%type <nonterminal_node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%token <int_value> INT
%token <float_value> FLOAT
%token <char_value> CHAR
%token <type_value> TYPE
%token <id_value> ID
%token LC RC STRUCT
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
Program: ExtDefList { $$ = lfs(Program); push_nonterminal($$, $1); }
 ;
ExtDefList: ExtDef ExtDefList { $$ = lfs(ExtDefList); push_nonterminal($$, $1); push_nonterminal($$, $2); }
 | %empty { $$ = lfs(ExtDefList); }
 ;
ExtDef: Specifier ExtDecList SEMI { $$ = lfs(ExtDef); push_nonterminal($$, $1); push_nonterminal($$, $2); push_keyword($3); }
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
 | %empty { $$ = lfs(StmtList); }
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
 | %empty  { $$ = lfs(DefList); }
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

struct node *lfs(const int nonterminal_type) {
  struct node *new_nonterminal_node = (struct node *)malloc(sizeof(struct node));
  new_nonterminal_node->node_type = NONTERMINAL;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->rhs = NULL;
  return new_nonterminal_node;
}

void push_int(struct node *lfs_node, const int int_val) {
  struct node *new_int_node = (struct node *)malloc(sizeof(struct node));
  new_int_node->node_type = INT;
  new_int_node->int_token = int_val;
  new_int_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_int_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_float(struct node *lfs_node, const int float_val) {
  struct node *new_float_node = (struct node *)malloc(sizeof(struct node));
  new_float_node->node_type = FLOAT;
  new_float_node->float_token = float_val;
  new_float_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_float_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_char(struct node *lfs_node, const char char_val) {
  struct node *new_char_node = (struct node *)malloc(sizeof(struct node));
  new_char_node->node_type = CHAR;
  new_char_node->char_token = char_val;
  new_char_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_char_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_type(struct node *lfs_node, const char *type_val) {
  struct node *new_type_node = (struct node *)malloc(sizeof(struct node));
  new_type_node->node_type = TYPE;
  new_type_node->type_token = type_val;
  new_type_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_type_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_id(struct node *lfs_node, const char *id_val) {
  struct node *new_id_node = (struct node *)malloc(sizeof(struct node));
  new_id_node->node_type = ID;
  new_id_node->id_token = id_val;
  new_id_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_id_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_keyword(struct node *lfs_node, const char *keyword_val) {
  struct node *new_keyword_node = (struct node *)malloc(sizeof(struct node));
  new_keyword_node->node_type = KEYWORD;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs = NULL;
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = new_keyword_node;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_nonterminal(struct node *lfs_node, const struct node *nonterminal) {
  struct list_node *new_rhs_node = (struct node *)malloc(sizeof(struct list_node));
  new_rhs_node->token_node = nonterminal;
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    ptr = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

char *get_keyword_name(const int keyword_val) {
  switch (keyword_val) {
    case DOT: return "DOT";
    case SEMI: return "SEMI";
    case COMMA: return "COMMA";
    case ASSIGN: return "ASSIGN";
    case LT: return "LT";
    case GT: return "GT";
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case MUL: return "MUL";
    case DIV: return "DIV";
    case NOT: return "NOT";
    case LP: return "LP";
    case RP: return "RP";
    case LB: return "LB";
    case RB: return "RB";
    case LC: return "LC";
    case RC: return "RC";
    case LE: return "LE";
    case GE: return "GE";
    case NE: return "NE";
    case EQ: return "EQ";
    case AND: return "AND";
    case OR: return "OR";
    case STRUCT: return "STRUCT";
    case IF: return "IF";
    case ELSE: return "ELSE";
    case WHILE: return "WHILE";
    case RETURN: return "RETURN";
    default: return "Undefined keyword type!";
  }
}

char *get_nonterminal_name(const int nonterminal_val) {
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
    default: return "Undefined nonterminal type!";
  }
}

void print_tree(const struct ast_node *node, int indent_depth) {
  for (int i = 0; i < indent_depth; i++) {
    printf(" ");
  }
  switch (node->node_type) {
    case INT: printf("INT: %d\n", node->int_token); break;
    case FLOAT: printf("FLOAT: %f\n", node->float_token); break;
    case CHAR: printf("CHAR: %c\n", node->char_token); break;
    case TYPE: printf("TYPE: %s\n", node->type_token); break;
    case ID: printf("ID: %s\n", node->id_token); break;
    case KEYWORD: printf("%s\n", node->keyword_token); break;
    case NONTERMINAL: printf("%s (%d)\n", node->nonterminal_token, yylineno); break;
    default: printf("Undefined node type!\n"); break;
  }
  struct list_node *ptr = node->rhs;
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
    yyparse();
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
