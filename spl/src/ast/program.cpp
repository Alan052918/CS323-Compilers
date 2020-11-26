#include "../../include/ast/program.h"
#include "../../include/ast/ext_def_list.h"

Program::Program(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce Program[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void Program::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Program (%d)\n", this->first_line);
#endif
  // Program := ExtDefList
  this->ext_def_list->visit(indent_level + 1);
}
