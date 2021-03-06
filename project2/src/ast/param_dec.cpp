#include "../../include/ast/param_dec.h"
#include "../../include/ast/specifier.h"
#include "../../include/ast/var_dec.h"

ParamDec::ParamDec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce ParamDec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void ParamDec::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "ParamDec (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0:  // ParamDec := Specifier VarDec
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->var_dec->visit(indent_level + 1, st);
      this->id = this->var_dec->id;
      break;

    default:
      std::cout << "Fail to visit <ParamDec> Node: line " << this->first_line
                << std::endl;
      break;
  }
}
