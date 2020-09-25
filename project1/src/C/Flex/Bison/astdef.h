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
  union {
    int int_token;
    float float_token;
    char char_token;
    struct ast_node *nonterminal_token;
  };
  struct list_node *next;
};

struct ast_node *make_ast_node(const int node_type);
void push_nonterminal(struct ast_node *LHS, struct ast_node *node);
void push_int(struct ast_node *LHS, const int int_terminal);
void push_float(struct ast_node *LHS, const int float_terminal);
void push_char(struct ast_node *LHS, const int char_terminal);
char *get_node_type_name(const int node_type_enum);
void print_tree(const struct ast_node *node, int indent_depth);

