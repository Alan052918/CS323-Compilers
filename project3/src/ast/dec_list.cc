#include "../../include/ast/dec_list.hh"
#include "../../include/ast/dec.hh"

DecList::DecList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce DecList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}
void DecList::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:    // DecList := Dec
    case 1: {  // DecList := Dec COMMA DecList
               // PUSH VAR for each Dec
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        Dec *dec = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "DecList (" << dec->first_line << ")\n";
#endif
        dec->var_type = this->var_type;
        dec->visit(indent_level + 1 + i, st);
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
      std::cout << "Fail to visit <DecList> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
