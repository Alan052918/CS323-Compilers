#include "../../include/ast/def_list.hh"
#include "../../include/ast/def.hh"

DefList::DefList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce DefList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}
void DefList::visit(int indent_level, SymbolTable *st) {
  if (this->rhs_form == 1) {
    return;
  }
  switch (this->rhs_form) {
    case 0:  // DefList := Def DefList
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        Def *def = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "DefList (" << def->first_line << ")\n";
#endif
        def->visit(indent_level + 1 + i, st);
      }
      break;
      /* case 1:  // DefList := %empty
        break; */

    default:
      std::cout << "Fail to visit <DefList> Node: line " << this->first_line
                << std::endl;

      break;
  }
}
