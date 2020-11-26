#include "../../../include/ast/var_dec.h"

VarDec::VarDec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce VarDec[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void VarDec::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("VarDec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // VarDec := ID
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
#endif
      this->id = this->id_node->id_token;
      // strcpy(this->id, this->id_node->id_token);
      this->is_array = false;
      break;
    }
    case 1: {  // VarDec := VarDec LB INT RB
               // array variable declaration
      this->var_dec->visit(indent_level + 1);
      this->is_array = true;

      this->dim_list.push_back(this->int_node->int_token);
#if defined(PARSE_TREE) || defined(DEBUG)
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
