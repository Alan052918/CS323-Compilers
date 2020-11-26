#ifndef STMT_LIST_H
#define STMT_LIST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Stmt;

class StmtList : public NonterminalNode {
 public:
  std::vector<Stmt *> node_list;

  StmtList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce StmtList[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // STMT_LIST_H
