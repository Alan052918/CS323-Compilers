#ifndef COMP_ST_H
#define COMP_ST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class DefList;
class StmtList;

class CompSt : public NonterminalNode {
 public:
  DefList *def_list;
  StmtList *stmt_list;

  CompSt(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // COMP_ST_H
