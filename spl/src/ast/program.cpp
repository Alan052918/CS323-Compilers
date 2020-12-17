#include "../../include/ast/program.hpp"
#include "../../include/ast/ext_def_list.hpp"

Program::Program(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Program[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Program::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Program (" << this->first_line << ")\n";
#endif
  // Program := ExtDefList
  this->ext_def_list->visit(indent_level + 1, st);
}
