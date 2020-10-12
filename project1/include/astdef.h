#include <stdarg.h>
/* syntax tree node types */
enum node_type {
  INT_T,
  FLOAT_T,
  CHAR_T,
  TYPE_T,
  ID_T,
  KEYWORD_T,
  NONTERMINAL_T
};

/* nonterminals */
enum nonterminal_type {
  Program,
  ExtDefList,
  ExtDef,
  ExtDecList,
  Specifier,
  StructSpecifier,
  VarDec,
  FunDec,
  VarList,
  ParamDec,
  CompSt,
  StmtList,
  Stmt,
  DefList,
  Def,
  DecList,
  Dec,
  Exp,
  Args,
  Nil
};

/* syntax tree node definition */
typedef struct Node {
  int node_type;
  int first_line;
  int last_line;
  int first_column;
  int last_column;
  union {
    long int_token;
    float float_token;
    char *char_token;
    char *type_token;
    char *id_token;
    char *keyword_token;
    int nonterminal_token;
  };
  struct Rhs_node *rhs;
} Node;

/* production rule right-hand-side definition */
typedef struct Rhs_node {
  struct Node *token_node;
  struct Rhs_node *next;
} Rhs_node;

/* syntax tree node constructors */
Node *lhs(int nonterminal_type, int first_line, int last_line, int first_column,
          int last_column);

/* syntax tree actions */
void push_int(Node *lhs_node, int int_val);
void push_float(Node *lhs_node, float float_val);
void push_char(Node *lhs_node, char *char_val);
void push_type(Node *lhs_node, char *type_val);
void push_id(Node *lhs_node, char *id_val);
void push_keyword(Node *lhs_node, char *keyword_val);
void push_nonterminal(Node *lhs_node, Node *nonterminal);

char *get_nonterminal_name(int nonterminal_val);
void print_tree(Node *pnode, int indent_depth);
