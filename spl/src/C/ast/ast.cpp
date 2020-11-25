#include "../../../include/ast/ast.h"

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
