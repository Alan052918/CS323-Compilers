#ifndef STMT_LIST_H
#define STMT_LIST_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Stmt;

class StmtList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Stmt *> node_list;

  // data member variables
  VarType *return_type;

  StmtList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STMT_LIST_H
