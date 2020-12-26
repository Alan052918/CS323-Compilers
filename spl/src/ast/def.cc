#include "../../include/ast/def.hh"
#include "../../include/ast/dec_list.hh"
#include "../../include/ast/specifier.hh"

Def::Def(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Def[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Def::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Def (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0:  // Def := Specifier DecList SEMI
             // local variable DECLARATOIN, PUSH MAP
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->dec_list->var_type = this->var_type;
      this->dec_list->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      break;

    default:
      std::cout << "Fail to visit <Def> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
  }
}
