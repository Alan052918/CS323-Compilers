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

  StmtList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level);
};

#endif  // STMT_LIST_H
