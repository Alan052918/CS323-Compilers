#ifndef STMT_LIST_H
#define STMT_LIST_H

#include "ast.h"
#include "stmt.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class StmtList : public NonterminalNode {
 public:
  std::vector<Stmt *> node_list;

  StmtList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
    if (this->rhs_form == 1) {
      return;
    }
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("StmtList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // StmtList := Stmt StmtList
        for (int i = 0; i < this->node_list.size(); i++) {
          Stmt *stmt = this->node_list.at(i);
          stmt->visit(indent_level + i);
        }
        break;
        /* case 1:  // StmtList := %empty
          break; */

      default:
        fprintf(stderr, "Fail to visit <StmtList> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // STMT_LIST_H
