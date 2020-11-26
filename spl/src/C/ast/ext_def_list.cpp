#include "../../../include/ast/ext_def_list.h"
#include "../../../include/ast/ext_def.h"

ExtDefList::ExtDefList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce ExtDefList[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc,
         lc);
#endif
}

void ExtDefList::visit(int indent_level) {
  if (this->rhs_form == 1) {
    return;
  }
  switch (this->rhs_form) {
    case 0:  // ExtDefList := ExtDef ExtDefList
      for (int i = 0; i < this->node_list.size(); i++) {
        ExtDef *ext_def = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        printf("ExtDefList (%d)\n", ext_def->first_line);
#endif
        ext_def->visit(indent_level + 1 + i);
      }
      break;
      /* case 1:  // ExtDefList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <ExtDefList> Node: line %d\n",
              this->first_line);
      break;
  }
}
