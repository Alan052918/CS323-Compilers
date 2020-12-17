#ifndef STMT_H
#define STMT_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class CompSt;
class Exp;

class Stmt : public NonterminalNode {
 public:
  // nonterminal member variables
  CompSt *comp_st;
  Exp *exp;
  Stmt *stmt_1, *stmt_2;

  // data member variables
  VarType *var_type;

  Stmt(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STMT_H
