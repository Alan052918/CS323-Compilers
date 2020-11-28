#include "../../include/ast/dec.h"
#include "../../include/ast/exp.h"
#include "../../include/ast/var_dec.h"

Dec::Dec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce Dec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_array = false;
  this->is_assign = false;
}

void Dec::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Dec (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Dec := VarDec
               // no assignment, this Dec has no type
      this->var_dec->visit(indent_level + 1, st);
      this->id = this->var_dec->id;
      this->is_array = this->var_dec->is_array;
      break;
    }
    case 1: {  // Dec := VarDec ASSIGN Exp
      this->var_dec->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ASSIGN\n";
#endif
      this->exp->visit(indent_level + 1, st);

      this->id = this->var_dec->id;
      this->is_array = this->var_dec->is_array;
      this->is_assign = true;
      if (this->is_array == false) {
        // 1. VarDec is non-array: Dec's type = Exp's type
        this->var_type = this->exp->var_type;
      } else {
        // 2. VarDec is array: error if Exp's type is not array
        VarType *vt = this->exp->var_type;
        if (vt->category != ARRAY) {
          std::cout
              << "Error Type 5 at Line " << this->first_line
              << ": unmatching types on both sides of assignment operator\n";
          break;
        }
        this->var_type = vt;
      }
      break;
    }

    default: {
      std::cout << "Fail to visit <Dec> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
