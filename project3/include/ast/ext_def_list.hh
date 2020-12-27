#ifndef EXT_DEF_LIST_H
#define EXT_DEF_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class ExtDef;

class ExtDefList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<ExtDef *> node_list;

  ExtDefList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEF_LIST_H
