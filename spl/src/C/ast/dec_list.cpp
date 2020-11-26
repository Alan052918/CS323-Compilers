#include "../../../include/ast/dec_list.h"
#include "../../../include/ast/dec.h"

DecList::DecList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce DecList[%d]\n", rhsf);
#endif
}
void DecList::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("DecList (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // DecList := Dec | Dec COMMA DecList
      for (int i = 0; i < this->node_list.size(); i++) {
        Dec *dec = this->node_list.at(i);
        dec->visit(indent_level + i);
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + i);
          printf("COMMA\n");
        }
#endif
      }
      break;

    default:
      fprintf(stderr, "Fail to visit <DecList> Node: line %d\n",
              this->first_line);
      break;
  }
}
