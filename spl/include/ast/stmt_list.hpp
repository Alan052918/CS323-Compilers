#ifndef STMT_LIST_H
#define STMT_LIST_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class Stmt;

class StmtList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Stmt *> node_list;

  // data member variables
  VarType *return_type;

  StmtList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STMT_LIST_H
