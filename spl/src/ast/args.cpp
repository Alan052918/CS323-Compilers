#include "../../include/ast/args.hpp"
#include "../../include/ast/exp.hpp"

Args::Args(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce Args[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
#endif
}

void Args::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:  // Args := Exp COMMA Args | Exp
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        Exp *exp = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        printf("Args (%d)\n", exp->first_line);
#endif
        exp->visit(indent_level + 1 + i, st);
        this->type_list.push_back(exp->var_type);
#if defined(TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
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
