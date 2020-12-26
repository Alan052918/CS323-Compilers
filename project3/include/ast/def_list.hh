#ifndef DEF_LIST_H
#define DEF_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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
