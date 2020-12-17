#include "../../include/ast/program.hpp"
#include "../../include/ast/ext_def_list.hpp"

Program::Program(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce Program[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
#endif
}

void Program::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Program (%d)\n", this->first_line);
#endif
  // Program := ExtDefList
  this->ext_def_list->visit(indent_level + 1, st);
}
