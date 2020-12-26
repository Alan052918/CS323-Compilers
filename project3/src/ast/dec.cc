#include "../../include/ast/dec.hh"
#include "../../include/ast/exp.hh"
#include "../../include/ast/var_dec.hh"

Dec::Dec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Dec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Dec::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
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
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ASSIGN\n";
#endif
      this->exp->visit(indent_level + 1, st);
      st->push_var(this->var_dec->id, this->var_type);
      break;
    }

    default: {
      std::cout << "Fail to visit <Dec> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
