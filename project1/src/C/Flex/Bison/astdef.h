#include <stdarg.h>

/* syntax tree node types */
enum node_type {
  INT_T, FLOAT_T, CHAR_T, TYPE_T, ID_T, KEYWORD_T, NONTERMINAL_T
};

/* nonterminals */
enum nonterminal_type {
  Program, ExtDefList, ExtDef, ExtDecList, Specifier, StructSpecifier, VarDec,
  FunDec, VarList, ParamDec, CompSt, StmtList, Stmt, DefList, Def, DecList,
  Dec, Exp, Args, Nil
};

/* syntax tree node definition */
struct node {
  int node_type;
  int lineno;
  int coluno;
  union {
    int int_token;
    float float_token;
    char char_token;
    char *type_token;
    char *id_token;
    char *keyword_token;
    int nonterminal_token;
  };
  struct rhs_node *rhs;
};

/* production rule right-hand-side definition */
struct rhs_node {
  struct node *token_node;
  struct rhs_node *next;
};

/* syntax tree node constructors */
struct node *lfs(int nonterminal_type);

/* syntax tree actions */
void push_int(struct node *lfs_node, int int_val);
void push_float(struct node *lfs_node, float float_val);
void push_char(struct node *lfs_node, char char_val);
void push_type(struct node *lfs_node, char *type_val);
void push_id(struct node *lfs_node, char *id_val);
void push_keyword(struct node *lfs_node, char *keyword_val);
void push_nonterminal(struct node *lfs_node, struct node *nonterminal);

char *get_nonterminal_name(int nonterminal_val);
void print_tree(struct node *pnode, int indent_depth);
