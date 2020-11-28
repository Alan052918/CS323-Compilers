#include "../../include/ast/dec_list.h"
#include "../../include/ast/dec.h"

DecList::DecList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce DecList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}
void DecList::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:  // DecList := Dec | Dec COMMA DecList
             // PUSH VAR for each Dec
      for (int i = 0; i < this->node_list.size(); i++) {
        Dec *dec = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "DecList (" << dec->first_line << ")\n";
#endif
        dec->visit(indent_level + 1 + i, st);
        if (!dec->is_assign && !dec->is_array) {
          // not assigned, not array
          st->push_var(dec->id, this->var_type);
        } else if (!dec->is_assign && dec->is_array) {
          // not assigned, is array
          // TODO: call add_arr_dimension() and add_arr_basetype() to build
          // array type
        } else if (dec->is_assign && !dec->is_array) {
          // is assigned, not array
          if (!compare_var_type(dec->var_type, this->var_type)) {
            std::cout << "Error type 17 at Line " << this->first_line
                      << ": the variable’s assigned type mismatches the "
                         "declared type\n";
          }
          st->push_var(dec->id, this->var_type);
        } else {
          // is assigned, is array
          if (this->var_type->category != ARRAY) {
            std::cout << "Error type 17 at Line " << this->first_line
                      << ": the variable’s assigned type mismatches the "
                         "declared type\n";
          }
          st->push_var(dec->id, this->var_type);
        }
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          std::cout << "COMMA\n";
        }
#endif
      }
      break;

    default:
      std::cout << "Fail to visit <DecList> Node: line " << this->first_line
                << std::endl;
      break;
  }
}
