#ifndef AST_H
#define AST_H

#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

/* syntax tree node types */
enum NodeType { Int, Float, Char, Type, Id, Keyword, Nonterminal };

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

  virtual void visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Generic ASTNode (%d)\n", this->first_line);
#endif
  }

  void print_indentation(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
      printf("  ");  // indent with 2 spaces
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
    const char *keyword_token;
  };

  TerminalNode(NodeType nt, int fl, int ll, int fc, int lc)
      : ASTNode(nt, fl, ll, fc, lc) {}
};

class NonterminalNode : public ASTNode {
 public:
  int rhs_form;

  NonterminalNode(int rhsf, int fl, int ll, int fc, int lc)
      : rhs_form(rhsf), ASTNode(Nonterminal, fl, ll, fc, lc) {}
};

#endif  // AST_H
