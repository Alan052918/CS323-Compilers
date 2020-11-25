#ifndef EXT_DEF_LIST_H
#define EXT_DEF_LIST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ExtDef;

class ExtDefList : public NonterminalNode {
 public:
  std::vector<ExtDef *> node_list;

  ExtDefList(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // EXT_DEF_LIST_H
