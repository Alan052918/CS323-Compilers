#ifndef ARGS_H
#define ARGS_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Exp;

class Args : public NonterminalNode {
 public:
  std::vector<Exp *> node_list;

  std::vector<VarType *> type_list;

  Args(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;

  VarType *exp_var_type();
};

#endif  // ARGS_H
