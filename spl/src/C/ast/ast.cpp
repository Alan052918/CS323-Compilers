#include "../../../include/ast/ast.h"

ASTNode::ASTNode(NodeType nt, int fl, int ll, int fc, int lc) {
  this->node_type = nt;
  this->first_line = fl;
  this->last_line = ll;
  this->first_column = fc;
  this->last_column = lc;
}

void ASTNode::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Generic ASTNode (%d)\n", this->first_line);
#endif
}

void ASTNode::print_indentation(int indent_level) {
  for (int i = 0; i < indent_level; i++) {
    printf("  ");  // indent with 2 spaces
  }
}

TerminalNode::TerminalNode(NodeType nt, int fl, int ll, int fc, int lc)
    : ASTNode(nt, fl, ll, fc, lc) {}

NonterminalNode::NonterminalNode(int rhsf, int fl, int ll, int fc, int lc)
    : rhs_form(rhsf), ASTNode(Nonterminal, fl, ll, fc, lc) {
  // #ifdef DEBUG
  //     printf("  bison: reduce NonterminalNode[%d]\n", rhsf);
  // #endif
}
