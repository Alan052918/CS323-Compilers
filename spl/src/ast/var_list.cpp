#include "../../include/ast/var_list.h"
#include "../../include/ast/param_dec.h"

VarList::VarList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce VarList[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void VarList::visit(int indent_level, SymbolTable *st) {
  switch (this->rhs_form) {
    case 0:  // VarList := ParamDec COMMA VarList | ParamDec
      for (int i = 0; i < this->node_list.size(); i++) {
        ParamDec *param_dec = this->node_list.at(i);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        printf("VarList (%d)\n", param_dec->first_line);
#endif
        param_dec->visit(indent_level + 1 + i, st);
        // this->type_list.push_back(param_dec->var_type);
        st->push_var(param_dec->id, param_dec->var_type);
#if defined(PARSE_TREE) || defined(DEBUG)
        if (i < this->node_list.size() - 1) {
          this->print_indentation(indent_level + 1 + i);
          printf("COMMA\n");
        }
#endif
      }
      break;

    default:
      fprintf(stderr, "Fail to visit <VarList> Node: line %d\n",
              this->first_line);
      break;
  }
}
