#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class VarDec;

class ExtDecList : public NonterminalNode {
 public:
  std::vector<VarDec *> node_list;

  ExtDecList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce ExtDecList[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // EXT_DEC_LIST_H
