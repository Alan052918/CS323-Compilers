#include "../../../include/ast/param_dec.h"
#include "../../../include/ast/specifier.h"
#include "../../../include/ast/var_dec.h"

void ParamDec::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("ParamDec (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // ParamDec := Specifier VarDec
      this->specifier->visit(indent_level + 1);
      this->var_dec->visit(indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
              this->first_line);
      break;
  }
}
