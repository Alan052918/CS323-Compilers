#ifndef DEF_LIST_H
#define DEF_LIST_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Def;

class DefList : public NonterminalNode {
 public:
  std::vector<Def *> node_list;

  std::vector<std::pair<char *, VarType *> > var_list;

  DefList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEF_LIST_H
