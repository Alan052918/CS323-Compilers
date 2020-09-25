#include <stdarg.h>

/* syntax tree node types */
enum node_type { INT, FLOAT, CHAR, TYPE, ID, KEYWORD, NONTERMINAL };

/* operators and reserved words */
enum keyword_type {
  DOT, SEMI, COMMA, ASSIGN, LT, GT, PLUS, MINUS, MUL, DIV, NOT, LP, RP, LB, RB,
  LC, RC, LE, GE, NE, EQ, AND, OR, STRUCT, IF, ELSE, WHILE, RETURN
};

/* nonterminals */
enum nonterminal_type {
  Program, ExtDefList, ExtDef, ExtDecList, Specifier, StructSpecifier, VarDec,
  FunDec, VarList, ParamDec, CompSt, StmtList, Stmt, DefList, Def, DecList,
  Dec, Exp, Args
};

/* syntax tree node definition */
struct node {
  int node_type;
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
  struct list_node *next;
};

/* syntax tree node constructors */
struct node *lfs(const int nonterminal_type);

/* syntax tree actions */
void push_int(struct node *lfs_node, const int int_val);
void push_float(struct node *lfs_node, const float float_val);
void push_char(struct node *lfs_node, const char char_val);
void push_type(struct node *lfs_node, const char type_val);
void push_id(struct node *lfs_node, const char *id_val);
void push_keyword(struct node *lfs_node, const char *keyword_val);
void push_nonterminal(struct node *lfs_node, const struct node *nonterminal);

char *get_keyword_name(const int keyword_val);
char *get_nonterminal_name(const int nonterminal_val);
void print_tree(const struct node *pnode, int indent_depth);
