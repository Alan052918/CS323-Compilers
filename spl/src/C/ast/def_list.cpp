#include "../../../include/ast/def_list.h"
#include "../../../include/ast/def.h"

DefList::DefList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce DefList[%d]\n", rhsf);
#endif
}
void DefList::visit(int indent_level) {
  if (this->rhs_form == 1) {
    return;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("DefList (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // DefList := Def DefList
      for (int i = 0; i < this->node_list.size(); i++) {
        Def *def = this->node_list.at(i);
        def->visit(indent_level + i);
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
