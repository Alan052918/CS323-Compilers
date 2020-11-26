#ifndef DEC_LIST_H
#define DEC_LIST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Dec;

class DecList : public NonterminalNode {
 public:
  std::vector<Dec *> node_list;

  DecList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce DecList[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // DEC_LIST_H
