#ifndef DEC_LIST_H
#define DEC_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class Dec;

class DecList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Dec *> node_list;

  // data member variables
  // This variable type is inherited from parent (Def) node
  VarType *var_type;

  DecList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEC_LIST_H
