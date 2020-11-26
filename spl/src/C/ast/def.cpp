#include "../../../include/ast/def.h"
#include "../../../include/ast/dec_list.h"
#include "../../../include/ast/specifier.h"

Def::Def(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce Def[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void Def::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Def (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // Def := Specifier DecList SEMI
             // local variable DECLARATOIN, PUSH MAP
      this->specifier->visit(indent_level + 1);
      this->dec_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Def> Node: line %d\n", this->first_line);
      break;
  }
}
