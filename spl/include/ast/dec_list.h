#ifndef DEC_LIST_H
#define DEC_LIST_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Dec;

class DecList : public NonterminalNode {
 public:
  std::vector<Dec *> node_list;

  DecList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEC_LIST_H
