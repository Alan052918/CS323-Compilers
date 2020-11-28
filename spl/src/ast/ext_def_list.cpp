#include "../../include/ast/ext_def_list.h"
#include "../../include/ast/ext_def.h"

ExtDefList::ExtDefList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce ExtDefList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void ExtDefList::visit(int indent_level, SymbolTable *st) {
  if (this->rhs_form == 1) {
    return;
  }
  switch (this->rhs_form) {
    case 0: {  // ExtDefList := ExtDef ExtDefList
      for (int i = 0; i < this->node_list.size(); i++) {
        ExtDef *ext_def = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "ExtDefList (" << ext_def->first_line << ")\n";
#endif
        ext_def->visit(indent_level + 1 + i, st);
      }
      break;
    }
      /* case 1:  // ExtDefList := %empty
        break; */

    default: {
      std::cout << "Fail to visit <ExtDefList> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
