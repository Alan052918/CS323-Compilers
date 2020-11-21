#include "../../include/astdef.h"

/* syntax tree node constructors */

Node *lhs(int nonterminal_type, int rhsf, int first_line, int last_line,
          int first_column, int last_column) {
  Node *new_nonterminal_node = (Node *)malloc(sizeof(Node));
  memset(new_nonterminal_node, '\0', sizeof(Node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->rhs_form = rhsf;
  new_nonterminal_node->first_line = first_line;
  new_nonterminal_node->last_line = last_line;
  new_nonterminal_node->first_column = first_column;
  new_nonterminal_node->last_column = last_column;
#ifdef DEBUG
  printf(" lhs: ");
  get_nonterminal_name(nonterminal_type);
  printf("[%d], line %d\n", nonterminal_type, new_nonterminal_node->first_line);
#endif
  return new_nonterminal_node;
}

/* Syntax tree actions */

void push_int(Node *lhs_node, int int_val) {
#ifdef DEBUG
  printf("    push int: %d, line %d\n", int_val, yylloc.first_line);
#endif
  Node *new_int_node = (Node *)malloc(sizeof(Node));
  memset(new_int_node, '\0', sizeof(Node));
  new_int_node->node_type = INT_T;
  new_int_node->int_token = int_val;
  new_int_node->rhs_form = -1;
  lhs_node->children.push_back(new_int_node);
}

void push_float(Node *lhs_node, float float_val) {
#ifdef DEBUG
  printf("    push float: %f, line %d\n", float_val, yylloc.first_line);
#endif
  Node *new_float_node = (Node *)malloc(sizeof(Node));
  memset(new_float_node, '\0', sizeof(Node));
  new_float_node->node_type = FLOAT_T;
  new_float_node->float_token = float_val;
  new_float_node->rhs_form = -1;
  lhs_node->children.push_back(new_float_node);
}

void push_char(Node *lhs_node, char *char_val) {
#ifdef DEBUG
  printf("    push char: %s, line %d\n", char_val, yylloc.first_line);
#endif
  Node *new_char_node = (Node *)malloc(sizeof(Node));
  memset(new_char_node, '\0', sizeof(Node));
  new_char_node->node_type = CHAR_T;
  new_char_node->char_token = char_val;
  new_char_node->rhs_form = -1;
  lhs_node->children.push_back(new_char_node);
}

void push_type(Node *lhs_node, char *type_val) {
#ifdef DEBUG
  printf("    push type: %s, line %d\n", type_val, yylloc.first_line);
#endif
  Node *new_type_node = (Node *)malloc(sizeof(Node));
  memset(new_type_node, '\0', sizeof(Node));
  new_type_node->node_type = TYPE_T;
  new_type_node->type_token = type_val;
  new_type_node->rhs_form = -1;
  lhs_node->children.push_back(new_type_node);
}

void push_id(Node *lhs_node, char *id_val) {
#ifdef DEBUG
  printf("    push id: %s, line %d\n", id_val, yylloc.first_line);
#endif
  Node *new_id_node = (Node *)malloc(sizeof(Node));
  memset(new_id_node, '\0', sizeof(Node));
  new_id_node->node_type = ID_T;
  new_id_node->id_token = id_val;
  new_id_node->rhs_form = -1;
  lhs_node->children.push_back(new_id_node);
}

void push_keyword(Node *lhs_node, const char *keyword_val) {
#ifdef DEBUG
  printf("    push keyword: %s, line %d\n", keyword_val, yylloc.first_line);
#endif
  Node *new_keyword_node = (Node *)malloc(sizeof(Node));
  memset(new_keyword_node, '\0', sizeof(Node));
  new_keyword_node->node_type = KEYWORD_T;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs_form = -1;
  lhs_node->children.push_back(new_keyword_node);
}

void push_nonterminal(Node *lhs_node, Node *nonterminal) {
#ifdef DEBUG
  printf("    push nonterminal: ");
  get_nonterminal_name(nonterminal->nonterminal_token);
  printf(", line %d\n", yylloc.first_line);
#endif
  lhs_node->children.push_back(nonterminal);
}

void get_nonterminal_name(int nonterminal_val) {
  switch (nonterminal_val) {
    case Program:
      printf("Program");
      break;
    case ExtDefList:
      printf("ExtDefList");
      break;
    case ExtDef:
      printf("ExtDef");
      break;
    case ExtDecList:
      printf("ExtDecList");
      break;
    case Specifier:
      printf("Specifier");
      break;
    case StructSpecifier:
      printf("StructSpecifier");
      break;
    case VarDec:
      printf("VarDec");
      break;
    case FunDec:
      printf("FunDec");
      break;
    case VarList:
      printf("VarList");
      break;
    case ParamDec:
      printf("ParamDec");
      break;
    case CompSt:
      printf("CompSt");
      break;
    case StmtList:
      printf("StmtList");
      break;
    case Stmt:
      printf("Stmt");
      break;
    case DefList:
      printf("DefList");
      break;
    case Def:
      printf("Def");
      break;
    case DecList:
      printf("DecList");
      break;
    case Dec:
      printf("Dec");
      break;
    case Exp:
      printf("Exp");
      break;
    case Args:
      printf("Args");
      break;
    case Nil:
      printf("Nil");
      break;
    default:
      printf("Undefined nonterminal type!");
      break;
  }
}
