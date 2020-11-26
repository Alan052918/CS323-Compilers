#include "../../include/ast/ext_dec_list.h"
#include "../../include/ast/var_dec.h"

ExtDecList::ExtDecList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce ExtDecList[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc,
         lc);
#endif
}

void ExtDecList::visit(int indent_level) {
  switch (this->rhs_form) {
    case 0:  // ExtDecList := VarDec | VarDec COMMA ExtDecList
      for (int i = 0; i < this->node_list.size(); i++) {
        VarDec *var_dec = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        printf("ExtDecList (%d)\n", var_dec->first_line);
#endif
        var_dec->visit(indent_level + 1 + i);
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          printf("COMMA\n");
        }
#endif
      }
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDecList> Node: line %d\n",
              this->first_line);
      break;
  }
}
