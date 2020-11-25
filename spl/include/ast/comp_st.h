#ifndef COMP_ST_H
#define COMP_ST_H

#include "ast.h"
#include "def_list.h"
#include "stmt_list.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class CompSt : public NonterminalNode {
 public:
  DefList *def_list;
  StmtList *stmt_list;

  CompSt(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("CompSt (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // CompSt := LC DefList StmtList RC
               // enter new scope, PUSH MAP
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("LC\n");
#endif
        st.push_maps();
        this->def_list->visit(indent_level + 1);
        this->stmt_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("RC\n");
#endif
        break;

      default:
        fprintf(stderr, "Fail to visit <CompSt> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // COMP_ST_H
