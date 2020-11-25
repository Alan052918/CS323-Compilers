#ifndef DEF_LIST_H
#define DEF_LIST_H

#include "ast.h"
#include "def.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class DefList : public NonterminalNode {
 public:
  std::vector<Def *> node_list;

  std::vector<std::pair<char *, VarType *> > var_list;

  DefList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
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
};

#endif  // DEF_LIST_H
