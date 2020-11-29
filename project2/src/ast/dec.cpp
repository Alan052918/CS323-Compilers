#include "../../include/ast/dec.h"
#include "../../include/ast/exp.h"
#include "../../include/ast/var_dec.h"

Dec::Dec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce Dec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
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
      if (this->var_dec->is_array) {
        VarType *at = new VarType();
        at->name = std::string("array");
        at->category = ARRAY;
        at->array = new Array();
        for (int i : this->var_dec->dim_list) {
          add_arr_dimension(at, i);
        }
        add_arr_basetype(at, this->var_type);
        st->push_var(this->var_dec->id, at);
      } else {
        st->push_var(this->var_dec->id, this->var_type);
      }
      break;
    }
    case 1: {  // Dec := VarDec ASSIGN Exp
      this->var_dec->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ASSIGN\n";
#endif
      this->exp->visit(indent_level + 1, st);

      if (!this->var_dec->is_array) {
        // 1. VarDec is non-array: Dec's type = Exp's type
        if (!compare_var_type(this->var_type, this->exp->var_type)) {
          std::cout << "Error type 17 at Line " << this->first_line
                    << ": the variable’s assigned type mismatches the "
                       "declared type\n";
          break;
        }
      } else {
        // 2. VarDec is array: error if Exp's type is not array
        if (this->exp->var_type->category != ARRAY) {
          std::cout << "Error type 17 at Line " << this->first_line
                    << ": the variable’s assigned type mismatches the "
                       "declared type\n";
          break;
        }
      }
      st->push_var(this->var_dec->id, this->var_type);
      break;
    }

    default: {
      std::cout << "Fail to visit <Dec> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
