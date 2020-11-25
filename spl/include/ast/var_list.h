#ifndef VAR_LIST_H
#define VAR_LIST_H

#include "ast.h"
#include "param_dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class VarList : public NonterminalNode {
 public:
  std::vector<ParamDec *> node_list;

  std::vector<VarType *> type_list;

  VarList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("VarList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // VarList := ParamDec COMMA VarList | ParamDec
        for (int i = 0; i < this->node_list.size(); i++) {
          ParamDec *param_dec = this->node_list.at(i);
          param_dec->visit(indent_level + i);
          this->type_list.push_back(param_dec->var_type);
#if defined(PARSE_TREE) || defined(DEBUG)
          if (i < this->node_list.size() - 1) {
            this->print_indentation(indent_level + i);
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
};

#endif  // VAR_LIST_H
