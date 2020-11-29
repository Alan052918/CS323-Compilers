#include "../../include/ast/def_list.h"
#include "../../include/ast/def.h"

DefList::DefList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce DefList[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}
void DefList::visit(int indent_level, SymbolTable *st) {
  if (this->rhs_form == 1) {
    return;
  }
  switch (this->rhs_form) {
    case 0:  // DefList := Def DefList
      for (int i = 0; i < this->node_list.size(); i++) {
        Def *def = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        printf("DefList (%d)\n", def->first_line);
#endif
        def->visit(indent_level + 1 + i, st);
      }
      break;
      /* case 1:  // DefList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <DefList> Node: line %d\n",
              this->first_line);
      break;
  }
}
