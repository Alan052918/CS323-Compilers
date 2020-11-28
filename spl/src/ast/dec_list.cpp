#include "../../include/ast/dec_list.h"
#include "../../include/ast/dec.h"

DecList::DecList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce DecList[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
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
        printf("DecList (%d)\n", dec->first_line);
#endif
        dec->visit(indent_level + 1 + i, st);
        if (dec->is_assign == false && dec->is_array == false) {
          // not assigned, not array
          st->push_var(dec->id, this->var_type);
        } else if (dec->is_assign == false && dec->is_array == true) {
          // not assigned, is array
          // TODO: call add_arr_dimension() and add_arr_basetype() to build
          // array type
        } else if (dec->is_assign == true && dec->is_array == false) {
          // is assigned, not array
          if (dec->var_type != this->var_type) {
            fprintf(stderr,
                    "Error Type 17 at Line %d: the variable’s assigned type "
                    "mismatches the declared type\n",
                    this->first_line);
          }
          st->push_var(dec->id, this->var_type);
        } else {
          // is assigned, is array
          if (this->var_type->category != ARRAY) {
            fprintf(stderr,
                    "Error Type 17 at Line %d: the variable’s assigned type "
                    "mismatches the declared type\n",
                    this->first_line);
          }
          st->push_var(dec->id, this->var_type);
        }
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          printf("COMMA\n");
        }
#endif
      }
      break;

    default:
      fprintf(stderr, "Fail to visit <DecList> Node: line %d\n",
              this->first_line);
      break;
  }
}
