#ifndef DEC_LIST_H
#define DEC_LIST_H

#include "ast.h"
#include "dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class DecList : public NonterminalNode {
 public:
  std::vector<Dec *> node_list;

  DecList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
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
};

#endif  // DEC_LIST_H
