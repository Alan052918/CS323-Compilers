#include "../../include/ast/param_dec.h"
#include "../../include/ast/specifier.h"
#include "../../include/ast/var_dec.h"

ParamDec::ParamDec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce ParamDec[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void ParamDec::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("ParamDec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // ParamDec := Specifier VarDec
      this->specifier->visit(indent_level + 1, st);
      this->var_dec->visit(indent_level + 1, st);
      break;

    default:
      fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
              this->first_line);
      break;
  }
}
