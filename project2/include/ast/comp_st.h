#ifndef COMP_ST_H
#define COMP_ST_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class DefList;
class StmtList;

class CompSt : public NonterminalNode {
 public:
  // nonterminal member variables
  DefList *def_list;
  StmtList *stmt_list;

  // data member variables
  VarType *return_type;

  CompSt(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // COMP_ST_H
