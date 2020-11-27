#ifndef STMT_H
#define STMT_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class CompSt;
class Exp;

class Stmt : public NonterminalNode {
 public:
  CompSt *comp_st;
  Exp *exp;
  Stmt *stmt_1, *stmt_2;

  Stmt(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STMT_H
