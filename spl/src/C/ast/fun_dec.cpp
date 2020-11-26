#include "../../../include/ast/fun_dec.h"
#include "../../../include/ast/var_list.h"

FunDec::FunDec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce FunDec[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void FunDec::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("FunDec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // FunDec := ID LP VarList RP
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->var_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 1:  // FunDec := ID LP RP
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
      this->print_indentation(indent_level + 1);
      printf("LP\n");
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <FunDec> Node: line %d\n",
              this->first_line);
      break;
  }
}
