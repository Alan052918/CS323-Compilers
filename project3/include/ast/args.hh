#ifndef ARGS_H
#define ARGS_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class Exp;

class Args : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Exp *> node_list;

  // data member variables
  std::vector<VarType *> type_list;

  Args(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;

  VarType *exp_var_type();
};

#endif  // ARGS_H
