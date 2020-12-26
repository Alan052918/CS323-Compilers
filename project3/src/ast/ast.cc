#include "../../include/ast/ast.hh"

ASTNode::ASTNode(NodeType nt, int fl, int ll, int fc, int lc) {
  this->node_type = nt;
  this->first_line = fl;
  this->last_line = ll;
  this->first_column = fc;
  this->last_column = lc;
}

void ASTNode::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Generic ASTNode (" << this->first_line << ")\n";
#endif
}

void ASTNode::print_indentation(int indent_level) {
  for (int i = 0; i < indent_level; i++) {
    std::cout << "  ";  // indent with 2 spaces
  }
}

TerminalNode::TerminalNode(NodeType nt, int fl, int ll, int fc, int lc)
    : ASTNode(nt, fl, ll, fc, lc) {}

NonterminalNode::NonterminalNode(int fl, int ll, int fc, int lc, int rhsf)
    : ASTNode(Nonterminal, fl, ll, fc, lc), rhs_form(rhsf) {
  // #ifdef DEBUG
  //     std::cout << "  bison: reduce NonterminalNode[" << rhsf << "]\n";
  // #endif
}
