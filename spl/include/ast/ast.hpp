#ifndef AST_H
#define AST_H

#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class ASTNode {
 public:
  NodeType node_type;
  int first_line;
  int last_line;
  int first_column;
  int last_column;
  SymbolTable *symbol_table;

  ASTNode(NodeType nt, int fl, int ll, int fc, int lc);

  virtual void visit(int indent_level, SymbolTable *st);
  void print_indentation(int indent_level);
};

class TerminalNode : public ASTNode {
 public:
  union {
    long int_token;
    float float_token;
    char *char_token;
    char *type_token;
    char *id_token;
    char *keyword_token;
  };

  TerminalNode(NodeType nt, int fl, int ll, int fc, int lc);
};

class NonterminalNode : public ASTNode {
 public:
  int rhs_form;

  NonterminalNode(int fl, int ll, int fc, int lc, int rhsf);
};

#endif  // AST_H
