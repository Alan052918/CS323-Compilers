#ifndef AST_H
#define AST_H

#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class ASTNode {
 public:
  NodeType node_type;
  int first_line;
  int last_line;
  int first_column;
  int last_column;

  ASTNode(NodeType nt, int fl, int ll, int fc, int lc) {
    this->node_type = nt;
    this->first_line = fl;
    this->last_line = ll;
    this->first_column = fc;
    this->last_column = lc;
  }

  void print_indentation(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
      std::cout << "  ";  // indent with 2 spaces
    }
  }
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

  TerminalNode(NodeType nt, int fl, int ll, int fc, int lc)
      : ASTNode(nt, fl, ll, fc, lc) {}
};

class NonterminalNode : public ASTNode {
 public:
  int rhs_form;

  NonterminalNode(int fl, int ll, int fc, int lc, int rhsf)
      : ASTNode(Nonterminal, fl, ll, fc, lc), rhs_form(rhsf) {}
};

#endif  // AST_H
