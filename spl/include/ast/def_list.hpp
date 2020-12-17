#ifndef DEF_LIST_H
#define DEF_LIST_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class Def;

class DefList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Def *> node_list;

  // data member variables
  std::vector<std::pair<char *, VarType *> > var_list;

  DefList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEF_LIST_H
