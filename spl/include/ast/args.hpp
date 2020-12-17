#ifndef ARGS_H
#define ARGS_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

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
