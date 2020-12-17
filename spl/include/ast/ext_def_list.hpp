#ifndef EXT_DEF_LIST_H
#define EXT_DEF_LIST_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class ExtDef;

class ExtDefList : public NonterminalNode {
 public:
  std::vector<ExtDef *> node_list;

  ExtDefList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEF_LIST_H
