#include "../../../include/ast/args.h"
#include "../../../include/ast/exp.h"

void Args::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Args (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // Args := Exp COMMA Args | Exp
      for (int i = 0; i < this->node_list.size(); i++) {
        Exp *exp = this->node_list.at(i);
        exp->visit(indent_level + i);
        this->type_list.push_back(exp->var_type);
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + i);
          printf("COMMA\n");
        }
#endif
      }
      break;

    default:
      fprintf(stderr, "Fail to visit <Args> Node: line %d\n", this->first_line);
      break;
  }
}
