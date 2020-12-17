#include "../../include/ast/def.hpp"
#include "../../include/ast/dec_list.hpp"
#include "../../include/ast/specifier.hpp"

Def::Def(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce Def[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
#endif
}

void Def::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Def (%d)\n", this->first_line);
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
      printf("SEMI\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Def> Node: line %d\n", this->first_line);
      break;
  }
}
