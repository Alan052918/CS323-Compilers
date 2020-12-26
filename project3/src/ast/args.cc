#include "../../include/ast/args.hh"
#include "../../include/ast/exp.hh"

Args::Args(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Args[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Args::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:    // Args := Exp COMMA Args
    case 1: {  // Args := Exp
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        Exp *exp = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "Args (" << exp->first_line << ")\n";
#endif
        exp->visit(indent_level + 1 + i, st);
        this->type_list.push_back(exp->var_type);
#if defined(TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          std::cout << "COMMA\n";
        }
#endif
      }
      break;
    }

    default: {
      std::cout << "Fail to visit <Args> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
