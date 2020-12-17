#include "../../include/ast/var_dec.hpp"

VarDec::VarDec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce VarDec[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
#endif
  this->is_array = false;
}

void VarDec::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("VarDec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // VarDec := ID
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
#endif
      this->id = this->id_node->id_token;
      if (st->find_var(this->id, DecfMode)) {
        std::cout << "Error type 3 at Line " << this->first_line
                  << ": redefine variable: " << this->id << std::endl;
      }
      break;
    }
    case 1: {  // VarDec := VarDec LB INT RB
               // array variable declaration
      this->var_dec->visit(indent_level + 1, st);
      this->is_array = true;
      this->dim_list.push_back(this->int_node->int_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("LB\n");
      this->print_indentation(indent_level + 1);
      printf("INT: %ld\n", this->int_node->int_token);
      this->print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;
    }

    default: {
      fprintf(stderr, "Fail to visit <VarDec> Node: line %d\n",
              this->first_line);
      break;
    }
  }
}
