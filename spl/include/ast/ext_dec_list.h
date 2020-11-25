#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.h"
#include "var_dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ExtDecList : public NonterminalNode {
 public:
  std::vector<VarDec *> node_list;

  ExtDecList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("ExtDecList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDecList := VarDec | VarDec COMMA ExtDecList
        for (int i = 0; i < this->node_list.size(); i++) {
          VarDec *var_dec = this->node_list.at(i);
          var_dec->visit(indent_level + i);
#if defined(PARSE_TREE) || defined(DEBUG)
          if (i < this->node_list.size() - 1) {
            this->print_indentation(indent_level + i);
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
};

#endif  // EXT_DEC_LIST_H
