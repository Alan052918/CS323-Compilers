#include "../../include/ast/ext_dec_list.hh"
#include "../../include/ast/var_dec.hh"

ExtDecList::ExtDecList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce ExtDecList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void ExtDecList::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:  // ExtDecList := VarDec | VarDec COMMA ExtDecList
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        VarDec *var_dec = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "ExtDecList (" << var_dec->first_line << ")\n";
#endif
        var_dec->visit(indent_level + 1 + i, st);
#if defined(TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          std::cout << "COMMA\n";
        }
#endif
        if (var_dec->is_array == true) {
          this->dec_list.push_back(
              std::make_pair(var_dec->id, var_dec->dim_list));
        } else {
          // pass empty vector as dimension vector for non-array variable
          this->dec_list.push_back(
              std::make_pair(var_dec->id, std::vector<int>()));
        }
      }
      break;

    default:
      std::cout << "Fail to visit <ExtDecList> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
  }
}
