#ifndef STMT_H
#define STMT_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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
