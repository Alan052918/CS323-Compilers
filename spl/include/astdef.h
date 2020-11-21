#ifndef ASTDEF_H
#define ASTDEF_H

#include <vector>

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
  int rhs_form;
  std::vector<Node *> children;
  union {
    long int_token;
    float float_token;
    char *char_token;
    char *type_token;
    char *id_token;
    const char *keyword_token;
    int nonterminal_token;
  };
  int first_line;
  int last_line;
  int first_column;
  int last_column;
} Node;

Node *program_root;

/* syntax tree node constructors */
Node *lhs(int nonterminal_type, int rhsf, int first_line, int last_line,
          int first_column, int last_column);

/* syntax tree actions */
void push_int(Node *lhs_node, int int_val);
void push_float(Node *lhs_node, float float_val);
void push_char(Node *lhs_node, char *char_val);
void push_type(Node *lhs_node, char *type_val);
void push_id(Node *lhs_node, char *id_val);
void push_keyword(Node *lhs_node, const char *keyword_val);
void push_nonterminal(Node *lhs_node, Node *nonterminal);

void get_nonterminal_name(int nonterminal_val);

/* visitor functions */
int visit_Program(Node *program);
int visit_ExtDefList(Node *extDefList, int indent_level);
int visit_ExtDef(Node *extDef, int indent_level);
int visit_ExtDecList(Node *extDecList, int indent_level);
int visit_Specifier(Node *specifier, int indent_level);
int visit_StructSpecifier(Node *structSpecifier, int indent_level);
int visit_VarDec(Node *varDec, int indent_level);
int visit_FunDec(Node *funDec, int indent_level);
int visit_VarList(Node *varList, int indent_level);
int visit_ParamDec(Node *paramDec, int indent_level);
int visit_CompSt(Node *compSt, int indent_level);
int visit_StmtList(Node *stmtList, int indent_level);
int visit_Stmt(Node *stmt, int indent_level);
int visit_DefList(Node *defList, int indent_level);
int visit_Def(Node *def, int indent_level);
int visit_DecList(Node *decList, int indent_level);
int visit_Dec(Node *dec, int indent_level);
int visit_Exp(Node *exp, int indent_level);
int visit_Args(Node *args, int indent_level);

void print_indentation(int indent_level);

#endif  // ASTDEF_H
