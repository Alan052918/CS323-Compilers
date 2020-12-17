#include "../../include/ast/var_list.hpp"
#include "../../include/ast/param_dec.hpp"

VarList::VarList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce VarList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void VarList::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:  // VarList := ParamDec COMMA VarList | ParamDec
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        ParamDec *param_dec = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "VarList (" << param_dec->first_line << ")\n";
#endif
        param_dec->visit(indent_level + 1 + i, st);
        // st->push_var(param_dec->id, param_dec->var_type);
        this->id_list.push_back(param_dec->id);
        this->type_list.push_back(param_dec->var_type);
#if defined(TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          std::cout << "COMMA\n";
        }
#endif
      }
      break;

    default:
      std::cout << "Fail to visit <VarList> Node: line " << this->first_line
                << std::endl;
      break;
  }
}
