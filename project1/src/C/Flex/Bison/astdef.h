#include <stdarg.h>

enum node_types {
  Program,
  ExtDefList, ExtDef, ExtDecList,
  Specifier, StructSpecifier,
  VarDec, FunDec, VarList, ParamDec,
  CompSt, StmtList, Stmt,
  DefList, Def, DecList, Dec,
  Exp, Args,
  Terminal
};

struct ast_node {
  int node_type;
  struct list_node *RHS;
};
  
struct list_node {
  struct ast_node *ast_content;
  struct list_node *next;
};

struct ast_node *make_ast_node(const char *fmt, ...);
struct list_node *make_list_node(const int node_type);
void push_right(struct ast_node *LHS, struct ast_node *node);
void print_tree(struct ast_node *root);

int indent_level = 0;
