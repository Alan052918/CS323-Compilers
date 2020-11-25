#include "../../../include/ast/dec.h"
#include "../../../include/ast/exp.h"
#include "../../../include/ast/var_dec.h"

void Dec::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Dec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // Dec := VarDec
      this->var_dec->visit(indent_level + 1);
      break;
    case 1:  // Dec := VarDec ASSIGN Exp
      this->var_dec->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ASSIGN\n");
#endif
      this->exp->visit(indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Dec> Node: line %d\n", this->first_line);
      break;
  }
}