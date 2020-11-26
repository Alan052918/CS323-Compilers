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

  ExtDecList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level);
};

#endif  // EXT_DEC_LIST_H
