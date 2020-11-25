#ifndef EXT_DEF_LIST_H
#define EXT_DEF_LIST_H

#include "ast.h"
#include "ext_def.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ExtDefList : public NonterminalNode {
 public:
  std::vector<ExtDef *> node_list;

  ExtDefList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
    if (this->rhs_form == 1) {
      return;
    }
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("ExtDefList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDefList := ExtDef ExtDefList
        for (int i = 0; i < this->node_list.size(); i++) {
          ExtDef *ext_def = this->node_list.at(i);
          ext_def->visit(indent_level + i);
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
};

#endif  // EXT_DEF_LIST_H
